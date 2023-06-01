#define _CRT_SECURE_NO_WARNINGS
//#define _WIN64 1
//#define _AMD64_ 1

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <synchapi.h>
#include "struct.h"
#define shift 2.1
#define scaling 0.5
#define cell 32
#define ageTiger 500
#define death 8
#define deathTiger 8
#define stepT 1
#define rangeT 3
int numGrass = 0, numAnimal = 0, numTiger = 0, numRabbit = 0;
#define SIZE 40
#define ageRabbit 20
#define rangeR 2
#define stepR 1
#define nutritionGrass 3
#define nutritionRabbit 3
#define XstartButton 1000
#define YstartButton 1300
#define XexitButton 270
#define YexitButton 1310
#define XcontinueButton 1000
#define YcontinueButton 1300

void createRabbit(int s, WORLD map[][SIZE]) {
    //srand(time(NULL));
    if (s >= SIZE * SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numAnimal == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere == 0 &&
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere == 0) {
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere = 1;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.age = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.pregnancy = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.pregTime = 0;
            char gender = (rand() % 2) + 1;// 1 - м 2 - ж
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender = gender;
            ++numAnimal;
            ++numRabbit;
        }
        else s++;
        --s;
    }
}

void createGrass(int s, WORLD map[][SIZE]) {
    if (s >= SIZE * SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numGrass == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].gHere == 0) {
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].gHere = 1;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].grass.age = 0;
            ++numGrass;
        }
        else s++;
        --s;
    }
}

void createTiger(int s, WORLD map[][SIZE]) {
    //srand(time(NULL));
    if (s >= SIZE * SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numAnimal == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere == 0 &&
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere == 0) {
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 1;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
            char gender = (rand() % 2) + 1;//1 - м 2 - ж
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = gender;
            ++numAnimal;
            ++numTiger;
        }
        else s++;
        --s;
    }
}

void killTiger(int x, int y, WORLD map[][SIZE]) {
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
    --numTiger;
}

void killRabbit(WORLD map[][SIZE], int x, int y) {
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.age = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.pregnancy = 0;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.pregTime = 0;
    --numRabbit;
}

void rewriteTiger(WORLD map[][SIZE], int x, int y, int x1, int y1) {
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.age = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.gender = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.hunger = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) %
        SIZE].tiger.pregnancy;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) %
        SIZE].tiger.pregnancy;
}

void move_to_rabbit(int x, int y, int x2, int y2, WORLD map[][SIZE]) {
    int x1 = x, y1 = y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int n = 0;
    while ((x1 != x2 || y1 != y2) && n < stepT) {
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
        ++n;
    }
    if (x1 == x2 && y1 == y2) {
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag = 1;
        rewriteTiger(map, x, y, x1, y1);
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.hunger -= nutritionRabbit;
        killRabbit(map, ((x1 + SIZE) % SIZE), ((y1 + SIZE) % SIZE));
        killTiger((x + SIZE) % SIZE, (y + SIZE) % SIZE, map);
        return;
    }
    if (map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere == 0 && !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag &&
        !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rHere) {
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag = 1;
        rewriteTiger(map, x, y, x1, y1);
        killTiger((x + SIZE) % SIZE, (y + SIZE) % SIZE, map);
    }
}

int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[] = { -1, -1, -1, 0, 1, 1, 1, 0 };

void find_empty_T(int x, int y, WORLD map[][SIZE]) {
    for (int i = 0; i < 8; ++i) {
        if (map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rHere == 0 &&
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tHere == 0 &&
            !map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].flag) {
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].flag = 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tHere = 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.age = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.hunger = 4;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.pregnancy = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.pregTime = 0;
            int gender = rand() % 2 + 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.gender = gender;
            return;
        }
    }
}

int ChanceAndBirthTiger(WORLD map[][SIZE], int i, int j, int x, int y, int rad) {
    if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.gender !=
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender &&
        ((map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 &&
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger > 4) ||
            (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 4 &&
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4))) {
        int random = rand() % 5;
        if (random == 0 || random == 1) {
            ++numTiger;
            find_empty_T(x, y, map);
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
            return 1;
        }
    }
    else if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.gender !=
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender &&
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4) {
        int random = rand() % 5;
        if (random == 0 || random == 1 || random == 2) {
            ++numTiger;
            find_empty_T(x, y, map);
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
            return 1;
        }
    }
    return 0;
}

