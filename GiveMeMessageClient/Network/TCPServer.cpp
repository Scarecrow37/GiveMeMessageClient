#include "TCPServer.h"
#include "TcpSocket.h"

#include <exception>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer() : ListenSocket(INVALID_SOCKET)
{
    WSAData WsaData;
    const int Result = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (Result < 0)
    {
        throw TcpSocket::MakeException("Winsock dll load fail.");
    }
}

TcpServer::~TcpServer()
{
    WSACleanup();
}

void TcpServer::Initialize()
{
    ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET)
    {
        throw TcpSocket::MakeException("Listen socket is invalid.");
    }
}

void TcpServer::Bind(const u_short Port) const
{
    SOCKADDR_IN Address = {};
    Address.sin_family = AF_INET;
    Address.sin_addr.s_addr = ADDR_ANY;
    Address.sin_port = htons(Port);

    const int Result = bind(ListenSocket, reinterpret_cast<sockaddr*>(&Address), sizeof(Address));
    if (Result < 0)
    {
        throw TcpSocket::MakeException("Bind fail.");
    }
}

void TcpServer::Listen(const int Backlog) const
{
    const int Result = listen(ListenSocket, Backlog);
    if (Result < 0)
    {
        throw TcpSocket::MakeException("Listen fail.");
    }
}

TcpSocket* TcpServer::Accept() const
{
    SOCKADDR_IN Address;
    int AddressLength = sizeof(Address);
    const SOCKET Client = accept(ListenSocket, reinterpret_cast<sockaddr*>(&Address), &AddressLength);
    if (Client == INVALID_SOCKET)
    {
        throw TcpSocket::MakeException("Accept socket is invalid.");
    }
    TcpSocket* ClientSocket = new TcpSocket(Client);
    return ClientSocket;
}

