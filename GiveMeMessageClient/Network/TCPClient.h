#pragma once
#include <WinSock2.h>

class TcpSocket;

class TCPClient
{
public:
    TCPClient();
    ~TCPClient();

    TcpSocket* Connect(const char* Address, u_short Port) const;
};
