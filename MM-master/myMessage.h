#ifndef MYMESSAGE_H_INCLUDED
#define MYMESSAGE_H_INCLUDED
#include <SFML/Network.hpp>
struct myMessage
{
    int Player{0};
    int posX{0};
    int posY{0};
    float angle{0};
    float speed{0};
    int lap{0};
    bool started{0};


    //friend sf::Packet operator <<(sf::Packet & packet, const myMessage&m);
    //friend sf::Packet operator >>(sf::Packet & packet, myMessage &m);


    friend sf::Packet& operator <<(sf::Packet& packet, const myMessage& m)
    {
        return packet << m.Player << m.posX << m.posY << m.angle << m.speed << m.lap << m.started;
    }

    friend sf::Packet& operator >>(sf::Packet& packet, myMessage& m)
    {
        return packet >> m.Player >> m.posX >> m.posY >> m.angle >> m.speed >> m.lap >> m.started;
    }

};


#endif // MYMESSAGE_H_INCLUDED
