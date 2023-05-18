#include "client.h"

int client::runClient()
{
    socket = std::make_shared<sf::TcpSocket>();
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

    Receiver receiver(socket, queue, MessageQueue); // create receiver

    std::thread(&Receiver::recv_loop, &receiver).detach();

    std::string s = "";


    //put game initialtion here



    while (1)
    {


        //put game loop here
        //std::cout << "loop\n";
//        std::getline(std::cin, s);
//        //s = "cats";
//        //Packet packet;
//        //packet << s;
//        //socket.send(packet);
//        std::cout << "Sending: \"" << s << "\"" << std::endl;
//        // TODO send messages to the server ... status
//        socket->send(s.c_str(), s.size() + 1);
        //std::cout << "loopc\n";
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
void client::sendMessage(myMessage m)
{
    //std::cout << "nobody cats\n";
    sf::Packet p;
    p.clear();
    //std::cout << "nobody\n";
     const myMessage mes = m;
    p << mes;
    //std::cout << "cats\n";
    socket->send(p);
    p.clear();
    //std::cout << "everybody cats\n";
    //sf::Socket::Status stat= ;
    //if  (stat != sf::Socket::Status::Done) std::cout<< "Send Message error";
    //else std::cout<< "no error";
//    auto send_to_one = [&p] (std::shared_ptr<sf::TcpSocket> socket)
//    {
//        socket->send(p);
//    };
//    sockets.for_each(send_to_one);
}
