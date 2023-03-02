#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <SFML/Network.hpp>
#include <queue>

void server()
{
    std::queue<sf::Packet> Queue;

    unsigned short port = 4300;
    sf::TcpListener listener;
    sf::Socket::Status status = sf::Socket::Disconnected;
    while (status != sf::Socket::Done)
    {

        status = listener.listen(port);

        if(status != sf::Socket::Done)
        {
            std::cout << "Error listening\n";
            port++;
        }
    }

    // Create queue
    // Create list

    // Create acceptor thread (needs to know queue and list)

    // Loop
    // get message from queue
    // send message to everyone in list



    for (int i = 0; i < 2; i++)
    {
        // Make socket a pointer
        sf::TcpSocket socket;
        status = listener.accept(socket);
        if(status != sf::Socket::Done)
        {
            std::cout << "Error accepinging\n";
            return;
        }
        // TODO: create a thread with *socket; needs to know what queue of messages we are using
        // Add *socket to a list of *sockets
        // Thread
        sf::Packet packet;
        status = socket.receive(packet);
        if(status != sf::Socket::Done)
        {
            std::cout << "Error reciving\n";
            return;
        }
        std::string message;
        Queue.push(packet);
        Queue.front() >> message;
        Queue.pop();
        std::cout << message << std::endl;
        packet.clear();
        packet << "message received";
        status = socket.send(packet);
        if(status != sf::Socket::Done)
        {
            std::cout << "Error sending\n";
            return;
        }
    }
}

void client()
{
    sf::TcpSocket socket;
    sf::IpAddress adress("localhost");
    sf::Socket::Status status = sf::Socket::Disconnected;
    unsigned short port = 4300;

    while(status != sf::Socket::Done)
    {
        status = socket.connect(adress,port);
        if(status != sf::Socket::Done)
        {
            std::cout << "Error conneting\n";
            port++;
        }
        std::cout << port;
    }
    sf::Packet packet;
    packet << "I am vengence";
    status = socket.send(packet);
    if(status != sf::Socket::Done)
    {
        std::cout << "Error sending 1\n";
        return;
    }
    packet.clear();
    status = socket.receive(packet);
    if(status != sf::Socket::Done)
    {
        std::cout << "Error reciving\n";
        return;
    }
    std::string message;
    packet >> message;
    std:: cout << message;


}

int main()
{
    std::thread serverThread(&server);
    std::thread clientThread(&client);
    client();
    serverThread.join();
    clientThread.join();
    return 0;




}
