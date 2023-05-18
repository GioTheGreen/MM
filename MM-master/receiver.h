#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "myMessage.h"
#include "queue.h"
#include <SFML/Network.hpp>

class Receiver {
    public:
        Receiver(std::shared_ptr<sf::TcpSocket> s, Queue<std::string>& q, Queue<myMessage>& MessageQueue);
        void recv_loop();
    private:
        std::shared_ptr<sf::TcpSocket> socket_;
        Queue<std::string> &queue_;
        Queue<myMessage> &Mqueue_;
        int players{0};

        };
#endif
