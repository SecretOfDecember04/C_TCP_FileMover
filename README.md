# C TCP File Mover

This project implements a simple file transfer system using TCP sockets in C. The system consists of a client (`ftpc`) and a server (`ftps`) that enable transferring files from the client to the server over a TCP connection.

## Project Structure

```plaintext
C-TCP-FileMover/
├── client.c          # Client source code
├── server.c          # Server source code
├── CMakeLists.txt    # CMake configuration file
├── .gitignore        # Git ignore file
└── README.md         # Project documentation

Features

- Client-Server Architecture: A simple client-server model where the client connects to the server and transfers a file.
- TCP Sockets: Uses TCP STREAM sockets to ensure reliable data transmission.
- File Transfer: The client can send files to the server, and the server will save them locally.

Requirements


- C Compiler: GCC or Clang
- CMake: Version 3.29 or later
- CLion (optional): For an enhanced development experience

Building the Project


Step 1: Clone the Repository
Clone the repository to your local machine using Git:
git clone https://github.com/yourusername/C-TCP-FileMover.git
cd C-TCP-FileMover


Step 2: Build Using CMake
Command Line
If you prefer using the command line, follow these steps:
mkdir build
cd build
cmake ..
make


Step 3: Locate the Executables

After building the project, you will have two executables:

- ftpc: The client program.
- ftps: The server program.
These will be located in the build directory (e.g., cmake-build-debug).

Running the Project

Step 1: Run the Server

In one terminal, navigate to the build directory and start the server:
./ftps <portnumber>


For example, to run the server on port 8080:

./ftps 8080

Step 2: Run the Client
In another terminal, navigate to the build directory and start the client:

./ftpc <server-ip> <portnumber>


For example, to connect the client to the server running on localhost at port 8080:

./ftpc 127.0.0.1 8080


Step 3: Transfer Files
After running the client, it will prompt you to enter the filename to transfer.
The client will then send the file to the server, and the server will save the file.
The server will acknowledge the number of bytes received.
Step 4: End the Session
To end the session, enter DONE when prompted for a filename in the client.
Error Handling
Common Issues
"Address family not supported by protocol family": This typically happens when there’s a mismatch between the address family of the socket and the IP address used. Ensure the socket and IP address are compatible (e.g., IPv4 with AF_INET and 127.0.0.1).
Troubleshooting
Ensure both client and server are using the same IP version (IPv4 or IPv6).
If using localhost, try replacing it with 127.0.0.1.
License
This project is licensed under the MIT License - see the LICENSE file for details.

Contributing
If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.

By completing these steps, you will be able to build, run, and test the C TCP File Mover project successfully. If you encounter any issues, feel free to open an issue on GitHub.


This entire block of text is in markdown format. You can directly copy this into your `README.md` file in your project directory. Let me know if you need anything else!
