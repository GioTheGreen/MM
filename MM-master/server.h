#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include "util.h"
#include "accepter.h"
#include "queue.h"
#include "list.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

class server {
private:
    Queue<myMessage> MessageQueue;
    const float OffsetFromPredicted {0.0f}; // futre implemtation
    List<std::shared_ptr<sf::TcpSocket>> sockets;

public:
    int runServer();
    void sendMessage(List<std::shared_ptr<sf::TcpSocket>> sockets, myMessage m);
};

#endif // SERVER_H_INCLUDED
