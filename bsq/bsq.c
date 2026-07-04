#include "bsq.h"
bool valid_char(char *line, game *g)
{
    int i = 0;
    while( line[i] != '\n')
    {
        if( line[i]!=g->empty && line[i]!=g->full && line[i]!=g->obs )
            return 0;
        i++;
    }
    return 1;
}

bool identical(game *g)
{
    if ( g->empty==g->full || g->empty==g->obs || g->full==g->obs )
        return 1;
    return 0;
}

bool valid_map(FILE *f, game *g)
{
    size_t size = 0;
    ssize_t nread;
    g->grid = calloc(g->lines,  sizeof(char*));
    g->w = 0;
    int l = 0;

    if( identical(g) )
        return (printf("Error: identical char\n"), 0);
    
    while (l < g->lines) {
        nread = getline(&g->grid[l], &size, f);
        if (!g->w)
            g->w = nread;
        if( nread != g->w )
            return (printf("Error: line len\n"), 0);
        if( !valid_char(g->grid[l], g) )
            return (printf("Error: line char err\n"), 0);
        l++;
    }

    if(g->w == 0)
        return (printf("Error: line len\n"), 0);
    if(g->lines == 0 || g->lines != l)
        return (printf("Error: line count\n"), 0);

    return 1;
}

int min3( int x1, int x2, int x3 )
{
    if ( x1<=x2 && x1<=x3 )
        return x1;
    if ( x2<=x1 && x2<=x3 )
        return x2;
    if ( x3<=x1 && x3<=x2 )
        return x3;
    return x1;
}

void bsq(game *g)
{
    max m;
    m.b=0;
    m.r=0;
    m.c=0;

    int dp[g->lines][g->w];
    for ( int i = 0; i < g->lines; i++ )
    {
        for( int j = 0; j < g->w; j++ )
        {
            if ( g->grid[i][j] == g->obs )
                dp[i][j] = 0;
            else if ( i==0 || j== 0)
                dp[i][j] = 1;
            else 
                dp[i][j] = 1 + min3( dp[i-1][j],
                               dp[i][j-1],
                               dp[i-1][j-1] ); 
            if ( dp[i][j] > m.b )
            {
                m.b = dp[i][j];
                m.r = i;
                m.c = j;
            }
        }
    }

    for ( int i = 0; i < g->lines; i++ )
    {
        for( int j = 0; j < g->w; j++ )
        {
            if( (i >= m.r - m.b + 1 ) && (j >= m.c - m.b + 1) && i <= m.r && j <= m.c )
                printf("%c", g->full);
            else 
                printf("%c", g->grid[i][j]);
        }
    }
}

void free_map(game *g)
{
    for ( int i = 0; i < g->lines; i++ )
        free(g->grid[i]);
    free(g->grid);
}

int main (int argc, char** argv)
{
    game g;
    if (argc == 1)
    {
        if ( fscanf(stdin, "%d %c %c %c ", &g.lines, &g.empty, &g.obs, &g.full) !=4 )
            return(printf("Error: fscanf err\n"));
                
        if (!valid_map(stdin, &g))
            return(printf("hi: map validation err\n"));

        bsq(&g);
        free_map(&g);
    }
    else if (argc == 2)
    {
        FILE *f = fopen(argv[1], "r");
        if (!f)
            return(printf("Error: file err\n"));
        if ( fscanf(f, "%d %c %c %c ", &g.lines, &g.empty, &g.obs, &g.full) !=4 )
            return(printf("Error: fscanf err\n"));
        if (!valid_map(f, &g))
            return(printf("Error: map validation err\n"));
        bsq(&g);
        free_map(&g);
        fclose(f);
    }
    else
        return(printf("worng no of args\n"));
    return 0;
}