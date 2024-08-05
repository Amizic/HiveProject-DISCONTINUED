#include "HiveServerNode.h"

HiveServerNode::HiveServerNode()
{
    //ctor
}

HiveServerNode::~HiveServerNode()
{
    //dtor
}

    //This function returns the server socket
SOCKET HiveServerNode::GetServerSocket(){
        return this->serverSocket;
    }

    //This function returns client socket
SOCKET HiveServerNode::GetClientSocket(int clientIndex){
        return this->clientSockets[clientIndex];
    }

    //Create socket for client for IPV4 protocol
SOCKET HiveServerNode::CreateServerSocket(){
        return this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    };

int HiveServerNode::SetSocketOptions(){
    if (setsockopt(this->serverSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&this->timeoutMS, sizeof(this->timeoutMS)) == SOCKET_ERROR) {
        return -1;
    }

    return 1;
}

    //Closing of socket
int HiveServerNode::CloseServerSocket(){
        return close(this->serverSocket);
    }

    //Define server address (IPV4 or IPV6, port, ip)
void HiveServerNode::DefineServerIPV4(int port){
        this->serverAddress.sin_family = AF_INET;
        this->serverAddress.sin_port = htons(port);
        //this->serverAddress.sin_addr.s_addr = INADDR_ANY;
        //this->serverAddress.sin_addr.s_addr = '127.0.0.1';
        this->serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    //Binding Server Socket to Server Address
int HiveServerNode::BindServerSocket(){
        return bind(this->serverSocket, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress));
    }

    //Listening on a specific socket (after it is created and binded to)
int HiveServerNode::Listen(){
        return listen(this->serverSocket, _MAX_CONNECTIONS);
    }

    //Initiates list of client sockets to be 0. Call this function only at the beginning of the program. Required for proper functioning.
void HiveServerNode::PrepareClients(){
        for(int i=0;i<_MAX_CONNECTIONS;i++){
            this->clientSockets[i]=0;
        }
    }


//AcceptNewClient and AddNewClientToList are designed to work together
//Accepting new client and putting it in array of client file descriptors
SOCKET HiveServerNode::AcceptNewClient(int clientIndex){

        return this->newClient = accept(this->serverSocket, (struct sockaddr*)&this->clientAddress[clientIndex], nullptr);
}


    //Pass the previously accepted connection from client (file descriptor of socket) to add it to list of active clients (File descriptors)
void HiveServerNode::AddNewClientToList(int clientIndex){
        if(this->clientSockets[clientIndex]<=0){
            this->clientSockets[clientIndex]=this->newClient;
        }
}

    //Pass message to this function, and the message will be sent to client
int HiveServerNode::SendOrder(const char* message){
        send(newClient, message, strlen(message), 0);
        return 1;
    }

void HiveServerNode::SendOrdersToAllClients(char* message){
        for(int i=0;i<_MAX_CONNECTIONS;i++){
            send(clientSockets[i], message, strlen(message), 0);
        }
}

int HiveServerNode::SendOrderTest(){
        const char * message="Order from server!";
        send(newClient, message, strlen(message), 0);
        return 1;
    }


    //Choose file name to be loaded for further reading
void HiveServerNode::ChooseFile(char* fileName){
        this->fileName = fileName;
    }

    /*DATA IO OPERATIONS*/
    // Function to read file content into a character array (based on the previously chosen file name)
bool HiveServerNode::ReadFile() {

                std::ifstream file(fileName); // Open the file in ASCII mode (default)
                if (!file.is_open()) {
                    return false;
                }

                // Get the size of the file
                file.seekg(0, std::ios::end);
                this->fileSize = file.tellg();
                file.seekg(0, std::ios::beg);

                // Allocate memory for the buffer
                this->fileBuffer = new char[fileSize + 1]; // +1 for null terminator

                // Read file into buffer
                file.read(this->fileBuffer, this->fileSize);
                this->fileBuffer[this->fileSize] = '\0'; // Null-terminate the buffer

                // Close the file
                file.close();
                std::cout<<fileBuffer;

            return true;
}

/*
    If development of the code proceeds to add functionality to read data from the clients (such as messages or heartbeat), it is important to have file descriptors to handle non blocking select function
*/

void HiveServerNode::ClearServerFileDescriptorSet(){
    FD_ZERO(&this->serverFileDescriptorSet);
}

void HiveServerNode::ClearClientFileDescriptorSet(){
    FD_ZERO(&this->clientFileDescriptorSet);
}

void HiveServerNode::AddServerSocketToFileDescriptor(){
    FD_SET(this->serverSocket, &this->serverFileDescriptorSet);
}

void HiveServerNode::AddClientSocketToFileDescriptor(int clientIndex){
    FD_SET(this->clientSockets[clientIndex], &this->clientFileDescriptorSet);
}
