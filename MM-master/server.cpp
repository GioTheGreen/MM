
#include "server.h"

int server::runServer()
{
    //List<std::shared_ptr<sf::TcpSocket>> sockets;
    // TODO launch an accepter thread.
    //std::thread(Accepter(queue, sockets)).detach();
    Queue<std::string> q;
    Accepter a(q, sockets, MessageQueue);
    std::thread AccepterThread(&Accepter::operator(), &a);

    AccepterThread.detach();

    //int alpha = 0;

    while(1)
    {

        myMessage* mes;
        if (MessageQueue.lenght() > 0)
        {
            MessageQueue.pop(*mes);
            //mes.angle = alpha;
            //alpha++;
            //MessageQueue.pop(mes);
            std::cout << "info: " << sockets.lenght() << std::endl;
        }

//        std::string s;
//        s ="sad";
//        q.pop(s);
//        std::cout << "Main read: \"" << s << "\"\n";
        // TODO send to all in sockets. Be careful to synchronise.
//        auto send_to_one = [&s] (std::shared_ptr<sf::TcpSocket> socket)
//        {
//            socket->send(s.c_str(), s.size() + 1);
//        };
//        sockets.for_each(send_to_one);
        //std::cout << "loopend\n";



    }
    return 0;
}

void server::sendMessage(List<std::shared_ptr<sf::TcpSocket>> sockets,myMessage m)
{
    sf::Packet p;
    p << m;
    //socket->send();
    auto send_to_one = [&p] (std::shared_ptr<sf::TcpSocket> socket)
    {
        socket->send(p);
    };
    sockets.for_each(send_to_one);
}
