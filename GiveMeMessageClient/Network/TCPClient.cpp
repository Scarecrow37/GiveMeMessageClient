#include "TCPClient.h"
#include "TcpSocket.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

TCPClient::TCPClient()
{
    WSAData WsaData;
    const int Result = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (Result < 0)
    {
        throw TcpSocket::MakeException("Winsock dll load fail.");
    }
}

TCPClient::~TCPClient()
{
    WSACleanup();
}

TcpSocket* TCPClient::Connect(const char* Address, const u_short Port) const
{
    const SOCKET Server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Server == INVALID_SOCKET)
    {
        throw TcpSocket::MakeException("Server socket is invalid.");
    }

    SOCKADDR_IN ServerSocketAddress = {};
    ServerSocketAddress.sin_family = AF_INET;
    int Result = inet_pton(AF_INET, Address, &ServerSocketAddress.sin_addr);
    if (Result != 1)
    {
        throw TcpSocket::MakeException("Address is invalid.");
    }
    ServerSocketAddress.sin_port = htons(Port);

    Result = connect(Server, reinterpret_cast<SOCKADDR*>(&ServerSocketAddress), sizeof(ServerSocketAddress));
    if (Result < 0)
    {
        throw TcpSocket::MakeException("Connection fail.");
    }

    TcpSocket* ServerSocket = new TcpSocket(Server);
    return ServerSocket;
}
