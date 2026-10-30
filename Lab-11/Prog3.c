#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100005
#define SIZE 262147

char words[MAX][11];
char startWord[11];

int hashTable[SIZE];

int hashFunction(char *s)
{
    unsigned long long h = 0;

    while (*s)
        h = (h * 31 + *s++) % SIZE;

    return h;
}

void insertWord(int index)
{
    int h = hashFunction(words[index]);

    while (hashTable[h] != 0)
        h = (h + 1) % SIZE;

    hashTable[h] = index + 1;
}

int findWord(char *s)
{
    int h = hashFunction(s);

    while (hashTable[h] != 0)
    {
        int index = hashTable[h] - 1;

        if (strcmp(words[index], s) == 0)
            return index;

        h = (h + 1) % SIZE;
    }

    return -1;
}

char *getWord(int index, int N)
{
    if (index == N)
        return startWord;

    return words[index];
}

int expand(int *frontier, int count, int *next,
           int *dist1, int *dist2, int N, int *nextCount)
{
    *nextCount = 0;

    for (int i = 0; i < count; i++)
    {
        int u = frontier[i];

        char temp[11];
        strcpy(temp, getWord(u, N));

        for (int j = 0; temp[j] != '\0'; j++)
        {
            char original = temp[j];

            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c == original)
                    continue;

                temp[j] = c;

                int v = findWord(temp);

                if (v != -1 && dist1[v] == -1)
                {
                    dist1[v] = dist1[u] + 1;

                    if (dist2[v] != -1)
                        return dist1[v] + dist2[v];

                    next[(*nextCount)++] = v;
                }
            }

            temp[j] = original;
        }
    }

    return -1;
}

int main()
{
    int N;

    printf("Enter number of dictionary words: ");
    scanf("%d", &N);

    printf("Enter dictionary words:\n");

    for (int i = 0; i < N; i++)
    {
        scanf("%10s", words[i]);
        insertWord(i);
    }

    printf("Enter starting word: ");
    scanf("%10s", startWord);

    char target[11];

    printf("Enter target word: ");
    scanf("%10s", target);

    int source = findWord(startWord);
    int destination = findWord(target);

    if (strcmp(startWord, target) == 0)
    {
        printf("Minimum mutations: 0\n");
        return 0;
    }

    if (destination == -1)
    {
        printf("No valid transformation exists.\n");
        return 0;
    }

    if (source == -1)
        source = N;

    int *dist1 = malloc((N + 1) * sizeof(int));
    int *dist2 = malloc((N + 1) * sizeof(int));

    int *f1 = malloc((N + 1) * sizeof(int));
    int *f2 = malloc((N + 1) * sizeof(int));
    int *next = malloc((N + 1) * sizeof(int));

    for (int i = 0; i <= N; i++)
    {
        dist1[i] = -1;
        dist2[i] = -1;
    }

    dist1[source] = 0;
    dist2[destination] = 0;

    f1[0] = source;
    f2[0] = destination;

    int count1 = 1;
    int count2 = 1;

    while (count1 > 0 && count2 > 0)
    {
        int answer;
        int nextCount;

        if (count1 <= count2)
        {
            answer = expand(f1, count1, next,
                            dist1, dist2, N, &nextCount);

            if (answer != -1)
            {
                printf("Minimum mutations: %d\n", answer);
                return 0;
            }

            int *temp = f1;
            f1 = next;
            next = temp;

            count1 = nextCount;
        }
        else
        {
            answer = expand(f2, count2, next,
                            dist2, dist1, N, &nextCount);

            if (answer != -1)
            {
                printf("Minimum mutations: %d\n", answer);
                return 0;
            }

            int *temp = f2;
            f2 = next;
            next = temp;

            count2 = nextCount;
        }
    }

    printf("No valid transformation exists.\n");

    return 0;
}