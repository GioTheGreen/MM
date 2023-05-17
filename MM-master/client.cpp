#include "client.h"

int client::runClient()
{
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
    if (!findServer(socket))        //try to find server, if find connect to it
    {
        createServer(socket);       //if not server, create server
        bool t = 0;
        while(!t)
        {
            t = findServer(socket); // join server you created
        }
    }

    std::cout << "Connected\n";

    Receiver receiver(socket, queue); // create receiver
    std::thread(&Receiver::recv_loop, &receiver).detach();
    std::string s = "";



    //put game initialtion here



    while (1)
    {


        //put game loop here

        std::getline(std::cin, s);
        //Packet packet;
        //packet << s;
        //socket.send(packet);
        std::cout << "Sending: \"" << s << "\"" << std::endl;
        // TODO send messages to the server ... status
        socket->send(s.c_str(), s.size() + 1);

    }
    return 0;
}
bool client::findServer(std::shared_ptr<sf::TcpSocket> s)
{
    //std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
    sf::Socket::Status status = s->connect(sf::IpAddress::getLocalAddress(), PORT);
    if (status == sf::Socket::Done)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void client::createServer(std::shared_ptr<sf::TcpSocket> socket)
{
    std::cout << "create";
    server s;
        std::thread ServerThread(&server::runServer, &s);
        ServerThread.detach();
}
void client::sendMessage()
{

}
