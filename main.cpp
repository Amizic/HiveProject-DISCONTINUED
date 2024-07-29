#include <iostream>
#include <stdio.h>
#include <HiveClientNode.h>
#include <HiveServerNode.h>

#define _SERVER_PORT 7777
#define _GREEN 10
#define _RED 12
#define _WHITE 15
#define _CYAN 11

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
        cout<<"WSAStartup failed with error: "<<error<<"\n";
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Couldnt find usable WinSock DLL */
        SetConsoleTextAttribute(hConsole, _RED);
        cout<<"Could not find version of Winsock.dll that can be used"<<"\n";
        WSACleanup();
        return -1;
    }

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTextAttribute(hConsole, _CYAN);



cout<<endl;
cout<<"                                   ███           "<<endl;
cout<<"                                        ██           "<<endl;
cout<<"                                                    "<<endl;
cout<<"                 █████           ██ █               "<<endl;
cout<<"                 ██████        ███████              "<<endl;
cout<<"                 ██████        ███████              "<<endl;
cout<<"         ████   █████████     ██ █████         ███  "<<endl;
cout<<"         ███    █████████    █████████         ████ "<<endl;
cout<<"                ██  ██████████████ ███              "<<endl;
cout<<"     █████            █████ ████            ██████  "<<endl;
cout<<"    ██████████   ██      █████     █     ██████████ "<<endl;
cout<<"     ███████████  ███████████   ████   ██████████   "<<endl;
cout<<"      ███████ ███  ██████ █ ███████  ███ █████ █    "<<endl;
cout<<"        ██████   █ ██████ █████████      ██████     "<<endl;
cout<<"         ██████  █ ████   █ █   ███ ██  █████       "<<endl;
cout<<"          ███████ ██     █████    ██ ███████        "<<endl;
cout<<"         ██ ██  █   ██████ █████   █  ██  █        "<<endl;
cout<<"          █████████    ██████    ██████████        "<<endl;
cout<<"         ████    ████         ████   ██ █         "<<endl;
cout<<"          ████ ██ ███████████████ █ █████         "<<endl;
cout<<"          ██████ ██████ █   ████ ███████          "<<endl;
cout<<"           █████  ████ █ ████████  ████           "<<endl;
cout<<"             ███  ██   ██████████ ███             "<<endl;
cout<<"               ███  █ █████      ██               "<<endl;
cout<<"       █          █ ███   █ ██  █  ██    ███      "<<endl;
cout<<"        ████   █   █████████████   █    ████      "<<endl;
cout<<"              ██ ███████   ███████ ██             "<<endl;
cout<<"             ██████ ██    ███ ██████             "<<endl;
cout<<"              ██████ █     █ ██████              "<<endl;
cout<<"             ███████       ██ ████              "<<endl;
cout<<"            █████         ████                "<<endl;
cout<<"                                            "<<endl;
cout<<"                                           "<<endl;

cout<<"|_______________/SERAPHIM_NODE_V1.4\\_______________|"<<endl;
cout<<endl<<endl;

    SetConsoleTextAttribute(hConsole, _WHITE);

    cout<<"1.Initiate client \n2.Initiate server\n3.Test reading of file (payload)\n";
    cin>>option;

    switch(option){
        //Simulate client
        case 1:
        {
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
        //Simulate server
        case 2:
            {
            HiveServerNode hiveServerNodeObject;

            hiveServerNodeObject.CreateServerSocket();
            hiveServerNodeObject.DefineServerIPV4(_SERVER_PORT);
            hiveServerNodeObject.BindServerSocket();
            hiveServerNodeObject.Listen();
            hiveServerNodeObject.AcceptNewClient();

            cout<<"Client connected!\n";


                while(1){
                    cout<<"Simulating data processing...\n";
                hiveServerNodeObject.SendOrderTest();
                }
                break;
            }

        case 3:{

            HiveServerNode hiveServerNodeObject;
            hiveServerNodeObject.ChooseFile("To test.txt");
            if(!hiveServerNodeObject.ReadFile()){
                SetConsoleTextAttribute(hConsole, _RED);
                cerr << "Failed to open the file: " << endl;
            }
            break;
        }
    }






    return 0;
}
