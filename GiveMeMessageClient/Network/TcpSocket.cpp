#include "TcpSocket.h"

#include <string>


TcpSocket::TcpSocket(const SOCKET Socket) : Socket(Socket)
{
}

void TcpSocket::Send(const std::string& Message) const
{
    const int Byte = send(Socket, Message.c_str(), static_cast<int>(Message.size()), 0);
    if (Byte < 0)
    {
        throw MakeException("Send fail.");
    }
    if (Byte == 0)
    {
        throw MakeException("Disconnected.");
    }
}

std::string TcpSocket::Receive() const
{
    char Buffer[1024] = {};
    const int Byte = recv(Socket, Buffer, sizeof(Buffer), 0);
    std::string ReceiveMessage(Buffer);
    return ReceiveMessage;
}

std::exception TcpSocket::MakeException(const std::string& Message)
{
    const DWORD ErrorCode = GetLastError();
    std::string ExceptionMessage;
    ExceptionMessage.append("[");
    ExceptionMessage.append(std::to_string(ErrorCode));
    ExceptionMessage.append("] ");
    ExceptionMessage.append(Message);
    return std::exception(ExceptionMessage.c_str());
}
