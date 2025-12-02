add_library(BlockQueue INTERFACE)

target_sources( BlockQueue
    INTERFACE
        FILE_SET HEADERS 
        FILES 
            blockqueue.h
)
target_compile_features( BlockQueue INTERFACE cxx_std_20)