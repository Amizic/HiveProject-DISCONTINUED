#ifndef IHIVESERVERNODE_H_INCLUDED
#define IHIVESERVERNODE_H_INCLUDED

class IHiveServerNode{
    public:
    virtual SOCKET GetServerSocket() = 0;
    virtual SOCKET GetClientSocket(int clientIndex) = 0;
    virtual SOCKET CreateServerSocket() = 0;
    virtual int SetSocketOptions() = 0;
    virtual int CloseServerSocket() = 0;
    virtual void DefineServerIPV4(int port) = 0;
    virtual int BindServerSocket() = 0;
    virtual int Listen() = 0;
    virtual void PrepareClients() = 0;
    virtual SOCKET AcceptNewClient(int clientIndex)=0;
    virtual void AddNewClientToList(int clientIndex) = 0;
    virtual int SendOrder(const char*) = 0;
    virtual int SendOrderTest() = 0;
    virtual void ChooseFile(char* fileName) = 0;
    virtual bool ReadFile() = 0;
    virtual void SendOrdersToAllClients(char* message) = 0;
    virtual void ClearServerFileDescriptorSet() = 0;
    virtual void ClearClientFileDescriptorSet() = 0;
    virtual void AddServerSocketToFileDescriptor() = 0;
    virtual void AddClientSocketToFileDescriptor(int clientIndex) = 0;

};

#endif // IHIVESERVERNODE_H_INCLUDED
