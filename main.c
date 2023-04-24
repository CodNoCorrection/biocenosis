#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#define SIZE 10

void createRabbit(int s, WORLD map[][SIZE]) {
    srand(time(NULL));
    if (s>=SIZE){
        printf("too much");
        return;
    }
    while (s!=0) {
        int x = rand()%SIZE, y = rand()%SIZE;
        if (map[x][y].rHere == 0){
            map[x][y].rHere = 1;
            map[x][y].rabbit.age = 0;
            map[x][y].rabbit.hunger = 0;
            map[x][y].rabbit.pregnancy = 0;
            map[x][y].rabbit.pregTime = 0;
            char gender = rand()%2;
            map[x][y].rabbit.gender = gender;
        }
        else s++;
        s--;
    }
}

void createGrass(int s, WORLD map[][SIZE]) {
    srand(time(NULL));
    if (s>=SIZE){
        printf("too much");
        return;
    }
    while (s!=0) {
        int x = rand()%SIZE, y = rand()%SIZE;
        if (map[x][y].gHere == 0){
            map[x][y].gHere = 1;
            map[x][y].grass.age = 0;
        }
        else s++;
        s--;
    }
}

void createTiger(int s, WORLD map[][SIZE]) {
    srand(time(NULL));
    if (s>=SIZE){
        printf("too much");
        return;
    }
    while (s!=0) {
        int x = rand()%SIZE, y = rand()%SIZE;
        if (map[x][y].tHere == 0){
            map[x][y].tHere = 1;
            map[x][y].tiger.age = 0;
            map[x][y].tiger.hunger = 0;
            map[x][y].tiger.pregnancy = 0;
            map[x][y].tiger.pregTime = 0;
            char gender = rand()%2;
            map[x][y].tiger.gender = gender;
        }
        else s++;
        s--;
    }
}

//void behavior(WORLD map[][SIZE]) {
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            if (!map[i][j].tHere && !map[i][j].rHere) continue;
//            else if (map[i][j].tHere) {
//                int a = 9;
//            }
//            else if (map[i][j].rHere) {
//               
//            }
//        }
//    }
//} 

void printArr(WORLD map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("(%d %d %d) ", map[i][j].gHere, map[i][j].rHere, map[i][j].tHere);
        }
        printf("\n");
    }
}

int main() {
    static WORLD map[SIZE][SIZE];
    printf("enter the amount of grass appearing per turn >");
    int cntGrass, cntRabbit, cntTiger;
    scanf("%d", &cntGrass);
    createGrass(cntGrass, map);
    printf("enter the amount of rabbits appearing per turn >");
    scanf("%d", &cntRabbit);
    createRabbit(cntRabbit, map);
    printf("enter the amount of tigers appearing per turn >");
    scanf("%d", &cntTiger);
    createTiger(cntTiger, map);
    printArr(map);
    return 0;
}