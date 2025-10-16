#include <math.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

#include "f(x).h"

void color(int);
void gotoxy(int, int);
void draw(float size);
float f(float x);

int main() {
    color(9);
    printf("Hello, I wanted to give you some instructions!");
    getch();
    printf("\nOkay, you have to zoom out as furthest you can in your console (Ctrl -)");
    getch();
    printf("\nThank you!");
    system("cls");

    /*
       Added that because there's not an actual way to change character size
       windows cmd, so the user or programmer has to zoom out himself because
       the program isn't able to.
    */

    draw(0.2); // Main size of plane
    getch();
    return 0;
}

void draw(float size) {
    const int margin = 5; // Margin left and right for the square
    const int graph_size_y = 300; // Size in visible characters
    const int graph_size_x = 500; // Size in visible characters

    // Just checking for corner position

    color(9);
    gotoxy(margin*2, margin); printf("DOT");
    gotoxy(margin*2, graph_size_y); printf("DOT");
    gotoxy(graph_size_x*2, margin); printf("DOT");
    gotoxy(graph_size_x*2, graph_size_y); printf("DOT");

    // Drawing the x, y center lines with the color gray
    color(8);
    for(int i = margin*2; i < graph_size_x*2; i+=2) {
        gotoxy(i, graph_size_y/2);
        printf("%c%c", 219, 219);}
    for(int i = margin; i < graph_size_y; i++) {
        gotoxy(graph_size_x, i);
        printf("%c%c", 219, 219);}

    color(15);
    for(float x = -(graph_size_x/2) + margin; x < graph_size_x/2; x += 0.02) { // Size in x divided by 2
        float y = graph_size_y/2 - 2*f(size*x/2)/size; // The "graph_size_y/2" starts it from the center

        if(y > margin && y < graph_size_y) { // This condition sets limits of showing the function on plane
            gotoxy(2*x /*This cancels the previous divition by 2*/ + graph_size_x, y);
            printf("%c%c", 219, 219); // Prints something like a pixel on screen
        }
    }

    // The input loop
    while(TRUE) {
        // Simple input catcher
        if(kbhit()) {
            char c = getch();

            // Here they are, the zoom in and zoom out functionalities
            if(c == 43/*-*/ && size > 0.5) {system("cls"); draw(size-0.2);} else if(c == 43 && size <= 0.5) {system("cls"); draw(size/2);}
            if(c == 45/*+*/ && size) {system("cls"); draw(size+0.2);}
        }
    }
}

// Color function used for the lines and the graph
void color(int n) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, n);
}

// Gotoxy function used as a 'character position selecter' or a 'position' function
void gotoxy(int x, int y) {
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}