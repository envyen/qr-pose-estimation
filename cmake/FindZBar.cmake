find_path(ZBAR_INCLUDE_DIRS zbar.h)
find_library(ZBAR_LIBRARIES	NAMES zbar)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
	ZBar DEFAULT_MSG
	ZBAR_LIBRARIES ZBAR_INCLUDE_DIRS)

mark_as_advanced(
	ZBAR_INCLUDE_DIRS
	ZBAR_LIBRARIES
)
