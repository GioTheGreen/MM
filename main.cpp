#include <thread>
#include <iostream>
#include <chrono>
#include <random>

struct Print
{
   void print(){std::cout << "Hi from thread\n";};
};
struct Charector
{
    std::string name;
    int helth = 100;
    int attack = 1;
    float douge = 0.5f;
    float attack_speed = 1.0f;
    Charector(std::string n,int h, int a, float d, float as)
    {
    name = n;
    helth = h;
    attack = a;
    douge = d;
    attack_speed = as;
    };
    void damage(int d)
    {
        helth -= d;
    };
    int hit(int a, float d)
    {
        if((d*100) >= 1 + rand()%100))
        {
            return attack;
        }
        else
        {
            return 0;
        }

    };
};
struct Loop
{
    bool HasToStop = false;

    Charector Rolfor("Rolfor(Human,Barbarian)",50,20,0.1f,1.0f);
    Charector GuardDan("GardDan(Gnome,Druid)",100,5,0.7f,2.2f);
    std::cout << Rolfor.name + " has " + Rolfor.helth + " helth";
    std::cout << GuardDan.name + " has " + GuardDan.helth + " helth";

    void run()
    {
        while(!HasToStop)
        {
            if (Rolfor.helth <=0 )
        };
        std::cout << "stop";
    };
};


int main()
{
    //Print p;
    //std::thread([&p]{
    // p.print();
    //}).join();
    srand(time(NULL));

    Loop l;
    std::thread t{&Loop::run, &l};


    std::thread([&l]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%5000));

    }).join();

    t.join();






}
