#include "accepter.h"
#include "queue.h"
#include "list.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "server.h"

int server::runServer()
{
 std::cout << "server";
    Queue<std::string> queue;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    // TODO launch an accepter thread.
    //std::thread(Accepter(queue, sockets)).detach();

    Accepter a(queue, sockets);
    std::thread AccepterThread(&Accepter::operator(), &a);
    AccepterThread.detach();
    while(1)
    {
        std::string s = queue.pop();
        std::cout << "Main read: \"" << s << "\"\n";
        // TODO send to all in sockets. Be careful to synchronise.
        auto send_to_one = [&s] (std::shared_ptr<sf::TcpSocket> socket) {
            socket->send(s.c_str(), s.size() + 1);
        };
        sockets.for_each(send_to_one);
    }
    return 0;
}

void server::sendMessage()
{

}
