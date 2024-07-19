#ifndef HIVECLIENTNODE_H
#define HIVECLIENTNODE_H

#include <winsock2.h>
#include <unistd.h>

#include <iostream>
#define _MAX_CONNECTIONS 10

/*
    ####MANUAL####
    1. Create client socket
    2. Define server address
    3. Connect to server
    4. Send/Receive data from server
    5. Close client socket

*/

class HiveClientNode
{
    private:

        int clientSocket;
        sockaddr_in serverAddress;

    public:
        char message[1024];
        HiveClientNode();
        virtual ~HiveClientNode();

    int GetClientSocket(){
        return this->clientSocket;
    }

    //Create socket for client for IPV4 protocol
    int CreateClientSocket(){
        return this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    }

    //Closing of socket
    void CloseClientSocket(){
        close(this->clientSocket);
    }

    //Define server address
    void DefineServerIPV4(int port){
        this->serverAddress.sin_family = AF_INET;
        this->serverAddress.sin_port = htons(port);
        //this->serverAddress.sin_addr.s_addr = INADDR_ANY;
        //this->serverAddress.sin_addr.s_addr = '127.0.0.1';
        this->serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    }


    //Connect to server
    int ConnectToServer(){
        return connect(this->clientSocket, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress));
    }

    //Send data to server from Client
    int SendDataToServer(const char* Data){
        //const char* message = "TEST DATA TRANSMISSION FROM CLIENT";
        //std::cout << message <<std::endl;
        return send(this->clientSocket, Data, strlen(Data), 0);
    }


    //Reading of data from server
    void ReadDataFromServer(){
        char buffer[1024] = {0};
        recv(this->clientSocket, buffer, sizeof(buffer), 0);
        std::cout << "Message from server: " << buffer << std::endl;
    }

};

#endif // HIVECLIENTNODE_H
