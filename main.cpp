#include <iostream>
#include <stdio.h>

#define _SERVER_PORT 7777

#include <HiveClientNode.h>
#include <HiveServerNode.h>
#include <ThreadResolvers.h>
#include <ColorCodes.h>
//WINDOWS SPECIFIC:
#include <thread>
#include <ASCIIART.h>

using namespace std;

int main()
{
    WSADATA wsaData;
    DWORD lastError;
    int option;

    //Handle for console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int error;
    //int serverConnectionTimeout = -1;
    //int readValue;

    //Request for WSA 2.2 version
    error=WSAStartup(MAKEWORD(2,2), &wsaData);

    if (error != 0){
        SetConsoleTextAttribute(hConsole, _RED);
        cerr<<"WSAStartup failed with error: "<<error<<"\n";
        return 1;
    }
    SetConsoleTextAttribute(hConsole, _GREEN);
    cout<<"WSA started..."<<endl;


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Couldnt find usable WinSock DLL */
        SetConsoleTextAttribute(hConsole, _RED);
        cerr<<"Could not find version of Winsock.dll that can be used"<<"\n";
        WSACleanup();
        return -1;
    }

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTextAttribute(hConsole, _CYAN);




    SetConsoleTextAttribute(hConsole, _WHITE);

    cout<<"1.Initiate client \n2. Test incoming connections from multiple clients\n";
    cin>>option;

    switch(option){
        //Simulate client
        case 1:
        {
            SetConsoleTextAttribute(hConsole, _CYAN);
            GreetingsAngel();
            HiveClientNode hiveClientNodeObject;
            cout<<"Defining server properties...\n";
            hiveClientNodeObject.DefineServerIPV4(_SERVER_PORT);

            cout<<"Creating client socket for data transfer...\n";

            if(hiveClientNodeObject.CreateClientSocket()<0){
                lastError = GetLastError();
                SetConsoleTextAttribute(hConsole, _RED);
                cout<<"Error:"<<lastError<<"\n"<<"Unable to create client socket...\n";
            }


            SetConsoleTextAttribute(hConsole, _GREEN);
            cout<<"Client socket created!\n";

            SetConsoleTextAttribute(hConsole, _WHITE);
            cout<<"---CLIENT_APPLICATION---\n\n";
            cout<<"File Descriptors:\n\n";

            cout<<"\t1.FD:"<<hiveClientNodeObject.GetClientSocket();
            cout<<"\n\t  Description: Client socket used to communicate with server.\n\n";

             //recv(hiveClientNodeObject.GetClientSocket(), (char*)hiveClientNodeObject.message, 1024, 0);


            SetConsoleTextAttribute(hConsole, _RED);
            while(hiveClientNodeObject.ConnectToServer()!=0){
                    cout<<"Connection to server node could not be established...\n";

            }

            SetConsoleTextAttribute(hConsole, _GREEN);
            cout<<"\nConnection to server established successfully!\n";
            SetConsoleTextAttribute(hConsole, _WHITE);
            while(1){
                hiveClientNodeObject.ReadDataFromServer();
            }
            break;
        }

        //simulate server
        case 2:{
            SetConsoleTextAttribute(hConsole, _CYAN);
            GreetingsSeraphim();
            SetConsoleTextAttribute(hConsole, _GREEN);
            HiveServerNode hiveServerNodeObject;

            if(hiveServerNodeObject.CreateServerSocket()<0){
                cerr<<"Unable to create server socket..."<<endl;
                terminate();
            }
            cout<<"Socket created..."<<endl;
            hiveServerNodeObject.ClearServerFileDescriptorSet();
            hiveServerNodeObject.AddServerSocketToFileDescriptor();

            hiveServerNodeObject.DefineServerIPV4(_SERVER_PORT);
            if(hiveServerNodeObject.BindServerSocket()== SOCKET_ERROR){
                SetConsoleTextAttribute(hConsole, _RED);
                cerr << "Unable to bind socket... " << WSAGetLastError() << std::endl;
                terminate();
            }
            cout<<"Socket binded to port "<<_SERVER_PORT<<endl;

            hiveServerNodeObject.ClearClientFileDescriptorSet();
            hiveServerNodeObject.PrepareClients();
            cout<<"Prepared file descriptors for incoming clients: "<<_MAX_CONNECTIONS<<endl;

            if(hiveServerNodeObject.Listen()!=0){
                SetConsoleTextAttribute(hConsole, _RED);
                cerr << "Unable to listen: "<<WSAGetLastError()<<endl;
                terminate();
            }
            cout<<"Listening for the incoming connections..."<<endl;


        //Thread needs to run continuously without interrupting the main function, hence it is detached from the process
            thread connectionResolverThread([&hiveServerNodeObject, &hConsole](){
                        ConnectionResolver(hiveServerNodeObject, hConsole);
                    });
            connectionResolverThread.detach();


        //Now operator can continue the instructions
        SetConsoleTextAttribute(hConsole, _CYAN);
        char* message;
        SetConsoleTextAttribute(hConsole, _WHITE);
            while(1){
                //cout<<"Enter the order:"<<endl;
                //cin>>message;
                cout<<"Simulating work...\n";
                sleep(1);
                hiveServerNodeObject.SendOrdersToAllClients("test");

            }

        }
    }






    return 0;
}
