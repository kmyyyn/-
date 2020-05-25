#include <iostream>
#include <TXLib.h>

using namespace std;

struct Ball{
    int x, y, Vx, Vy, r0;
    int r, g, b;
    int Grx0, Gry0, Grxk, Gryk;
};

Ball BallCoor( Ball jeppa );

void draw_ball( Ball jeppa );

void draw_rec( Ball jeppa);

void collide( Ball *one, Ball *two);

int main()
{
    txBegin();
    int k = 3;
    Ball jeppa[k];
    jeppa[0] = {400, 400, 5, 7, 50, 100, 100, 100, 50,  50, 500,  600};
    jeppa[1] = {500, 600, 10, 20, 30, 100, 10,  50,  50,  50, 500,  600};
    jeppa[2] = {800, 400, 7, 5,  40, 10,  100, 90,  550, 350, 1200, 600};
    int xd = 1440, yd = 720;
    txCreateWindow( xd, yd);
    while( !GetAsyncKeyState(VK_ESCAPE))
    {
        for( int i = 0; i < k; i++)
        {
            draw_rec( jeppa[i]);
        }
        collide( &jeppa[0], &jeppa[1]);
        collide( &jeppa[1], &jeppa[2]);
        collide( &jeppa[2], &jeppa[0]);
        for( int i = 0; i < k; i++)
        {
            jeppa[i] = BallCoor(jeppa[i]);
            draw_ball(jeppa[i]);
        }

        txSleep(50);
        txSetFillColor(TX_BLACK);
        txClear();
    }

    txEnd();
    return 0;
}

Ball BallCoor( Ball jeppa )
{
    jeppa.x += jeppa.Vx;
    jeppa.y += jeppa.Vy;
    if( jeppa.x-jeppa.r0 < jeppa.Grx0)
    {
        jeppa.x = 2*jeppa.Grx0 - jeppa.x + jeppa.r0*2;
        jeppa.Vx = -1*jeppa.Vx;
    }
    if( jeppa.y-jeppa.r0 < jeppa.Gry0)
    {
        jeppa.y = 2*jeppa.Gry0 - jeppa.y +jeppa.r0*2;
        jeppa.Vy = -1*jeppa.Vy;
    }
    if( jeppa.x+jeppa.r0 > jeppa.Grxk)
    {
        jeppa.x = jeppa.Grxk-(jeppa.x+jeppa.r0)%(jeppa.Grxk-jeppa.r0);
        jeppa.Vx = -1*jeppa.Vx;
    }
    if( jeppa.y+jeppa.r0 > jeppa.Gryk)
    {
        jeppa.y = jeppa.Gryk-(jeppa.y+jeppa.r0)%(jeppa.Gryk-jeppa.r0);
        jeppa.Vy = -1*jeppa.Vy;
    }

    return jeppa;
}

void draw_ball( Ball jeppa )
{
    txSetColor( RGB(jeppa.r, jeppa.g, jeppa.b));
    txSetFillColor( RGB(jeppa.r, jeppa.g, jeppa.b));
    txCircle( jeppa.x, jeppa.y, jeppa.r0);
}

void draw_rec( Ball jeppa)
{
    txSetColor( RGB(jeppa.r, jeppa.g, jeppa.b));
    txSetFillColor( TX_RED);
    txRectangle( jeppa.Grx0,jeppa.Gry0,jeppa.Grxk,jeppa.Gryk);
}

void collide( Ball *one, Ball *two)
{
    double tmp;

    double r = (one->x-two->x)*(one->x-two->x)+(one->y-two->y)*(one->y-two->y);

    double r1 = ((one->r0 + two->r0)*(one->r0 + two->r0));

    if( r <= r1)
    {

        tmp = one->Vx;
        one->Vx = two->Vx;
        two->Vx = tmp;
        tmp = one->Vy;
        one->Vy = two->Vy;
        two->Vy = tmp;
    }
}



