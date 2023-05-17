#ifndef MYMESSAGE_H_INCLUDED
#define MYMESSAGE_H_INCLUDED
#include <SFML/Network.hpp>
struct myMessage
{
    int Player;
    int posX;
    int posY;
    float angle;
    float speed;
    int lap;
    bool started;


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
