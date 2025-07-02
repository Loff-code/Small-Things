#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define sizeCol 100
#define sizeRow 50

int curGen[sizeRow][sizeCol];
int newGen[sizeRow][sizeCol];

int cntNeighbor(row, col)
{
    int cnt = 0;
    for (int dRow = -1; dRow < 2; dRow++)
    {
        for (int dCol = -1; dCol < 2; dCol++)
        {
            if (!(row + dRow < 0 || row + dRow >= sizeRow || col + dCol < 0 || col + dCol >= sizeCol || (dCol == 0 && dRow == 0)))
            {
                cnt += curGen[row + dRow][col + dCol];
            }
        }
    }
    return cnt;
}

int born(row, col)
{
    int neighbors = cntNeighbor(row, col);
    int alive = curGen[row][col];
    return (alive && (neighbors == 2 || neighbors == 3)) || (!alive && neighbors == 3);
}

void printBoard(void)
{

    char str[sizeRow * (sizeCol + 1) + 1];
    int cnt = 0;
    for (int row = 0; row < sizeRow; row++)
    {
        for (int col = 0; col < sizeCol; col++)
        {
            str[cnt++] = curGen[row][col] ? 219 : ' ';
        }
        str[cnt++] = '\n';
    }
    str[cnt] = '\0';
    system("clear");
    printf("%s", str);
}

void initBoard()
{
    for (int row = 0; row < sizeRow; row++)
    {
        for (int col = 0; col < sizeCol; col++)
        {
            curGen[row][col] = rand() % 2;
        }
    }
}

void generateNewGen()
{
    for (int row = 0; row < sizeRow; row++)
    {
        for (int col = 0; col < sizeCol; col++)
        {
            newGen[row][col] = born(row, col);
        }
    }
}

int next(int gen)
{
    int diff = 0;
    generateNewGen();
    for (int row = 0; row < sizeRow; row++)
    {
        for (int col = 0; col < sizeCol; col++)
        {
            diff += (curGen[row][col] != newGen[row][col]);
            curGen[row][col] = newGen[row][col];
        }
    }
    usleep(1000000 / 15);

    printBoard();
    printf("\n\nCurrent Generation: %d\n", gen);
    return diff > 0 ? next(gen++) : 0;
}

int main(int argc, char const *argv[])
{
    srand(argc > 1 ? atoi(argv[1]) : 1);
    initBoard();
    next(0);
    return 0;
}
