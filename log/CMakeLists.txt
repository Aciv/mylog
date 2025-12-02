add_library(Log STATIC)

target_sources( Log
    PRIVATE
        log.cpp
    PUBLIC
        FILE_SET HEADERS 
        FILES 
            pattern.h
            log.h
)


target_link_libraries( Log
    PUBLIC
        Buffer
        Sender
        BlockQueue
)

target_compile_features(Log PRIVATE cxx_std_20)

if(
	(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
	(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)
	target_compile_options(Log PRIVATE -Wall)
	target_compile_options(Log PRIVATE -O2)

endif()