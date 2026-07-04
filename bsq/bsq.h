#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct game
{
    int lines;
    char empty;
    char obs;
    char full;
    FILE f;
    int w;
    char **grid;
} game;

typedef     struct max 
{
    int r ;
    int c ;
    int b ;
} max;

#endif