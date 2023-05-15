#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <cmath>
#include <iostream>
#include <thread>
#include "server.h"
#include "client.h"
using namespace sf;

const int num=8; //checkpoints
// TODO: use checkpoint to make sure we are on the track.
// Slow speed when not on the track.
int points[num][2] = {300, 610,
    1270,430,
    1380,2380,
    1900,2460,
    1970,1700,
    2550,1680,
    2560,3150,
    500, 3300};

struct Car
{
    float x,y,speed,angle, acceleration;
    int n, lap;
    Vector2f bTL,bTR,bBL,bBR;
    Car() {speed=2; angle=0; n=0; lap = 0; bTL = Vector2f(2.0f,2.0f); bTR = Vector2f(40.0f,2.0f); bBL = Vector2f(2.0f,42.0f); bBR = Vector2f(40.0f,42.0f);}
    void move()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }
    void findTarget()
    {
        float tx=points[n][0];
        float ty=points[n][1];
        float beta = angle-atan2(tx-x,-ty+y);
        if (sin(beta)<0) angle+=0.005*speed; else angle-=0.005*speed;
        // Check if passed a checkpoint
        if ((x-tx)*(x-tx)+(y-ty)*(y-ty)<25*25) n=(n+1)%num; // TODO: simplify
    }
    void respawn()
    {

    }
};

