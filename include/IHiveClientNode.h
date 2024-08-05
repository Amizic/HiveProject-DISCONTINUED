#ifndef IHIVECLIENTNODE_H_INCLUDED
#define IHIVECLIENTNODE_H_INCLUDED

class IHiveClientNode{
    public:
    virtual int CreateClientSocket() = 0;
    virtual void CloseClientSocket() = 0;
    virtual int GetClientSocket() = 0;
    virtual void DefineServerIPV4(int port) = 0;
    virtual int ConnectToServer() = 0;
    virtual int SendDataToServer(const char* Data) = 0;
    virtual void ReadDataFromServer() = 0;
    virtual ~IHiveClientNode() {}

};

#endif // IHIVECLIENTNODE_H_INCLUDED
