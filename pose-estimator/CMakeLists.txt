
file(GLOB_RECURSE QR_POSE_EST_SOURCES "src/*.cpp")

add_library(QRPoseEstimator SHARED
	${QR_POSE_EST_SOURCES}
	)

target_link_libraries(QRPoseEstimator
	${OpenCV_LIBS}
	${ZBAR_LIBRARIES}
	)
