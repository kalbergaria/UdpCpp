# UdpCpp
A cross-platform (tested on: Windows and Linux) C++ project developed and tested to send and receive arbitrary data via UDP.

# Building for Windows
A Visual Studio C++ project is located within the windows directory. This can be used to for compiling/building and for future development.

# Building for Linux
Located within the linux directory are two makefiles (receiverTest.mk and senderTest.mk). Run these using the command make -f <filename> to compile and build each test.

# Development
If you would like to modify/update any files, all of the source code files are located in the sourceCode directory. Just remember that the Visual Studio project is also configured to compile/build from those files so modifications made for one platform will be visible to other as well.
