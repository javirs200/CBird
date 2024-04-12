#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define WIDTH 60
#define HEIGHT 20
#define FPS 10
#define PIPE_GAP 6

int bird_x, bird_y;
int pipe1_x, pipe1_height;
int pipe2_x, pipe2_height;
int score;

void setup()
{
    bird_x = WIDTH / 4;
    bird_y = HEIGHT / 2;
    pipe1_x = WIDTH / 2;
    pipe1_height = rand() % (HEIGHT - 3);
    pipe2_x = WIDTH - 1;
    pipe2_height = rand() % (HEIGHT - 3);
    score = 0;
}

void draw()
{
    system("cls");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == bird_x && i == bird_y)
            {
                printf("B");
            }
            else if (j == pipe1_x && (i < pipe1_height || i > pipe1_height + PIPE_GAP))
            {
                printf("|");
            }
            else if (j == pipe2_x && (i < pipe2_height || i > pipe2_height + PIPE_GAP))
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void update()
{
    // Move the bird down
    if (bird_y < HEIGHT + 1)
    {
        bird_y++;
    }
    // Move the pipes to the left
    pipe1_x--;
    pipe2_x--;
    // if imput is detected, move the bird up
    if (_kbhit())
    {
        _getch();
        bird_y -= 2;
    }

    // Check if bird is out of bounds
    if (bird_y < 0 || bird_y > HEIGHT)
    {
        setup();
    }
    else
    {
        if (pipe1_x == bird_x)
        {
            if (bird_y < pipe1_height || bird_y > pipe1_height + 3)
            {
                setup();
            }
            else
            {
                score++;
            }
        }
        else if (pipe2_x == bird_x)
        {
            if (bird_y < pipe2_height || bird_y > pipe2_height + 3)
            {
                setup();
            }
            else
            {
                score++;
            }
        }
    }

    // Check if pipes are out of bounds and reset them
    if (pipe1_x < 0) {
        pipe1_x = WIDTH - 1;
        pipe1_height = rand() % (HEIGHT - PIPE_GAP);
    }
    else if (pipe2_x < 0) {
        pipe2_x = WIDTH - 1;
        pipe2_height = rand() % (HEIGHT - PIPE_GAP);
    }
}

void game_loop()
{
    while (1)
    {
        draw();
        update();
        Sleep(1000 / FPS);
    }
}

int main()
{
    setup();
    game_loop();
    return 0;
}