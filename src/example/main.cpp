#include <iostream>
#include <iomanip>
#include <memory>

#include "../library/QRCodeStateEstimator.hpp"
#include <cmath>

void printUsage(std::string const& name) {
	std::cout << "Usage: " << name << " CALIB_FILE [CAMERA_ID]" << std::endl;
}

int main(int argc, char** argv) {

	// Print usage and exit when no argument is given
	if (argc < 2) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}

	// Load calibration data from the xml given as first parameter
	cv::FileStorage fs(argv[1], cv::FileStorage::READ);
	cv::Mat_<double> cameraMatrix(3, 3);
	fs["Camera_Matrix"] >> cameraMatrix;
	cv::Mat_<double> distortionParameters(5, 1);  // k1, k2, p1, p2, k3
	fs["Distortion_Coefficients"] >> distortionParameters;

	// Set camera ID from argument if there is one, otherwise use 0
	int cam_idx = 0;
	if (argc == 3) {
		cam_idx = atoi(argv[2]);
	}

	// Open opencv camera video source
	cv::VideoCapture cap(cam_idx);
	if (!cap.isOpened()) {
		std::cerr << "Could not open camera!" << std::endl;
		return EXIT_FAILURE;
	}

	// Make size same as calibration (Change to match your calibration)
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	// Initialize the state estimator, while wrapping any exceptions so we know
	// where it came from
	std::unique_ptr<QRCodeStateEstimator> stateEstimator;
	SOM_TRY
	stateEstimator.reset(new QRCodeStateEstimator(640, 480, cameraMatrix,
																								distortionParameters, true));
	SOM_CATCH("Error initializing state estimator\n")

	// Initialize some variables we are going to use while processing frames
	cv::Mat frame;
	cv::Mat cameraPose;
	std::string QRCodeIdentifierBuffer;
	double QRCodeDimensionBuffer;
	bool thereIsANewFrame = false;

	while (true) {
		// Capture an OpenCV frame from the camera
		cap >> frame;

		// Give the frame to the state estimator and try to get the camera's pose
		// from the QR code image
		SOM_TRY
		thereIsANewFrame = stateEstimator->estimateStateFromBGRFrame(
				frame, cameraPose, QRCodeIdentifierBuffer, QRCodeDimensionBuffer);
		SOM_CATCH("Error estimating state\n")

		// Print out values of camera's pose matrix
		if (thereIsANewFrame) {
			std::cout << "Camera position/orientation matrix:" << std::endl
								<< cameraPose << std::endl;
		}

	}  // End of frame processing loop

	return EXIT_SUCCESS;
}
