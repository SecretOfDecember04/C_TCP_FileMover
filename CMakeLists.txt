cmake_minimum_required(VERSION 3.29)
project(C_TCP_FileMover C)

set(CMAKE_C_STANDARD 11)

# Create the client executable
add_executable(ftpc client.c)

# Create the server executable
add_executable(ftps server.c)
