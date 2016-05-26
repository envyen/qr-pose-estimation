cmake_minimum_required(VERSION 3.1)

project(QRPoseEstimation)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV 3 REQUIRED core videoio highgui calib3d)
find_package(ZBar REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
	${ZBAR_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/pose-estimator/include
	)

# build the library
add_subdirectory(pose-estimator)

# build the examples
add_subdirectory(examples)
