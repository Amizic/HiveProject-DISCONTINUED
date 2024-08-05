#ifndef THREADRESOLVERS_H_INCLUDED
#define THREADRESOLVERS_H_INCLUDED

#include <iostream>
#include <ColorCodes.h>

#include <windows.h>
#include <winsock2.h>


void ConnectionResolver(HiveServerNode& hiveServerNodeObject, HANDLE hConsole) {

    // Set up the timeout required for select function (if nothing is arriving on server, we still want to monitor the connections we already have and send data)
    timeval timeout;
    timeout.tv_sec = 5;  // Timeout in seconds
    timeout.tv_usec = 0;  // Timeout in microseconds
    int activity;

    while (1) {
            /*Explanation:
                For each client socket (the amount of maximum connections), check if they are equal to 0. In case they are, it means they are empty (the logic behind the code)
                After that, accept function returns FD in case connection is accepted which results that FD is bigger than zero.
                Then we have pipe write process to pass the new client info
                finally, we add newly created client to the list

                In case that client is initialized and accepted (client socket in this case returns number bigger than 0, it means connection already exists, and we can implement mechanism for heartbeat.
                Heartbeat can also be implemented in another header, which will have separate while(1), because accept() is a blocking function or it can be used with timeout (maybe better solution for more readability)
                Heartbeat is required in order to clear client sockets that are no longer being used, the ones that are disconnected or lost connection, so new clients can join/rejoin

                Checking of accept can also be implemented by using Select
            */
            for(int clientIndex=0;clientIndex<_MAX_CONNECTIONS;clientIndex++){
                //For every select (located in AcceptNewClient(clientIndex) function, it is better to clear and reset file descriptor set of sockets that are being monitored, even if the set contains only one file descriptor (server FD in this example)
                hiveServerNodeObject.ClearServerFileDescriptorSet();
                hiveServerNodeObject.AddServerSocketToFileDescriptor();
                if(hiveServerNodeObject.GetClientSocket(clientIndex)==0){
                        activity = select(0, &hiveServerNodeObject.serverFileDescriptorSet, nullptr, nullptr, &timeout);
                        if ((activity != SOCKET_ERROR)&&(activity!=0)) {
                                if(hiveServerNodeObject.AcceptNewClient(clientIndex)>0){
                                hiveServerNodeObject.AddNewClientToList(clientIndex);
                                hiveServerNodeObject.AddClientSocketToFileDescriptor(clientIndex);
                            }
                        }else{
                            SetConsoleTextAttribute(hConsole, _RED);
                            std::cout<<"No activity on the server socket or error occoured... (timeout: 5s)\n";
                            SetConsoleTextAttribute(hConsole, _WHITE);
                        }
                }
            }


    }
}

#endif // THREADRESOLVERS_H_INCLUDED
