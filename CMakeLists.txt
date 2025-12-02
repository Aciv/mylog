cmake_minimum_required(VERSION 3.25)
project(SimpleLog VERSION 1.0.0)

find_package(Threads REQUIRED)

add_subdirectory(blockqueue)
add_subdirectory(buffer)
add_subdirectory(sender)
add_subdirectory(log)


include(GNUInstallDirs)

install( 
	TARGETS Log Sender BlockQueue Buffer
	EXPORT SimpleLogTargets
	FILE_SET HEADERS
)

install(
  EXPORT SimpleLogTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimpleLog
  NAMESPACE SimpleLog::
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/SimpleLogConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    cmake/SimpleLogConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SimpleLogConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimpleLog
)


