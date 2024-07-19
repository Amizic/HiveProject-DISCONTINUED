#ifndef HIVESERVERNODE_H
#define HIVESERVERNODE_H

#define _MAX_CONNECTIONS 30

#include <winsock2.h>
#include <unistd.h>

#include <stdio.h>


/*
    ####MANUAL####
    1. Create server socket
    2. Define server address
    3. Prepare clients
    4. Accept new client (socket)
    5. Add newly created socket to File Descriptor Set
    6. Traverse trough the File Descriptor Set, and check for each FD.
    7. Receive/Send data to each client
    8. Check for new connections
    9. Repeat from step 3.
    10. Close server socket
*/

class HiveServerNode
{
    private:
        int serverSocket;
        sockaddr_in serverAddress;
        int newClient;
        int clientSockets[_MAX_CONNECTIONS];

    public:
        HiveServerNode();
        virtual ~HiveServerNode();

    int GetServerSocket(){
        return this->serverSocket;
    }

    //Create socket for client for IPV4 protocol
    int CreateServerSocket(){
        return this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    };

    //Closing of socket
    void CloseServerSocket(){
        close(this->serverSocket);
    }

    //Define server address
    void DefineServerIPV4(int port){
        this->serverAddress.sin_family = AF_INET;
        this->serverAddress.sin_port = htons(port);
        //this->serverAddress.sin_addr.s_addr = INADDR_ANY;
        //this->serverAddress.sin_addr.s_addr = '127.0.0.1';
        this->serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    //Binding Server Socket to Server Address
    int BindServerSocket(){
        return bind(this->serverSocket, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress));
    }

    //Listening on a specific socket (after it is created and binded to)
    void Listen(){
        listen(this->serverSocket, _MAX_CONNECTIONS);
    }

    void PrepareClients(){
        for(int i=0;i<_MAX_CONNECTIONS;i++){
            this->clientSockets[i]=0;
        }
    }

    //Accept communication from server
    int AcceptNewClient(){
        //return this->clientSocket[currentClientIndex] = accept(this->serverSocket, nullptr, nullptr);
        return this->newClient = accept(this->serverSocket, (struct sockaddr*)&this->serverAddress, nullptr);
    }

    int SendOrder(){
        const char * message="Order from server!";
        send(newClient, message, strlen(message), 0);
        return 1;
    }


};

#endif // HIVESERVERNODE_H
