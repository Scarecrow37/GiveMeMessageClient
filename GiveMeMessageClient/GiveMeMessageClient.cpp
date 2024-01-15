#include <iostream>

#include "Network/TCPClient.h"
#include "Network/TcpSocket.h"

int main(int argc, char* argv[])
{
    const TCPClient* Client = new TCPClient();
    const TcpSocket* Socket = Client->Connect("127.0.0.1", 5001);
    Socket->Send("give me message.");
    const std::string Message = Socket->Receive();

    std::cout << Message << std::endl;
    
    return 0;
}
