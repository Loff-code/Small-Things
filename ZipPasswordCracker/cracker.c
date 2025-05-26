#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#define len 6

char alphabet[27];
char password[len + 1];

void initAlph()
{
    for (size_t i = 0; i < 26; i++)
    {
        alphabet[i] = 'a' + i;
    }
    alphabet[26] = '\0';
}

void crack()
{
    int attempt = 0;

    password[len] = '\0';

    int num[len];
    for (size_t i = 0; i < len; i++)
    {
        num[i] = 0;
    }

    int found = 0;

    while (num[len - 1] < 26 && !found)
    {
        attempt++;
        // Handle carry logic
        for (size_t i = 0; i < len - 1; i++)
        {
            if (num[i] == 26)
            {
                num[i] = 0;
                num[i + 1]++;
            }
        }

        // Construct password guess
        for (size_t i = 0; i < len; i++)
        {
            password[i] = alphabet[num[i]];
        }
        // password[len - 3] = 'g';
        password[len - 2] = 'e';
        password[len - 1] = 'r';

        // Test the archive with the password
        char command[256];
        sprintf(command, "unzip -t -P %s topsecret.zip > /dev/null 2>&1", password);
        int ret = system(command);

        if (ret == 0)
        {
            // Success! The password worked
            printf("Success! The password is: %s\n", password);
            found = 1;
        }

        num[0]++;
    }

    if (found)
    {
        char command[256];
        sprintf(command, "unzip -o -P %s topsecret.zip", password);
        system(command);
        printf("Attempt: %d\n", attempt);
    }
}

int main(int argc, char const *argv[])
{
    initAlph();

    struct timeval start, end;
    gettimeofday(&start, NULL);

    crack();

    gettimeofday(&end, NULL);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     ((end.tv_usec - start.tv_usec) / 1000000.0);

    printf("Time taken: %.2f seconds\n", elapsed);
    printf("Done!\n");

    return 0;
}
