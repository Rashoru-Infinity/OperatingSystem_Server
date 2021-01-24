# OperatingSystem_Server
This branch isn't complete so it won't work.  
If you want to check the working version, you should check the following.  
<https://github.com/Rashoru-Infinity/OperatingSystem_Server/tree/Version1.0>  
  
Created as part of a university OS class.  
A program that creates a git remote repository on a host machine in a LAN.  
The server-side program becomes a daemon process and continues to run.  
Once you launch the server program, you can then create a git repository without logging in to its host machine.  
  
# Requirement
Ubuntu : gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0  
Raspbian : gcc (Raspbian 8.3.0-6+rpi1) 8.3.0  
You may need to install OpenSSL 1.1.1.  
  
# Installation
・OpenSSL
<https://github.com/openssl/openssl/tree/OpenSSL_1_1_1-stable>  
After cloning OpenSSL ...  
```
cd openssl
./config
make
sudo make install
Open file /etc/ld.so.conf, add a new line: "/usr/local/lib" at EOF
sudo ldconfig
```
See also <https://stackoverrun.com/ja/q/664736#44282009>  
  
# Usage
```
git clone https://github.com/Rashoru-Infinity/OperatingSystem_Server.git

cd OperatingSystem_Server

# build client side program
make client
(The program will be generated directly under a directory named client)

# build server side program
make server
(The program will be generated directly under a directory named server)

# build client + server
make
or
make all

# delete all object files
make clean

# delete all binary files
make fclean

# delete all binary files & rebuild
make re

# execute client program
cd client
./git_client [host(ip address only)] [port] [keyfile]

# execute server program
cd server
./git_server [port]
```
  
# Note
Since the files used for authentication by the client and the server must match, the files that the client has must be uploaded to the home directory of the user who runs the server-side program.  
The keyfile on the client side will be the uploaded file.  
On the server side, create a directory named "repo" in the home directory of the user who executes the server program in advance.
