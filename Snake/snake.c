#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    START
};
int sizeX = 40;
int sizeY = 20;
int direction = START;
int length = 3;
int dead = 0;
int x = 7, y = 5;
typedef struct
{
    char shape;
    int x;
    int y;
} Snake;

void initSnake(Snake *snake)
{
    snake[0].shape = 'O';
    snake[0].x = 7;
    snake[0].y = 5;
    for (size_t i = 1; i < 100; i++)
    {
        snake[i].shape = '*';
        snake[i].x = snake[i - 1].x - 1;
        snake[i].y = snake[i - 1].y;
    }
}
void initPoint(Snake *point)
{
    point->shape = '+';
    point->x = 17;
    point->y = 5;
}

void moveSnake(Snake *snake)
{
    if (!dead && direction != START)
    {
        for (size_t i = length; i > 0; i--)
        {
            snake[i].x = snake[i - 1].x;
            snake[i].y = snake[i - 1].y;
        }
        snake[0].x = x;
        snake[0].y = y;
        snake[0].shape = 'O';
    }
}
void spawnPoint(Snake *snake, Snake *point)
{
    if (snake[0].x == point->x && snake[0].y == point->y)
    {
        if (length < 99)
        {
            length++;
        }
        point->x = rand() % (sizeX) + 1;
        point->y = rand() % (sizeY) + 1;
    }
}

void drawGame(Snake *snake, Snake point, char *text)
{
    for (int x = 0; x <= sizeX; ++x)
    {
        mvaddch(0, x, '-');
        mvaddch(sizeY + 1, x, '-');
    }
    for (int y = 0; y <= sizeY; ++y)
    {
        mvaddch(y, 0, '|');
        mvaddch(y, sizeX + 1, '|');
    }

    if (dead)
    {
        for (size_t i = 0; text[i]; i++)
        {
            mvaddch(5, 5 + i, text[i]);
        }
        direction = START;
    }
    else
    {
        for (size_t i = 0; i <= length; i++)
        {
            mvaddch(snake[i].y, snake[i].x, snake[i].shape);
        }
    }

    mvaddch(point.y, point.x, point.shape);
}
void checkDeath(Snake *snake)
{
    if (direction != START && !dead)
    {
        for (size_t i = 1; i <= length; i++)
        {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            {
                dead = 1;
                break;
            }
        }
    }
}

int main(void)
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    Snake snake[100];
    initSnake(snake);

    Snake point;
    initPoint(&point);

    char text[] = "You're dead";

    int ch;
    while ((ch = getch()) != 'q')
    {
        switch (ch)
        {
        case KEY_LEFT:
            if (direction != RIGHT)
            {
                direction = LEFT;
            }
            break;
        case KEY_RIGHT:
            if (direction != LEFT)
            {
                direction = RIGHT;
            }
            break;
        case KEY_UP:
            if (direction != DOWN)
            {
                direction = UP;
            }
            break;
        case KEY_DOWN:
            if (direction != UP)
            {
                direction = DOWN;
            }
            break;
        }

        switch (direction)
        {
        case LEFT:
            x = x > 1 ? x - 1 : sizeX;
            break;
        case RIGHT:
            x = x < sizeX ? x + 1 : 1;
            break;
        case UP:
            y = y > 1 ? y - 1 : sizeY;
            break;
        case DOWN:
            y = y < sizeY ? y + 1 : 1;
            break;
        default:
            break;
        }

        moveSnake(snake);
        spawnPoint(snake, &point);
        checkDeath(snake);
        clear();
        drawGame(snake, point, text);
        refresh();
        napms(direction == UP || direction == DOWN ? 150 : 100);
    }

    endwin();
    return 0;
}
