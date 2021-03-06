
<hr>

## Purpose:

The purpose of this library is to make it so that it is really easy to determine where a robot, UAV or generic camera is relative to a QR code.  To use this library in your project, all you need to do is "calibrate" a camera so the library knows how it works and print out a QR code (instructions below).

Once that is done, you can just load the calibration information, start passing the library frames directly from OpenCV video sources and start getting the pose of your camera.

<hr>
## How it works:

If you have a calibrated camera and a known 3D shape, it is possible to figure out what sort of rotation and translation relative to the camera would be required to make it look like it does when your camera looks at it (OpenCV has some great functions to help with this).  If you invert that transformation, it will give you the rotation and translation of your camera relative to that matrix.

This means that with a bit of work, it is possible to make a landmark and figure out where your camera is relative to it.  This can be used for robotics applications and to do cool augmented reality applications (like this one: https://www.youtube.com/watch?v=wzN_YPlB3fA).  However, it can be hard to make your application be able to distinguish between different landmarks, making using it for navigation a little tricky.  The other catch, is that you need to hard program in how big your landmarks are or your scale will be off.

This library gets around those issues by using QR codes as the landmarks.  QR codes can embed text, which means that we can pull out both how big they are and a unique identifier to tell them apart.  This means that you need to be a little careful printing out your QR codes, but you can use different size tags without having to change your code (getting your pose back in meters, no matter the tag size).

To prepare a QR code for use with the library, you just embed the text in the following format: "sizeOfQRCodeSide-uniqueIdentifier"

For example, a 6 in x 6 in QR code could have "6in-IdentString" as its string (dimension - indentifier).  You can used decimal amounts, such as 6.5 and the following unit types are supported (just remember to put in the "-"):  "m-", "cm-", "mm-", "ft-", "in-". 

<hr>

## Building/Dependencies:

This library depends on OpenCV (a general computer vision library), ZBar (a bar code reading library) and uses the CMake build tool.  It has been built and tested on Ubuntu Linux, but should be reasonably easy to port to other systems (cmake is cross platform).

Getting OpenCV:  
`http://opencv.org/downloads.html`

Getting ZBar:  
`http://zbar.sourceforge.net/download.html`

If you are running Ubuntu Linux, you can download the dependencies by running the following commands:   
`sudo apt-get install libopencv-dev libopencv-highgui-dev libopencv-calib3d-dev`  
`sudo apt-get install libzbar-dev`  
`sudo apt-get install cmake`  

The library can be build once the dependencies have been satisfied by going to the root directory and running the following commands (Ubuntu Linux tested):     
`cmake ./`      
`make`   

This will generate the library's .so file in the lib directory, which you can then move to a folder you link to (sorry, no install rule as of yet) and an example program which you can modify to get your project up and running (probably by changing the camera calibration values).

<hr>

## Camera Calibration:

The OpenCV tutorial on how to do camera calibration can be found here:
http://docs.opencv.org/doc/tutorials/calib3d/camera_calibration/camera_calibration.html

Once you have the XML/YAML file that the calibrator generates, pull out the <Camera_Matrix type_id="opencv-matrix"> values and <Distortion_Coefficients type_id="opencv-matrix"> values to populate the camera calibration matrix and distortion parameters respectively. 

An example OpenCV camera calibration file can be found in the example program's source directory.

<hr>

## QR Code generation:

To generate QR codes in Ubuntu Linux, use the command line program qrencode (installable with: sudo apt-get install qrencode)

Once qrencode is installed, you can use a command like this to get an image that can be scaled and printed as a 6 in x 6 in QR code.   

`qrencode -o ./6InTestQRCode.png -s 100 -m 0 '6in-IdentString'`  

<hr>

I hope you find this library useful.  Open a Github issue if you run into trouble.  Thanks.

