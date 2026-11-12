add_executable(WorldServer
    WorldServer.cpp
        WorldLoop.h
        WorldLoop.cpp
        NetworkService.cpp
        NetworkService.h
        WorldSocket.cpp
        WorldSocket.h
        MessageBuffer.cpp
        MessageBuffer.h
)

target_link_libraries(WorldServer PRIVATE Boost::headers)
target_compile_options(WorldServer PRIVATE -Wall -Wextra)
