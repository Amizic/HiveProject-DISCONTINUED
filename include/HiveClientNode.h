#ifndef HIVECLIENTNODE_H
#define HIVECLIENTNODE_H
#define _MAX_CONNECTIONS 30

#include <iostream>
#ifdef _WIN32 // Check if compiling for Windows
#include <winsock2.h>
#include <unistd.h>
#else // Assuming Unix-like system
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif


#include <IHiveClientNode.h>
/*
    ####MANUAL####
    1. Create client socket
    2. Define server address
    3. Connect to server
    4. Send/Receive data from server
    5. Close client socket

*/

class HiveClientNode: public IHiveClientNode
{
    private:

        int clientSocket;
        sockaddr_in serverAddress;

    public:
        char message[1024];
        HiveClientNode();
        virtual ~HiveClientNode();

        int CreateClientSocket() override;
        void CloseClientSocket() override;
        int GetClientSocket() override;
        void DefineServerIPV4(int port) override;
        int ConnectToServer() override;
        int SendDataToServer(const char* Data) override;
        void ReadDataFromServer() override;

};

#endif // HIVECLIENTNODE_H
