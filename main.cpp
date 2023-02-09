#include <thread>
#include <iostream>
#include <chrono>
#include <random>

struct Print
{
   void print(){std::cout << "Hi from thread\n";};
};
struct Loop
{
    bool HasToStop = false;
    void run()
    {
        while(!HasToStop)
        {
            //do nothing
        };
        std::cout << "stop";
    };
};
struct Charector
{
    int helth = 100;
    void damage(int d)
    {

    };
};

int main()
{
    //Print p;
    //std::thread([&p]{
    // p.print();
    //}).join();

    Loop l;
    std::thread t{&Loop::run, &l};

    std::thread([&l]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%5000));
        l.HasToStop = true;
    }).join();

    t.join();

}
