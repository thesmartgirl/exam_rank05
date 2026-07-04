#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_board(int i, int j, char board[i][j])
{
    // printf("printing...%d %d\n", i, j);
    for(int x=0; x<i; x++)
    {
        for(int y=0; y<j; y++)
        {
            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}

int count_neig(int i, int j, int h, int w, char board[h][w])
{
    int c = 0;
    for(int x=i-1; x<i+2; x++)
    {
        for(int y=j-1; y<j+2; y++)
        {
            if(x==i && y==j)
                continue;
            if (x >=0 && x<h && y>=0 && y<w )
            {
                if(board[x][y] == '0')
                    c++;
            }
        }
    }
    return c;
}

int main(int argc, char** argv)
{
    if (argc != 4)
        return(printf("wrong no of args\n"));
    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int it = atoi(argv[3]);
    char board[h][w];

    for(int x=0; x<h; x++)
        for(int y=0; y<w; y++)
            board[x][y] = ' ';
    // print_board(w, h, board);
    char buff;
    int i = 0;
    int j = 0;
    bool d = 0;
    while (read( 0, &buff, 1) == 1)
    {
        if (buff == 'w')
        {
            if(i>0)
                i--;
        }
        else if (buff == 's')
        {
            if(i<h-1)
                i++;
        }
        else if(buff == 'a')
        {
            if(j>0)
                j--;
        }
        else if(buff =='d')
        {
            if(j<w-1)
                j++;
        }
        else if(buff == 'x')
            d = !d;
        else if(buff == '\n')
            continue;
        else
            return(printf("invalid input\n"));

        if(d && i>=0 && i<h && j>=0 && j<w)
        {
            // printf("%d %d\n",i , j);
            board[i][j] = '0';
        }
        // else
        //     board[i][j] = ' ';


    }

    int q = 0;
    while (q < it)
    {
        char tmp[h][w];

                
        for(int i = 0; i < h; i++) //rows
            for(int j = 0; j < w; j++) //col
            {
                int n = count_neig(i, j, h, w, board);
                if (board[i][j] == '0')
                {
                    if (n==2 || n==3)
                        tmp[i][j] = '0';
                    else 
                        tmp[i][j] = ' ';
                }
                else {
                    if (n == 3)
                        tmp[i][j] = '0';
                    else
                        tmp[i][j] = ' ';
                }
            }

        for(int i = 0; i < h; i++) //rows
            for(int j = 0; j < w; j++) //col
                board[i][j] = tmp[i][j];
        q++;
    }
    print_board(h, w, board);


}