int loveT(int x, int y, WORLD map[][SIZE], int rad) {
    int i, j = y - rad, flag = 0;
    for (i = x - rad; i < x + rad; ++i) {
        flag = ChanceAndBirthTiger(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    for (; j < y + rad; ++j) {
        flag = ChanceAndBirthTiger(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    for (; i > x - rad; --i) {
        flag = ChanceAndBirthTiger(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    for (; j > y - rad; --j) {
        flag = ChanceAndBirthTiger(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    return 0;
}

int huntT(int x, int y, WORLD map[][SIZE], int rad) {
    int i, j = y - rad;
    for (i = x - rad; i < x + rad; ++i) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_rabbit((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    for (; j < y + rad; ++j) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_rabbit((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    for (; i > x - rad; --i) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_rabbit((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    for (; j > y - rad; --j) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_rabbit((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    return 0;
}

void moveT(int x, int y, WORLD map[][SIZE]) {
    char flag = 0;
    for (int i = 0; i < 15; ++i) {
        int mod = stepT * 2 + 1;
        int addX = rand() % mod - stepT, addY = rand() % mod - stepT;
        if (addX == 0 && addY == 0) continue;
        if (!map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].flag &&
            !map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].rHere &&
            !map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tHere) {
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].flag = 1;
            rewriteTiger(map, (x + SIZE) % SIZE, (y + SIZE) % SIZE, (x + addX + SIZE) % SIZE, (y + addY + SIZE) % SIZE);
            killTiger((x + SIZE) % SIZE, (y + SIZE) % SIZE, map);
            flag = 1;
        }
        if (flag) return;
    }
}

void tiger(int x, int y, WORLD map[][SIZE]) {
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age++;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger++;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age == ageTiger ||
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger == deathTiger) {
        killTiger(x, y, map);
        return;
    }
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 3) {
        int r = 1, flag = 0;
        while (r != rangeT) {
            flag = huntT(x, y, map, r);
            if (flag) return;
            ++r;
        }
        r = 0;
        while (r != rangeT) {
            if (r > stepT) break;
            flag = loveT(x, y, map, r);
            if (flag) return;
            ++r;
        }
        if (!flag) {
            moveT(x, y, map);
        }
    }
    else {
        int r = 1, flag = 0;
        while (r != rangeT) {
            if (r > stepT) break;
            flag = loveT(x, y, map, r);
            if (flag) return;
            ++r;
        }
        if (!flag) {
            moveT(x, y, map);
        }
    }
}

void rewriteRabbit(WORLD map[][SIZE], int x, int y, int x1, int y1) {
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rHere = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.age = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.age;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.gender = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.hunger = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) %
        SIZE].rabbit.pregnancy;
    map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) %
        SIZE].rabbit.pregnancy;
}

void move_to_grass(int x, int y, int x2, int y2, WORLD map[][SIZE]) {
    int x1 = x, y1 = y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int n = 0;
    while ((x1 != x2 || y1 != y2) && n < stepR) {
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
        ++n;
    }
    if (x1 == x2 && y1 == y2 && !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere) {
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag = 1;
        rewriteRabbit(map, x, y, x1, y1);
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.hunger -= nutritionGrass;
        killRabbit(map, ((x + SIZE) % SIZE), ((y + SIZE) % SIZE));
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].gHere = 0;
        numGrass--;
        return;
    }
    if (!map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rHere && !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag &&
        !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere) {
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag = 1;
        rewriteRabbit(map, x, y, x1, y1);
        killRabbit(map, (x + SIZE) % SIZE, (y + SIZE) % SIZE);
    }
}

int feeding(int x, int y, WORLD map[][SIZE], int rad) {
    int i, j = y - rad;
    for (i = x - rad; i < x + rad; ++i) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].gHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_grass((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    for (; j < y + rad; ++j) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].gHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_grass((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    for (; i > x - rad; --i) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].gHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_grass((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    for (; j > y - rad; --j) {
        if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].gHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
            move_to_grass((x + SIZE) % SIZE, (y + SIZE) % SIZE, (i + SIZE) % SIZE, (j + SIZE) % SIZE, map);
            return 1;
        }
    }
    return 0;
}

void moveR(int x, int y, WORLD map[][SIZE]) {
    char flag = 0;
    for (int i = 0; i < 15; ++i) {
        int mod = stepR * 2 + 1;
        int addX = rand() % mod - stepR, addY = rand() % mod - stepR;
        if (addX == 0 && addY == 0) continue;
        if (!map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].flag &&
            !map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].rHere &&
            !map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tHere) {
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].flag = 1;
            rewriteRabbit(map, (x + SIZE) % SIZE, (y + SIZE) % SIZE, (x + addX + SIZE) % SIZE,
                (y + addY + SIZE) % SIZE);
            killRabbit(map, (x + SIZE) % SIZE, (y + SIZE) % SIZE);
            flag = 1;
        }
        if (flag) return;
    }
}

void find_empty_R(int x, int y, WORLD map[][SIZE]) {
    for (int i = 0; i < 8; ++i) {
        if (map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rHere == 0 &&
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tHere == 0 &&
            !map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].flag) {
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].flag = 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rHere = 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rabbit.age = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rabbit.hunger = 4;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rabbit.pregnancy = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rabbit.pregTime = 0;
            int gender = rand() % 2 + 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rabbit.gender = gender;
            return;
        }
    }
}

int ChanceAndBirthRabbit(WORLD map[][SIZE], int i, int j, int x, int y, int rad) {
    if (rad <= stepR && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rabbit.gender !=
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere &&
        ((map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger <= 4 &&
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rabbit.hunger > 4) ||
            (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger > 4 &&
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rabbit.hunger <= 4))) {
        int random = rand() % 2;
        if (random == 0) {
            ++numRabbit;
            find_empty_R(x, y, map);
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
            return 1;
        }
    }
    else if (rad <= stepR && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rabbit.gender !=
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere &&
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger <= 4 &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rabbit.hunger <= 4) {
        int random = rand() % 5;
        if (random == 0 || random == 1 || random == 2 || random == 3 || random == 4) {
            ++numRabbit;
            find_empty_R(x, y, map);
            find_empty_R(x, y, map);
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
            return 1;
        }
    }
    else if (rad <= stepR && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rabbit.gender !=
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender &&
        map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere) {
        int random = rand() % 10;
        if (random == 0 || random == 1 || random == 2 || random == 3) {
            ++numRabbit;
            find_empty_R(x, y, map);
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
            map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
            return 1;
        }
    }
    return 0;
}

int loveR(int x, int y, WORLD map[][SIZE], int rad) {
    int i, j = y - rad, flag;
    for (i = x - rad; i < x + rad; ++i) {
        flag = ChanceAndBirthRabbit(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    for (; j < y + rad; ++j) {
        flag = ChanceAndBirthRabbit(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    for (; i > x - rad; --i) {
        flag = ChanceAndBirthRabbit(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    for (; j > y - rad; --j) {
        flag = ChanceAndBirthRabbit(map, i, j, x, y, rad);
        if (flag) return 1;
    }
    return 0;
}

void rabbit(int x, int y, WORLD map[][SIZE]) {
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.age++;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger++;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.age == ageRabbit ||
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger == death) {
        killRabbit(map, x, y);
        return;
    }
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger > 3) {
        int r = 1, flag = 0;
        while (r != rangeR) {
            flag = feeding(x, y, map, r);
            if (flag) return;
            ++r;
        }
        r = 1;
        while (r != rangeR) {
            if (r > stepR) break;
            flag = loveR(x, y, map, r);
            if (flag) return;
            ++r;
        }
        if (!flag) {
            moveR(x, y, map);
        }
    }
    else {
        int r = 1, flag = 0;
        while (r != rangeR) {
            if (r > stepR) break;
            flag = loveR(x, y, map, r);
            if (flag) return;
            ++r;
        }
        if (!flag) {
            moveR(x, y, map);
        }
    }
}

void behavior(WORLD map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //if (!map[i % SIZE][j % SIZE].tHere && !map[i % SIZE][j % SIZE].rHere) {
            //    map[i % SIZE][j % SIZE].flag = 1;
            //    continue;
            //}
            if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
                tiger(i, j, map);
            }
            else if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere &&
                !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {
                rabbit(i, j, map);
            }
        }
    }
}

void printArr(WORLD map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //printf("(%d %d %d) ", map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].gHere, map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere, map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere);
            if (map[i][j].gHere) printf("# ");
            else if (map[i][j].rHere) printf("* ");
            else if (map[i][j].tHere) printf("@ ");
            else printf("  ");
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

int input_text(sfEvent event, int flag, sfText* inputText, int cnt) {
    if (event.text.unicode <= 57 && event.text.unicode >= 48 && cnt <= 2 &&
        flag == 1) {
        char c = event.text.unicode;
        char str[2] = { c };
        str[1] = '\0';
        char* text = malloc(strlen(sfText_getString(inputText)) + strlen(str) + 1);
        strcpy(text, sfText_getString(inputText));
        strcat(text, str);
        sfText_setString(inputText, text);
        cnt += 1;
        //printf("%s\n",sfText_getString(inputText));

    }
    return cnt;

}


void
make_texture(sfRectangleShape* smth, sfTexture* texture, float x_size_vector, float y_size_vector, float x_pos_vector,
    float y_pos_vector) {
    sfRectangleShape_setSize(smth, (sfVector2f) { x_size_vector, y_size_vector });
    sfRectangleShape_setTexture(smth, texture, sfTrue);
    sfRectangleShape_setPosition(smth, (sfVector2f) { x_pos_vector, y_pos_vector });
}


int main() {
    srand(10);
    static WORLD map[SIZE][SIZE];
    int show_start = 1, show_flag_input = 0, show_continue = 0, flag_v = 0, tigers = 0, rabbits = 0, grass = 0, cnt = 0, cnt1 = 0, matrix = 0, flag_constant_print = 0;
    sfVideoMode mode = { 1500, 1500, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "life", sfResize | sfClose, NULL);
    sfFont* font = sfFont_createFromFile("Monocraft.ttf");


    sfText* choose_text_grass = sfText_create();
    sfText_setString(choose_text_grass, "grass\namount");
    sfText_setFont(choose_text_grass, font);
    sfText_setFillColor(choose_text_grass, sfColor_fromRGB(0, 255, 0));
    sfText_setCharacterSize(choose_text_grass, 48);
    sfText_setPosition(choose_text_grass, (sfVector2f) { 120 * shift, 130 * 1.875 });

    sfText* choose_text_rabbits = sfText_create();
    sfText_setString(choose_text_rabbits, "rabbits\namount");
    sfText_setFont(choose_text_rabbits, font);
    sfText_setFillColor(choose_text_rabbits, sfCyan);
    sfText_setCharacterSize(choose_text_rabbits, 48);
    sfText_setPosition(choose_text_rabbits, (sfVector2f) { 670, 130 * 1.875 });

    sfText* choose_text_tigers = sfText_create();
    sfText_setString(choose_text_tigers, "tigers\namount");
    sfText_setFont(choose_text_tigers, font);
    sfText_setFillColor(choose_text_tigers, sfRed);
    sfText_setCharacterSize(choose_text_tigers, 48);
    sfText_setPosition(choose_text_tigers, (sfVector2f) { 1080, 130 * 1.875 });

    sfRectangleShape* inputBox_grass;

    int i = 0;
    inputBox_grass = sfRectangleShape_create();
    sfRectangleShape_setSize(inputBox_grass, (sfVector2f) { 150.f, 94.f });
    sfRectangleShape_setFillColor(inputBox_grass, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox_grass, 4);
    sfRectangleShape_setOutlineColor(inputBox_grass, sfColor_fromRGB(0, 255, 0));
    sfRectangleShape_setPosition(inputBox_grass, (sfVector2f) { 140 * 1.875, 250 * 1.875 });
    sfText* inputText_grass;
    inputText_grass = sfText_create();
    sfText_setFont(inputText_grass, font);
    sfText_setCharacterSize(inputText_grass, 24 * 1.875);
    sfText_setFillColor(inputText_grass, sfBlack);
    sfText_setPosition(inputText_grass, (sfVector2f) { (140 + 10) * 1.875, 260 * 1.875 });

    sfRectangleShape* inputBox_rabbits;

    int j = 0;
    inputBox_rabbits = sfRectangleShape_create();
    sfRectangleShape_setSize(inputBox_rabbits, (sfVector2f) { 150.f, 94.f });
    sfRectangleShape_setFillColor(inputBox_rabbits, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox_rabbits, 4);
    sfRectangleShape_setOutlineColor(inputBox_rabbits, sfCyan);
    sfRectangleShape_setPosition(inputBox_rabbits, (sfVector2f) { 360 * 1.875, 250 * 1.875 });


    sfText* inputText_rabbits;
    inputText_rabbits = sfText_create();
    sfText_setFont(inputText_rabbits, font);
    sfText_setCharacterSize(inputText_rabbits, 24 * 1.875);
    sfText_setFillColor(inputText_rabbits, sfBlack);
    sfText_setPosition(inputText_rabbits, (sfVector2f) { (360 + 10) * 1.875, 260 * 1.875 });

    sfRectangleShape* inputBox_tigers;

    int k = 0;
    inputBox_tigers = sfRectangleShape_create();
    sfRectangleShape_setSize(inputBox_tigers, (sfVector2f) { 150.f, 94.f });
    sfRectangleShape_setFillColor(inputBox_tigers, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox_tigers, 4);
    sfRectangleShape_setOutlineColor(inputBox_tigers, sfRed);
    sfRectangleShape_setPosition(inputBox_tigers, (sfVector2f) { 580 * 1.875, 250 * 1.875 });


    sfText* inputText_tigers;
    inputText_tigers = sfText_create();
    sfText_setFont(inputText_tigers, font);
    sfText_setCharacterSize(inputText_tigers, 24 * 1.875);
    sfText_setFillColor(inputText_tigers, sfBlack);
    sfText_setPosition(inputText_tigers, (sfVector2f) { (580 + 10) * 1.875, 260 * 1.875 });

    sfTexture* rabbit_male = sfTexture_createFromFile("RM1.png", NULL);

    sfSprite* sprite_rabbit_male = sfSprite_create();
    sfSprite_setTexture(sprite_rabbit_male, rabbit_male, sfTrue);

    sfTexture* rabbit_female = sfTexture_createFromFile("RF.png", NULL);

    sfSprite* sprite_rabbit_female = sfSprite_create();
    sfSprite_setTexture(sprite_rabbit_female, rabbit_female, sfTrue);

    sfTexture* tiger_texture_male = sfTexture_createFromFile("tigerM.png", NULL);

    sfSprite* sprite_tiger_male = sfSprite_create();
    sfSprite_setTexture(sprite_tiger_male, tiger_texture_male, sfTrue);

    sfTexture* tiger_texture_female = sfTexture_createFromFile("tigerF.png", NULL);

    sfSprite* sprite_tiger_female = sfSprite_create();
    sfSprite_setTexture(sprite_tiger_female, tiger_texture_female, sfTrue);


    sfTexture* grass_texture = sfTexture_createFromFile("textures\\block\\green_concrete_powder.png", NULL);


    sfTexture* dirt_texture = sfTexture_createFromFile("textures\\block\\mycelium_top.png", NULL);
    sfSprite* sprite_dirt = sfSprite_create();
    sfSprite_setTexture(sprite_dirt, dirt_texture, sfTrue);
    sfSprite* sprite_grass = sfSprite_create();
    sfSprite_setTexture(sprite_grass, grass_texture, sfTrue);


    sfRectangleShape* button_exit = sfRectangleShape_create();
    sfTexture* texture_exit = sfTexture_createFromFile("image.png", NULL);
    make_texture(button_exit, texture_exit, 250, 90, XexitButton, YexitButton);

    sfRectangleShape* button_start = sfRectangleShape_create();
    sfTexture* texture_start = sfTexture_createFromFile("start.png", NULL);
    make_texture(button_start, texture_start, 300, 120, XstartButton, YstartButton);

    sfRectangleShape* button_continue = sfRectangleShape_create();
    sfTexture* texture_continue = sfTexture_createFromFile("continue.png", NULL);
    make_texture(button_continue, texture_continue, 300, 120, XcontinueButton, YcontinueButton);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            // printf("%d\n",event.type );
            switch (event.type) {
            case sfEvtClosed:
                sfRenderWindow_close(window);
                break;

            case sfEvtMouseButtonReleased:
                if (event.mouseButton.button == sfMouseLeft) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    printf("%d %d\n", x, y);

                    if (x >= XexitButton && x <= XexitButton + 300 && y >= YexitButton && y <= YexitButton + 120) {
                        sfRenderWindow_close(window);
                        return 0;
                    }
                    else if (x >= XstartButton && y >= YstartButton && x <= XstartButton + 300 &&
                        y <= YstartButton + 120 && show_continue == 0) {
                        show_start = 0;
                        show_flag_input = 1;
                    }
                    else if (x >= XstartButton && y >= YstartButton && x <= XstartButton + 300 &&
                        y <= YstartButton + 120 && flag_constant_print == 0) {
                        matrix = 1;
                        flag_constant_print = 1;


                        createGrass(grass, map);
                        createRabbit(rabbits, map);
                        createTiger(tigers, map);
                        show_flag_input = 0;

                        sfRectangleShape* rectangleBack = sfRectangleShape_create();
                        sfVector2f sizeBack = { 1280, 1280 };
                        sfVector2f posBack = { 110, 0 };
                        sfRectangleShape_setSize(rectangleBack, sizeBack);
                        sfColor colorBack = sfBlack;
                        sfRectangleShape_setFillColor(rectangleBack, colorBack);
                        sfRectangleShape_setPosition(rectangleBack, posBack);
                        sfRenderWindow_drawRectangleShape(window, rectangleBack, NULL);
                        sfRenderWindow_display(window);
                        for (int n = 0; n < SIZE; n++) {
                            printf("\n");
                            for (int m = 0; m < SIZE; m++) {

                                sfRectangleShape* rectangle = sfRectangleShape_create();
                                sfVector2f size = { cell, cell };
                                sfRectangleShape_setSize(rectangle, size);
                                sfColor color = sfBlack;
                                sfRectangleShape_setFillColor(rectangle, color);

                                sfVector2f pos = { 110 + n * cell, m * cell };
                                //sfRectangleShape_setPosition(rectangle, pos);
                                //sfVector2f position = { 80 + n * 64, m * 64 };
                                //sfSprite_setPosition(sprite_dirt, position);
                                //sfVector2f scale = { 0.5 * 0.99, 0.5 * 0.99 };
                                //sfSprite_setScale(sprite_dirt, scale);
                                //for (int tmp = 0; tmp < 3; tmp++) {
                                //    sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                //    sfRenderWindow_drawSprite(window, sprite_dirt, NULL);
                                //    sfRenderWindow_display(window);
                                //}


                                if (map[m][n].gHere == 1) {
                                    sfSprite_setPosition(sprite_grass, pos);
                                    sfVector2f scale = { scaling, scaling };
                                    sfSprite_setScale(sprite_grass, scale);
                                    sfRectangleShape* rectangle = sfRectangleShape_create();
                                    sfVector2f size = { cell, cell };
                                    sfRectangleShape_setSize(rectangle, size);
                                    sfColor color = sfBlack;
                                    sfRectangleShape_setFillColor(rectangle, color);
                                    sfRectangleShape_setPosition(rectangle, pos);
                                    //for (int tmp = 0; tmp < 2; tmp++) {
                                    //sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                    sfRenderWindow_drawSprite(window, sprite_grass, NULL);
                                    //sfRenderWindow_display(window);
                                    //}
                                }
                                else {
                                    sfRectangleShape_setPosition(rectangle, pos);
                                    sfSprite_setPosition(sprite_dirt, pos);
                                    sfVector2f scale = { 0.5 * 1 * scaling, 0.5 * 1 * scaling };
                                    sfSprite_setScale(sprite_dirt, scale);
                                    //for (int tmp = 0; tmp < 3; tmp++) {
                                    //sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                    sfRenderWindow_drawSprite(window, sprite_dirt, NULL);
                                    //sfRenderWindow_display(window);
                                }
                                if (map[m][n].rHere == 1) {
                                    if (map[m][n].rabbit.gender == 1) {
                                        sfSprite_setPosition(sprite_rabbit_male, pos);
                                        sfVector2f scale = { scaling,  scaling };
                                        sfSprite_setScale(sprite_rabbit_male, scale);
                                        //for (int tmp = 0; tmp < 4; tmp++) {

                                        sfRenderWindow_drawSprite(window, sprite_rabbit_male, NULL);
                                        //sfRenderWindow_display(window);

                                        //}
                                    }
                                    else {
                                        sfSprite_setPosition(sprite_rabbit_female, pos);
                                        sfVector2f scale = { scaling,  scaling };
                                        sfSprite_setScale(sprite_rabbit_female, scale);
                                        //for (int tmp = 0; tmp < 3; tmp++) {

                                        sfRenderWindow_drawSprite(window, sprite_rabbit_female, NULL);
                                        //sfRenderWindow_display(window);

                                        //}
                                    }

                                }
                                if (map[m][n].tHere == 1) {
                                    if (map[m][n].tiger.gender == 1) {
                                        sfSprite_setPosition(sprite_tiger_male, pos);
                                        sfVector2f scale = { scaling,  scaling };
                                        sfSprite_setScale(sprite_tiger_male, scale);
                                        //for (int tmp = 0; tmp < 4; tmp++) {
                                        sfRenderWindow_drawSprite(window, sprite_tiger_male, NULL);
                                        //sfRenderWindow_display(window);

                                        //}
                                    }
                                    else {
                                        sfSprite_setPosition(sprite_tiger_female, pos);
                                        sfVector2f scale = { scaling,  scaling };
                                        sfSprite_setScale(sprite_tiger_female, scale);
                                        //for (int tmp = 0; tmp < 3; tmp++) {
                                        sfRenderWindow_drawSprite(window, sprite_tiger_female, NULL);
                                        //sfRenderWindow_display(window);
                                        //}
                                    }
                                }
                            }
                        }
                        sfRenderWindow_display(window);
                        //break;
                    }
                    else if (x >= XstartButton && y >= YstartButton && x <= XstartButton + 300 &&
                        y <= YstartButton + 120 && flag_constant_print == 1) {
                        int step = 0;
                        while (1) {
                            printf("step = %d\n", step);
                            ++step;
                            behavior(map);
                            sfRectangleShape* rectangle = sfRectangleShape_create();
                            sfVector2f size = { 16, 16 };
                            sfRectangleShape_setSize(rectangle, size);
                            sfColor color = sfBlack;
                            sfRectangleShape_setFillColor(rectangle, color);
                            for (int n = 0; n < SIZE; n++) {
                                printf("\n");
                                for (int m = 0; m < SIZE; m++) {
                                    //sfRectangleShape* rectangle = sfRectangleShape_create();
                                    //sfVector2f size = { 64, 64 };
                                    //sfRectangleShape_setSize(rectangle, size);
                                    //sfColor color = sfBlack;
                                    //sfRectangleShape_setFillColor(rectangle, color);

                                    sfVector2f pos = { 110 + n * cell, m * cell };
                                    sfRectangleShape_setPosition(rectangle, pos);
                                    sfSprite_setPosition(sprite_dirt, pos);
                                    sfVector2f scale = { 0.5 * 1 * scaling, 0.5 * 1 * scaling };
                                    sfSprite_setScale(sprite_dirt, scale);
                                    //for (int tmp = 0; tmp < 3; tmp++) {
                                    //sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                    sfRenderWindow_drawSprite(window, sprite_dirt, NULL);
                                    //sfRenderWindow_display(window);
                                    //}
                                    if (map[m][n].gHere == 1) {
                                        sfSprite_setPosition(sprite_grass, pos);
                                        sfVector2f scale = { scaling, scaling };
                                        sfSprite_setScale(sprite_grass, scale);
                                        //sfRectangleShape* rectangle = sfRectangleShape_create();
                                        //sfVector2f size = { 64, 64 };
                                        //sfRectangleShape_setSize(rectangle, size);
                                        //sfColor color = sfBlack;
                                        //sfRectangleShape_setFillColor(rectangle, color);
                                        //sfRectangleShape_setPosition(rectangle, pos);
                                        //for (int tmp = 0; tmp < 2; tmp++) {
                                        //sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                        sfRenderWindow_drawSprite(window, sprite_grass, NULL);
                                        // sfRenderWindow_display(window);
                                        //}
                                    }
                                    else {
                                        sfRectangleShape_setPosition(rectangle, pos);
                                        sfSprite_setPosition(sprite_dirt, pos);
                                        sfVector2f scale = { 0.5 * 0.99 * scaling, 0.5 * 0.99 * scaling };
                                        sfSprite_setScale(sprite_dirt, scale);
                                        //for (int tmp = 0; tmp < 3; tmp++) {
                                        //sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                        sfRenderWindow_drawSprite(window, sprite_dirt, NULL);
                                        //sfRenderWindow_display(window);
                                    }
                                    if (map[m][n].rHere == 1) {
                                        if (map[m][n].rabbit.gender == 1) {
                                            sfSprite_setPosition(sprite_rabbit_male, pos);
                                            sfVector2f scale = { scaling,  scaling };
                                            sfSprite_setScale(sprite_rabbit_male, scale);
                                            //for (int tmp = 0; tmp < 4; tmp++) {
                                            sfRenderWindow_drawSprite(window, sprite_rabbit_male, NULL);
                                            //   sfRenderWindow_display(window);
                                            //}
                                        }
                                        else {
                                            sfSprite_setPosition(sprite_rabbit_female, pos);
                                            sfVector2f scale = { scaling,  scaling };
                                            sfSprite_setScale(sprite_rabbit_female, scale);
                                            //for (int tmp = 0; tmp < 3; tmp++) {
                                            sfRenderWindow_drawSprite(window, sprite_rabbit_female, NULL);
                                            // sfRenderWindow_display(window);
                                            //}
                                        }
                                    }
                                    if (map[m][n].tHere == 1) {
                                        if (map[m][n].tiger.gender == 1) {
                                            sfSprite_setPosition(sprite_tiger_male, pos);
                                            sfVector2f scale = { scaling,  scaling };
                                            sfSprite_setScale(sprite_tiger_male, scale);
                                            //for (int tmp = 0; tmp < 4; tmp++) {
                                            sfRenderWindow_drawSprite(window, sprite_tiger_male, NULL);
                                            // sfRenderWindow_display(window);
                                            //}
                                        }
                                        else {
                                            sfSprite_setPosition(sprite_tiger_female, pos);
                                            sfVector2f scale = { scaling,  scaling };
                                            sfSprite_setScale(sprite_tiger_female, scale);
                                            //for (int tmp = 0; tmp < 3; tmp++) {
                                            sfRenderWindow_drawSprite(window, sprite_tiger_female, NULL);
                                            //  sfRenderWindow_display(window);
                                            //}
                                        }
                                    }
                                }
                            }
                            sfRenderWindow_display(window);
                            //Sleep(500);
                            reset(map);
                            createGrass(grass, map);
                        }
                    }
                }
                break;
            case sfEvtTextEntered:
                switch (flag_v) {
                case 0:
                    cnt = input_text(event, show_flag_input, inputText_grass, cnt);
                    break;
                case 1:
                    cnt = input_text(event, show_flag_input, inputText_rabbits, cnt);
                    break;
                case 2:
                    cnt = input_text(event, show_flag_input, inputText_tigers, cnt);
                    break;
                default:
                    break;
                }
                if (event.text.unicode == '\r' && show_flag_input == 1) {
                    flag_v++;

                    if (cnt == 0) {
                        switch (flag_v) {
                        case 1:
                            sfText_setString(inputText_grass, "0");
                            break;
                        case 2:
                            sfText_setString(inputText_rabbits, "0");
                            break;
                        case 3:
                            sfText_setString(inputText_tigers, "0");
                            break;
                        default:
                            break;
                        }
                    }
                    cnt = 0;
                    switch (flag_v) {
                    case 1:
                        grass = atoi(sfText_getString(inputText_grass));

                        break;
                    case 2:
                        rabbits = atoi(sfText_getString(inputText_rabbits));
                        break;
                    case 3:
                        tigers = atoi(sfText_getString(inputText_tigers));
                        show_continue = 1;
                        break;
                    default:
                        break;
                    }
                    //printf("%s\n",sfText_getString(inputText));
                }
                break;
            default:
                break;
            }
        }
        if (show_flag_input == 1 && matrix == 0) {
            sfRenderWindow_drawRectangleShape(window, inputBox_grass, NULL);
            sfRenderWindow_drawRectangleShape(window, inputBox_rabbits, NULL);
            sfRenderWindow_drawRectangleShape(window, inputBox_tigers, NULL);
            sfRenderWindow_drawText(window, inputText_grass, NULL);
            sfRenderWindow_drawText(window, inputText_rabbits, NULL);
            sfRenderWindow_drawText(window, inputText_tigers, NULL);
            sfRenderWindow_drawText(window, choose_text_grass, NULL);
            sfRenderWindow_drawText(window, choose_text_rabbits, NULL);
            sfRenderWindow_drawText(window, choose_text_tigers, NULL);
        }
        if (show_start == 1)
            sfRenderWindow_drawRectangleShape(window, button_start, NULL);
        sfRenderWindow_drawRectangleShape(window, button_exit, NULL);
        if (show_continue == 1)
            sfRenderWindow_drawRectangleShape(window, button_continue, NULL);
        //if(matrix == 0)
        sfRenderWindow_display(window);
    }
    sfTexture_destroy(texture_start);
    sfRectangleShape_destroy(inputBox_tigers);
    sfRectangleShape_destroy(inputBox_rabbits);
    sfRectangleShape_destroy(inputBox_grass);
    sfTexture_destroy(texture_exit);
    sfRectangleShape_destroy(button_exit);
    sfRenderWindow_destroy(window);

    return 0;
}
