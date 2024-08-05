#ifndef HIVESERVERNODE_H
#define HIVESERVERNODE_H

#define _MAX_CONNECTIONS 30


#ifdef _WIN32 // Check if compiling for Windows
#include <winsock2.h>
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
        int serverSocket;
        sockaddr_in serverAddress;
        int newClient;
        int clientSockets[_MAX_CONNECTIONS];

        //IO variables
        char* fileName;
        char* fileBuffer;
        int fileSize;


    public:
        HiveServerNode();
        virtual ~HiveServerNode();

     int GetServerSocket() override;
     int CreateServerSocket() override;
     int CloseServerSocket() override;
     void DefineServerIPV4(int port) override;
     int BindServerSocket() override;
     void Listen() override;
     void PrepareClients() override;
     int AcceptNewClient() override;
     int SendOrderTest() override;
     void ChooseFile(char* fileName)override;
     bool ReadFile()override;



};

#endif // HIVESERVERNODE_H
