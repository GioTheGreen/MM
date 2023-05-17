#ifndef ACCEPTER_HPP
#define ACCEPTER_HPP
#include "myMessage.h"
#include "queue.h"
#include "list.h"
#include <SFML/Network.hpp>

class Accepter {
    private:
        Queue<std::string>& queue_;
        List<std::shared_ptr<sf::TcpSocket>>& socket_;
        Queue<myMessage>& Mqueue_;
    public:
        Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s,Queue<myMessage>& myM );
        void operator()();
};


#endif
