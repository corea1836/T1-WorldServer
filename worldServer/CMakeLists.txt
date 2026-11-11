add_executable(WorldServer
    WorldServer.cpp
        WorldLoop.h
        WorldLoop.cpp
)

target_compile_options(WorldServer PRIVATE -Wall -Wextra)
