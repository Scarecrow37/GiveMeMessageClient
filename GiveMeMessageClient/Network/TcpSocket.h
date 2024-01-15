#pragma once
#include <WinSock2.h>
#include <xstring>

class TcpSocket
{
public:
    TcpSocket(SOCKET Socket);

    static std::exception MakeException(const std::string& Message);

    void Send(const std::string& Message) const;
    std::string Receive() const;

private:
    SOCKET Socket;
};
