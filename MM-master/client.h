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
public:
    int runClient();
    bool findServer(std::shared_ptr<sf::TcpSocket>  s);
    void createServer(std::shared_ptr<sf::TcpSocket>  s);
    void sendMessage();
};


#endif // CLIENT_H_INCLUDED
