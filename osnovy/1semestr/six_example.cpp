// Work_6.cpp : Defines the entry point for the console application.
#include <conio.h>
//#include <curses.h>
#include <dos.h>
#include <bios.h>
#include <ctype.h>

int main(void)
{
    int w1x1 = 1, w1y1 = 1, w1x2 = 40, w1y2 = 24;
    int w2x1 = 41, w2y1 = 1 , w2x2 = 80, w2y2 = 24;
    int w3x1 = 1, w3y1 = 25 , w3x2 = 80, w3y2 = 25;
    int FLAG = 0;
    struct time t;
    struct date d;
    textmode(C80);
    textbackground(BLACK);
    textcolor(WHITE);
    clrscr();
    _setcursortype(_NOCURSOR);
    window(w3x1, w3y1, w3x2, w3y2);
    textattr(WHITE + (RED << 4));
    clrscr();
    gotoxy(7, 1);
    cprintf("Press: 1 – To See Left Window, 2 – To See Right Window, ESC to EXIT");
    while(FLAG != 27)
    {
        if(bioskey(1) != 0)
        {
            FLAG = toascii(bioskey(0));
        }
        gettime(&t);
        getdate(&d);
//////////////// window1 //////////////////
        if(FLAG == '1')
        {
            window(w1x1, w1y1, w1x2, w1y2);
            textbackground(BLUE);
            clrscr();
            gotoxy(17, 12);
            cprintf("%2d:%02d:%02d", t.ti_hour, t.ti_min, t.ti_sec);
            window(w2x1, w2y1, w2x2, w2y2);
            textbackground(BROWN);
            clrscr();
        }
//////////////// window2 //////////////////
        if(FLAG == '2')
        {
            window(w2x1, w2y1, w2x2, w2y2);
            textbackground(GREEN);
            clrscr();
            gotoxy(17, 12);
            cprintf("%d.%d.%d", d.da_day, d.da_mon, d.da_year);
            window(w1x1, w1y1, w1x2, w1y2);
            textbackground(BROWN);
            clrscr();
    }
        delay(500);
    }
////////////////////////////////////////////////
    textmode(LASTMODE);
    textbackground(BLACK);
    textcolor(WHITE);
    _setcursortype(_NORMALCURSOR);
    return 0;
}