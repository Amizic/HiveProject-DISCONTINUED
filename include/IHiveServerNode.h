#ifndef IHIVESERVERNODE_H_INCLUDED
#define IHIVESERVERNODE_H_INCLUDED

class IHiveServerNode{
    public:
    virtual int GetServerSocket() = 0;
    virtual int CreateServerSocket() = 0;
    virtual int CloseServerSocket() = 0;
    virtual void DefineServerIPV4(int port) = 0;
    virtual int BindServerSocket() = 0;
    virtual void Listen() = 0;
    virtual void PrepareClients() = 0;
    virtual int AcceptNewClient() = 0;
    virtual int SendOrderTest() = 0;
    virtual void ChooseFile(char* fileName) = 0;
    virtual bool ReadFile() = 0;

};

#endif // IHIVESERVERNODE_H_INCLUDED
