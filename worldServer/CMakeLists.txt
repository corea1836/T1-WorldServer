add_executable(WorldServer
    WorldServer.cpp
        WorldLoop.h
        WorldLoop.cpp
)

target_link_libraries(WorldServer PRIVATE Boost::headers)
target_compile_options(WorldServer PRIVATE -Wall -Wextra)
