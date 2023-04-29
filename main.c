#define _CRT_SECURE_NO_WARNINGS
#define _WIN64 1
#define _AMD64_ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#define SIZE 10
#define ageTiger 80
#define death 8
#define stepT 1
#define rangeT 3
int numGrass = 0, numAnimal = 0;

void createRabbit(int s, WORLD map[][SIZE]) {
    srand(time(NULL));
    if (s >= SIZE*SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numAnimal == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rHere == 0 && map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tHere == 0) {
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rHere = 1;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rabbit.age = 0;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rabbit.hunger = 0;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rabbit.pregnancy = 0;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rabbit.pregTime = 0;
            char gender = (rand() % 2) + 1;// 1 - м 2 - ж
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rabbit.gender = gender;
            numAnimal++;
        }
        else s++;
        s--;
    }
}

void createGrass(int s, WORLD map[][SIZE]) {
    srand(time(NULL));
    if (s >= SIZE*SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numGrass == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].gHere == 0) {
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].gHere = 1;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].grass.age = 0;
            numGrass++;
        }
        else s++;
        s--;
    }
}

void createTiger(int s, WORLD map[][SIZE]) {
    srand(time(NULL));
    if (s >= SIZE*SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numAnimal == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].rHere == 0 && map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tHere == 0) {
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tHere = 1;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tiger.age = 0;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tiger.hunger = 0;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tiger.pregnancy = 0;
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tiger.pregTime = 0;
            char gender = (rand() % 2) + 1;//1 - м 2 - ж
            map[(x + SIZE)%SIZE][(y + SIZE)%SIZE].tiger.gender = gender;
            numAnimal++;
        }
        else s++;
        s--;
    }
}


void behavior(WORLD map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!map[i % SIZE][j % SIZE].tHere && !map[i % SIZE][j % SIZE].rHere) {
                map[i % SIZE][j % SIZE].flag = 1;
                continue;
            }
            else if (map[(i + SIZE)%SIZE][(j + SIZE)%SIZE].tHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
                tiger(i, j, map);
            }
            else if (map[(i + SIZE)%SIZE][(j + SIZE)%SIZE].rHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
               
            }
        }
    }
} 

void printArr(WORLD map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("(%d %d %d) ", map[(i + SIZE)%SIZE][(j + SIZE)%SIZE].gHere, map[(i + SIZE)%SIZE][(j + SIZE)%SIZE].rHere, map[(i + SIZE)%SIZE][(j + SIZE)%SIZE].tHere);
        }
        printf("\n");
    }
}

void reset(WORLD map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            map[i][j].flag = 0;
        }
    }
}

int main() {
    static WORLD map[SIZE][SIZE];
    printf("enter the amount of grass appearing per turn > ");
    int cntGrass, cntRabbit, cntTiger;
    scanf("%d", &cntGrass);
    createGrass(cntGrass, map);
    printf("enter the amount of rabbits appearing at the begining > ");
    scanf("%d", &cntRabbit);
    createRabbit(cntRabbit, map);
    printf("enter the amount of tigers appearing at the begining > ");
    scanf("%d", &cntTiger);
    createTiger(cntTiger, map);
    printArr(map);
    while (1) {
        behavior(map);
        printf("\n\n\n");
        printArr(map);
        reset(map);
    }
    return 0;
}
