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
    char buffer[256];
    sf::Packet packet;
    while(1)
    {
        std::memset(buffer, 0, 256);
        std::size_t received;
        // TODO receive a message here
        socket_->receive(buffer, 256, received);
        queue_.push(std::string(buffer));

        std::cout << "resived\n";
        socket_->receive(packet);
        myMessage m;
        packet >> m;
        Mqueue_.push(m);
    }
}

