#include "HiveServerNode.h"

HiveServerNode::HiveServerNode()
{
    //ctor
}

HiveServerNode::~HiveServerNode()
{
    //dtor
}

int HiveServerNode::GetServerSocket(){
        return this->serverSocket;
    }

    //Create socket for client for IPV4 protocol
int HiveServerNode::CreateServerSocket(){
        return this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    };

    //Closing of socket
int HiveServerNode::CloseServerSocket(){
        return close(this->serverSocket);
    }

    //Define server address
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
void HiveServerNode::Listen(){
        listen(this->serverSocket, _MAX_CONNECTIONS);
    }

void HiveServerNode::PrepareClients(){
        for(int i=0;i<_MAX_CONNECTIONS;i++){
            this->clientSockets[i]=0;
        }
    }

    //Accept communication from server
int HiveServerNode::AcceptNewClient(){
        //return this->clientSocket[currentClientIndex] = accept(this->serverSocket, nullptr, nullptr);
        return this->newClient = accept(this->serverSocket, (struct sockaddr*)&this->serverAddress, nullptr);
    }

int HiveServerNode::SendOrderTest(){
        const char * message="Order from server!";
        send(newClient, message, strlen(message), 0);
        return 1;
    }


void HiveServerNode::ChooseFile(char* fileName){
        this->fileName = fileName;
    }

    /*DATA IO OPERATIONS*/
    // Function to read file content into a character array
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
