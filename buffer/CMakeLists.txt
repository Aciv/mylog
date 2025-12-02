add_library(Buffer OBJECT)

target_sources( Buffer
    PRIVATE
        buffer.cpp
    PUBLIC
        FILE_SET HEADERS 
        FILES 
            buffer.h
)

target_compile_features( Buffer PRIVATE cxx_std_20)