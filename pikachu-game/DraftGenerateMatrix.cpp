#include <iostream>
#include <cstdio>

void GenerateMatrix(const int n)
{
    srand(time(NULL));

    bool * checkDuplicate = new bool [n * n];
    int * pos = new int [n * n];
    int * pairCharacter = new int [n * n];
    
    //Build random character pair
    for (int i = 0; i < n * n; i += 2)
        if (i / 2 > 25)
            pairCharacter[i] = pairCharacter[i + 1] = rand() % 26 + 'A';
        else
            pairCharacter[i] = pairCharacter[i + 1] = i / 2 + 'A';

    //Build position array
    for (int i = 0; i < n * n; i++) checkDuplicate[i] = 0;
    for (int i = 0; i < n * n; i++) {
        int tmp = 0;
        do {
            tmp = rand() % (n * n);
        } while (checkDuplicate[tmp]);
        checkDuplicate[tmp] = 1;
        pos[i] = tmp;
    }

    //Initiallized
    char** dataTable = new char * [n];
    for (int i = 0; i < n; i++) 
        dataTable[i] = new char [n];

    //Build table
    for (int i = 0; i < n * n; i++)
        dataTable[pos[i] / n][pos[i] % n] = pairCharacter[i];

    //Cout for debugging
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << dataTable[i][j] << ' ';
        std::cout << '\n';
    }

    //return dataTable;
}