cmake_minimum_required(VERSION 3.25)
project(SimpleLog VERSION 1.0.0)

add_subdirectory(blockqueue)
add_subdirectory(buffer)
add_subdirectory(sender)
add_subdirectory(log)


include(GNUInstallDirs)

install( 
	TARGETS Log Sender BlockQueue Buffer
	EXPORT LogTargets
	FILE_SET HEADERS
)

install(
  EXPORT LogTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Log
  NAMESPACE SimpleLog::
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/LogConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    cmake/LogConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/LogConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Log
)


