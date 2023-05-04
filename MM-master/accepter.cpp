#include "accepter.h"
#include "receiver.h"
#include "util.h"
#include <iostream>
#include <thread>

Accepter::Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s):
    queue_(q),
    socket_(s)
{}

void Accepter::operator()()
{
    sf::TcpListener listener;
    // TODO the listener has to listen.
    listener.listen(PORT);
    std::cout << "Bound to port\n";
    while (true)
    {
        std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
        // TODO accept a connection on socket
        listener.accept(*socket);
        socket_.push(socket);
        std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>(socket, queue_);
        // TODO launch a thread to receive with the receiver
        std::thread(&Receiver::recv_loop, receiver).detach();
    }
}

