
file(GLOB_RECURSE SIMPLE_EXAMPLE_SOURCES "src/*.cpp")

add_executable(qrpose-simple ${SIMPLE_EXAMPLE_SOURCES})

target_link_libraries(qrpose-simple
	${OpenCV_LIBS}
	${ZBAR_LIBRARIES}
	QRPoseEstimator
	)
