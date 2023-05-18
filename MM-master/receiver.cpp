#include "receiver.h"
#include "util.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

Receiver::Receiver(std::shared_ptr<sf::TcpSocket> s,
        Queue<std::string> &q, Queue<myMessage> &MessageQueue):
    socket_(s),
    queue_(q),
    Mqueue_(MessageQueue)
{
}

void Receiver::recv_loop()
{
    //char buffer[256];
    sf::Packet packet;
    while(1)
    {
//        std::memset(buffer, 0, 256);
//        std::size_t received;
//        // TODO receive a message here
//        socket_->receive(buffer, 256, received);
//        queue_.push(std::string(buffer));

        std::cout << "resived\n";
        packet.clear();
        std::cout << "packet cleared\n";

        if (socket_->receive(packet) != sf::Socket::Done)
        {
            std::cout << "error still\n";
        }
        std::cout << "the cat is back\n";
        myMessage* m;
        std::cout << "thing 1\n";
        packet >> *m;
        std::cout << "thing 2\n";
        packet.clear();
        std::cout << "the cat is gone\n";
        Mqueue_.push(*m);
        std::cout << "resived still\n";
    }
}

