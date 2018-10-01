add_subdirectory(actors)
add_subdirectory(utils)
add_subdirectory(hash)



add_executable(server server.c)
add_executable(cli cli.c)


target_link_libraries (server geohash_actor)
target_link_libraries (server geohash)
target_link_libraries (server log_actor)
target_link_libraries (server czmq_utils)
target_link_libraries (server czmq)
target_link_libraries (server m)
target_link_libraries (server buffer)


target_link_libraries (cli czmq_utils)
target_link_libraries (cli czmq)
