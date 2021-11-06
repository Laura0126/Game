#include <stdio.h> // printf()
#include <conio.h> // getch()
#include <windows.h>
#include <stdbool.h>

#define H 30
#define W 60
#define NR_GHOSTS 20

bool meet = false;

struct coord
{
    int x;
    int y;
};

struct PacMan {
    struct coord position;
    int vx;
    int vy;
    int lives;
    bool chasing;
    int food_collected;
};

struct Ghost {
    struct coord position;
    int vx;
    int vy;
    bool chasing;
};

struct Ghost allGhosts[NR_GHOSTS];

struct PacMan myPacMan =
{
    {
        .x = 1,
        .y = 1,
    },
        .vx = 0,
        .vy = 0,
        .lives = 3,
        .chasing = false,
        .food_collected = 0
    };

char playfield[H][W] =
{
    { "############################################################" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "#      # # # # # #    # # # # # #        # # # # # #       #" },
    { "#      #              #                       #            #" },
    { "#      #              #                       #            #" },
    { "#      #              #                       #            #" },
    { "#      #              #                       #            #" },
    { "#      #              #                       #            #" },
    { "#      #              #                       #            #" },
    { "#      #              #                       #            #" },
    { "#      # # # # # #    # # # # # #        # # # # # #       #" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "#          # # # # # #           # # # # # #               #" },
    { "#          #         #           #                         #" },
    { "#          #         #           #                         #" },
    { "#          # # # # #             #                         #" },
    { "#          # #                   # # # # # #               #" },
    { "#          #   #                           #               #" },
    { "#          #     #                         #               #" },
    { "#          #       #                       #               #" },
    { "#          #         #           # # # # # #               #" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "#                                                          #" },
    { "############################################################" }
};

void initialize()
{

    // food
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            if(playfield[i][j]==' ') playfield[i][j] = '.';
        }
    }

    // ghosts
    for(int i = 0; i < NR_GHOSTS; i++)
    {
        allGhosts[i].vx = 0;
        allGhosts[i].vy = 0;
        allGhosts[i].chasing = true;

        // find food
        int x,y;
        do
        {
            x = 1 + rand() % (W-1);
            y = 1 + rand() % (H-1);

        } while (playfield[y][x] != '.');

        allGhosts[i].position.x = x;
        allGhosts[i].position.y = y;
        playfield[y][x] = 'G';

    }
}

void user_input()
{
    if(_kbhit())
    {
        char c1 = _getch();

        if(c1 == -32)
        {
            char c2 = _getch();

            myPacMan.vx = 0;
            myPacMan.vy = 0;

            switch(c2)
            {
                case 72: myPacMan.vy = -1; break; // cursor up
                case 80: myPacMan.vy = +1; break; // cursor down
                case 75: myPacMan.vx = -1; break; // cursor left
                case 77: myPacMan.vx = +1; break; // cursor right
            }
        }
    }
}

void move_figures()
{

    playfield[myPacMan.position.y][myPacMan.position.x] = ' ';

    int nx = myPacMan.vx + myPacMan.position.x;
    int ny = myPacMan.vy + myPacMan.position.y;

    if(playfield[ny][nx] == '#')
    {
        myPacMan.vx = 0;
        myPacMan.vy = 0;
    }

    myPacMan.position.x += myPacMan.vx;
    myPacMan.position.y += myPacMan.vy;

    if(playfield[ny][nx] == '.')
    {
        myPacMan.food_collected++;
    }
    else
    {
        if(playfield[ny][nx] == 'G')
        {
            meet = true;
        }
    }

    playfield[myPacMan.position.y][myPacMan.position.x] = 'P';

}

void check_for_collisions()
{

}

void show_playfield()
{
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            printf("%c", playfield[i][j]);
        }
            printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);
}

void show_gmaeoverfield()
{
    char playfield_gameover_ver[H][W] =
    {
        { "############################################################" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#              #                        #                  #" },
        { "#               #                      #                   #" },
        { "#                 #                  #                     #" },
        { "#                   # #          # #                       #" },
        { "#                 #                  #                     #" },
        { "#               #                      #                   #" },
        { "#              #                        #                  #" },
        { "#                                                          #" },
        { "#             #                          #                 #" },
        { "#            ###                        ###                #" },
        { "#           #####                      #####               #" },
        { "#          #####                        #####              #" },
        { "#          #####      ############      #####              #" },
        { "#        ######       #          #      ######             #" },
        { "#       #######       #          #      #######            #" },
        { "#       ########      ############       ########          #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "#                   ---GAME OVER---                        #" },
        { "#                                                          #" },
        { "#                                                          #" },
        { "############################################################" }
    };
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            printf("%c", playfield_gameover_ver[i][j]);
        }
        printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);

}

void set_cursor_position(int x, int y)
{

    COORD coord = {x, y};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
    system("cls");

    hidecursor();
    initialize();

    while(!meet)
    {
        user_input();
        move_figures();

        if(meet) break;

        check_for_collisions();
        show_playfield();

        Sleep( 1000 / 30 );
        set_cursor_position(0, 0);
    }

    show_gmaeoverfield();
}
