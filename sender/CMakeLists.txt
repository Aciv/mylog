add_library(Sender OBJECT)

target_sources( Sender
    PRIVATE
        fileSender.cpp
        sender.cpp
        stdoutSender.cpp
    PUBLIC
        FILE_SET HEADERS 
        FILES 
            sender.h
            level.h
            fileSender.h
            stdoutSender.h
)

target_compile_features(Sender PRIVATE cxx_std_20)