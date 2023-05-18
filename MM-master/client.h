#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <SFML/Network.hpp>
#include "queue.h"
#include "receiver.h"
#include <iostream>
#include <thread>
#include "server.h"
#include <chrono>

class client {
private:
    Queue<std::string> queue;
    Queue<myMessage> MessageQueue;
    std::shared_ptr<sf::TcpSocket> socket;//= std::make_shared<sf::TcpSocket>();
public:
    int runClient();
    bool findServer(std::shared_ptr<sf::TcpSocket>  s);
    void createServer(std::shared_ptr<sf::TcpSocket>  s);
    void sendMessage( myMessage m);
};


#endif // CLIENT_H_INCLUDED
