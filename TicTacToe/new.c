#include <stdio.h>
#include <stdlib.h>

#define len 3 * 3 + 4
#define len2 3

char table[len][len];
char playTable[len2][len2];
int num;

void checkWin(char player)
{
    char checker[3];
    char real[3];
    for (size_t i = 0; i < len2; i++)
    {
        checker[i] = player;
    }

    int hori;
    int vert;
    int dia1;
    int dia2;

    for (size_t row = 0; row < len2; row++)
    {
        hori = 0;
        vert = 0;
        if (playTable[row][row] == player)
        {
            dia1++;
        }

        if (playTable[2 - row][row] == player)
        {
            dia2++;
        }
        for (size_t col = 0; col < len2; col++)
        {
            if (playTable[row][col] == player)
            {
                hori++;
            }
            if (playTable[col][row] == player)
            {
                vert++;
            }
        }
        if (hori == 3 || vert == 3)
        {
            printf("Player %c WON!\n", player);
            exit(0);
        }

        printf("Hori: %d, Vert: %d, num: %d\n", hori, vert, row);
    }
    if (dia1 == 3 || dia2 == 3)
    {
        printf("Player %c WON!\n", player);
        exit(0);
    }
}

void play(char player)
{
    int field;
    printf("You are player: %c\n", player);
    printf("Choose a number from 1-9\n");
    scanf("%d", &field);
    field--;
    int fieldRow = 2 + field / 3 * 4;
    int fieldCol = 2 + field % 3 * 4;

    if (field + 1 < 1 || field + 1 > 9)
    {
        printf("Not a valid number\n");
        play(player);
    }
    else if (table[fieldRow][fieldCol] == 'x' || table[fieldRow][fieldCol] == 'o')
    {
        printf("Field is occupied\n");
        play(player);
    }
    else
    {
        table[fieldRow][fieldCol] = player;
        playTable[field / 3][field % 3] = player;
    }
}

void initTable()
{
    for (int row = 0; row < len; row++)
    {
        for (int col = 0; col < len; col++)
        {
            table[row][col] = ' ';
            if (row % 4 == 0)
            {
                table[row][col] = '-';
            }
            if (col % 4 == 0)
            {
                table[row][col] = '|';
            }
            if ((row % 4 == 0) && (col % 4 == 0))
            {
                table[row][col] = '+';
            };
            if (((row - 2) % 4 == 0) && ((col - 2) % 4 == 0))
            {
                table[row][col] = ++num + '0';
            }
        }
    }
}

void printTable()
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            printf("%c", table[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    char player;
    int turn = 0;
    int spot;
    initTable();
    while (1)
    {
        system("clear");
        printTable();
        player = turn % 2 == 0 ? 'x' : 'o';

        play(player);
        turn++;
        checkWin(player);
    }

    return 0;
}
