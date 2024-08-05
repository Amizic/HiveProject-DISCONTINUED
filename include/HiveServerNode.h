#ifndef HIVESERVERNODE_H
#define HIVESERVERNODE_H

#define _MAX_CONNECTIONS 30
#define _ACCEPT_TIMEOUT 100


#ifdef _WIN32 // Check if compiling for Windows
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#else // Assuming Unix-like system
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif


/*IO Operations*/
#include <iostream>
#include <fstream>
#include <IHiveServerNode.h>
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

class HiveServerNode: public IHiveServerNode
{
    private:
        SOCKET serverSocket;
        SOCKET newClient;
        SOCKET clientSockets[_MAX_CONNECTIONS];
        sockaddr_in serverAddress;
        sockaddr_in clientAddress[_MAX_CONNECTIONS];
        int serverAddressLenght=sizeof(serverAddress);


        //IO variables
        char* fileName;
        char* fileBuffer;
        int fileSize;

    //option for sockets:
    DWORD timeoutMS = _ACCEPT_TIMEOUT;


    public:
        fd_set serverFileDescriptorSet;
        fd_set clientFileDescriptorSet;

        HiveServerNode();
        virtual ~HiveServerNode();

     SOCKET GetServerSocket() override;
     SOCKET GetClientSocket(int clientIndex) override;
     SOCKET CreateServerSocket() override;
     int SetSocketOptions() override;
     int CloseServerSocket() override;
     void DefineServerIPV4(int port) override;
     int BindServerSocket() override;
     int Listen() override;
     void PrepareClients() override;
     SOCKET AcceptNewClient(int clientIndex) override;
     void AddNewClientToList(int clientIndex) override;
     int SendOrder(const char*) override;
     void SendOrdersToAllClients(char* message) override;
     int SendOrderTest() override;
     void ChooseFile(char* fileName)override;
     bool ReadFile()override;
     void ClearServerFileDescriptorSet();
     void ClearClientFileDescriptorSet() override;
     void AddServerSocketToFileDescriptor() override;
     void AddClientSocketToFileDescriptor(int clientIndex) override;



};

#endif // HIVESERVERNODE_H