int main()
{
    // ****************************************


    //create a client
    //look for a server
    //    join server
    //if not create server
    //


    client c;
    std::thread clientThread(&client::runClient, &c);
    clientThread.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

//    ServerThread.join();
//    clientThread.join();


    // Initialise
    srand(time(NULL));
    RenderWindow app(VideoMode(640, 480), "Car Racing Game!");
    RectangleShape checkPoint1(sf::Vector2f(40.f, 5.f));
    //Checkpoint 1
    checkPoint1.rotate(30.f);
    checkPoint1.setPosition(Vector2f(300.f, 610.f));
    checkPoint1.setFillColor(sf::Color::Blue);
    app.setFramerateLimit(60);
    Texture t1,t2;
    Image hitImage;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/car.png");
    hitImage.loadFromFile("images/b_hit.png");
    Color cTrack{0,0,0};// (0 0 0) is the road
    Color cBump{255,255,255};// (255 255 255) is the bumps
    Color cWater{0,36,222};// (0 36 222) is death soup
    Color cWall{0,182,0};// (0 182 0) is wall
    // (...) is checkpoint 1
    // (...) is checkpoint 2
    // (...) is checkpoint 3
    // (...) is checkpoint 4
    //...
    t1.setSmooth(true);
    t2.setSmooth(true);
    Sprite sBackground(t1), sCar(t2);
    sBackground.scale(2,2);
    sCar.setOrigin(22, 22);
    float R=22;
    const int N=5;
    Car car[N];
    Color colors[5] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

    //Color col = hitImage.getPixel(0,0); // THIS IS THE KEY TO COLLITION DETECTIOM FROM THE IMAGE

    for(int i=0;i<N;i++)// Starting positions
    {
        car[i].x=300+i*50;
        car[i].y=1700+i*80;
        car[i].speed=7+((float)i/5);
    }

    float speed=0,angle=0;
    float maxSpeed=12.0;
    float acc=0.2, dec=0.3;
    float turnSpeed=0.08;
    int offsetX=0,offsetY=0;


    // ****************************************
    // Loop
    const Vector2f TR{40,2};  // values of weel locations at angle = 0
    const Vector2f TL{2,2};
    const Vector2f BR{40,42};
    const Vector2f BL{2,42};

    Color cW[4]; // hitImage value of weel locations
    int waterHits;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))   //it apears to be a loop
        {
            if (e.type == Event::Closed)
                app.close();
        }

        bool Up=0,Right=0,Down=0,Left=0;               // client input
        if (Keyboard::isKeyPressed(Keyboard::Up))    Up=1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) Right=1;
        if (Keyboard::isKeyPressed(Keyboard::Down))  Down=1;
        if (Keyboard::isKeyPressed(Keyboard::Left))  Left=1;

        sf::Transform transformWeel;                              // rotate weels by angle
        transformWeel.rotate((car[0].angle)*180/3.141593, 22,22);
        car[0].bTR =transformWeel.transformPoint(TR);
        car[0].bTL =transformWeel.transformPoint(TL);
        car[0].bBR =transformWeel.transformPoint(BR);
        car[0].bBL =transformWeel.transformPoint(BL);

        cW[0] = hitImage.getPixel((car[0].x + car[0].bTR.x - 22)/2,(car[0].y+ car[0].bTR.y - 22)/2); //get colour of hitImage from weel locations
        cW[1] = hitImage.getPixel((car[0].x + car[0].bTL.x - 22)/2,(car[0].y+ car[0].bTL.y - 22)/2);
        cW[2] = hitImage.getPixel((car[0].x + car[0].bBR.x - 22)/2,(car[0].y+ car[0].bBR.y - 22)/2);
        cW[3] = hitImage.getPixel((car[0].x + car[0].bBL.x - 22)/2,(car[0].y+ car[0].bBL.y - 22)/2);
        //std::cout << (int)cW[0].r << " " << (int)cW[0].g << " " << (int)cW[0].b <<std::endl;     //test for hitmap colour
        if (cW[0] == cWater) std::cout << "soup" << std::endl;
        if (cW[0] == cWall) std::cout << "wall" << std::endl;
        if (cW[0] == cTrack) std::cout << "track" << std::endl;
        if (cW[0] == cBump) std::cout << "bump" << std::endl;

        waterHits = 0;   //check for the soup
        for (int i=0;i<4;i++)
        {
            if (cW[i] == cWater) waterHits++;

            if (cW[i] == cWall)  //wall collion
            {
                bool b_top{false};
                bool b_right{false};
                switch (i)
                {
                    case 0:
                        if (car[0].bTR.x > 0) b_right = true;
                        if (car[0].bTR.y < 0) b_top = true;
                        break;
                    case 1:
                        if (car[0].bTL.x > 0) b_right = true;
                        if (car[0].bTL.y < 0) b_top = true;
                        break;
                    case 2:
                        if (car[0].bBR.x  > 0) b_right = true;
                        if (car[0].bBR.y  < 0) b_top = true;
                        break;
                    case 3:
                        if (car[0].bBL.x  > 0) b_right = true;
                        if (car[0].bBL.y  < 0) b_top = true;
                        break;
                }
                if (b_top) car[0].y -= 3;
                if (!b_top) car[0].y += 3;
                if (b_right) car[0].x -= 3;
                if (!b_right) car[0].x += 3;
                break;
            };
        }
        if (waterHits > 1) car[0].respawn();



        if (Up && speed<maxSpeed) //speed manager
        {
            if (speed < 0)  speed += dec;
            else  speed += acc;
        }
        if (Down && speed>-maxSpeed)
        {
            if (speed > 0) speed -= dec;
            else  speed -= acc;
        }
        if (!Up && !Down)
        {
            if (speed - dec > 0) speed -= dec;
            else if (speed + dec < 0) speed += dec;
            else speed = 0;
        }
        if (Right && speed!=0)  angle += turnSpeed * speed/maxSpeed;
        if (Left && speed!=0)   angle -= turnSpeed * speed/maxSpeed;
        car[0].speed = speed;
        car[0].angle = angle;
        for(int i=0;i<N;i++) car[i].move();
        for(int i=1;i<N;i++) car[i].findTarget();
        //collision
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if (i == j)
                {
                    break;
                }
                int dx=0, dy=0;
                while (dx*dx+dy*dy<4*R*R)
                {
                    car[i].x+=dx/10.0;
                    car[i].y+=dy/10.0;
                    car[j].x-=dx/10.0;
                    car[j].y-=dy/10.0;
                    dx = car[i].x-car[j].x;
                    dy = car[i].y-car[j].y;
                    if (!dx && !dy)
                        break;
                }
            }
        }
        // Render
        app.clear(Color::White);

        if (car[0].x>320) offsetX = std::min(car[0].x-320,2880.f-640);
        if (car[0].y>240) offsetY = std::min(car[0].y-240,3648.f-480);
        //if (car[0].x>320) offsetX = car[0].x-320;
        //if (car[0].y>240) offsetY = car[0].y-240;
        //offsetX = min(car[0].x-320,2880-400)
        //offsetY = min(car[0].y-240,3648-300)
        sBackground.setPosition(-offsetX,-offsetY);
        app.draw(sBackground);
        checkPoint1.setPosition(-offsetX+300,-offsetY+610);
        app.draw(checkPoint1);
        for(int i=0;i<N;i++)
        {
            sCar.setPosition(car[i].x-offsetX,car[i].y-offsetY);
            sCar.setRotation(car[i].angle*180/3.141593);
            sCar.setColor(colors[i]);
            app.draw(sCar);
        }
        app.display();
    }

    return 0;
}
