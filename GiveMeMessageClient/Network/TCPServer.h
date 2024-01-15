#pragma once
#include <exception>
#include <string>
#include <WinSock2.h>

#include "TcpSocket.h"

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    void Initialize();
    void Bind(u_short Port) const;
    void Listen(int Backlog = 1) const;
    TcpSocket* Accept() const;

private:
    SOCKET ListenSocket;
};
