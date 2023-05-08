#define _CRT_SECURE_NO_WARNINGS
#define _WIN64 1
#define _AMD64_ 1
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <synchapi.h>
#include "struct.h"
//#include "structures.h"
#define ageTiger 80
#define death 8
#define stepT 1
#define rangeT 3
int numGrass = 0, numAnimal = 0;
#define SIZE 10


void createRabbit(int s, WORLD map[][SIZE]) {
    //srand(time(NULL));
    if (s >= SIZE * SIZE) {
        printf("too much");
        return;
    }
    while (s != 0) {
        if (numAnimal == SIZE * SIZE) return;
        int x = rand() % SIZE, y = rand() % SIZE;
        if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere == 0 && map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere == 0) {
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere = 1;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.age = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.hunger = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.pregnancy = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.pregTime = 0;
            char gender = (rand() % 2) + 1;// 1 - м 2 - ж
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rabbit.gender = gender;
            numAnimal++;
        }
        else s++;
        s--;
    }
}

void createGrass(int s, WORLD map[][SIZE]) {
    //srand(time(NULL));
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
            numGrass++;
        }
        else s++;
        s--;
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
        if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].rHere == 0 && map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere == 0) {
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 1;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
            char gender = (rand() % 2) + 1;//1 - м 2 - ж
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = gender;
            numAnimal++;
        }
        else s++;
        s--;
    }
}

void move_to_rabbit(int x, int y, int x2, int y2, WORLD map[][SIZE]) {
    int x1 = x, y1 = y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int n = 0;
    while ((x1 != x2 || y1 != y2) && n < stepT)
    {
        int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
        ++n;
    }
    if (x1 == x2 && y1 == y2) {
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag = 1;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.age = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.gender = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.hunger = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger - 3;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.age = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.gender = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.hunger = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.pregnancy = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rabbit.pregTime = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rHere = 0;
        return;
    }
    if (map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere == 0 && !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag && !map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].rHere) {
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].flag = 1;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tHere = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.age = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.gender = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.hunger = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
        map[(x1 + SIZE) % SIZE][(y1 + SIZE) % SIZE].tiger.pregTime = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
    }
}

int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[] = { -1,-1,-1, 0, 1, 1,  1,  0 };
void find_empty_T(int x, int y, WORLD map[][SIZE]) {
    for (int i = 0; i < 8; ++i) {
        if (map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].rHere == 0 && map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tHere == 0 && !map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].flag) {
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].flag = 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tHere = 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.age = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.hunger = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.pregnancy = 0;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.pregTime = 0;
            int gender = rand() % 2 + 1;
            map[(x + dx[i] + SIZE) % SIZE][(y + dy[i] + SIZE) % SIZE].tiger.gender = gender;
            return;
        }
    }
}

int loveT(int x, int y, WORLD map[][SIZE], int rad) {
    int i, j = y - rad;
    for (i = x - rad; i < x + rad; ++i) {
        if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && ((map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger > 4) || (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4))) {
            int random = rand() % 5;
            if (random == 0 || random == 1) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
        else if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4) {
            int random = rand() % 5;
            if (random == 0 || random == 1 || random == 2) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
    }
    for (; j < y + rad; ++j) {
        if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && ((map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger > 4) || (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4))) {
            int random = rand() % 5;
            if (random == 0 || random == 1) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
        else if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4) {
            int random = rand() % 5;
            if (random == 0 || random == 1 || random == 2) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
    }
    for (; i > x - rad; --i) {
        if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && ((map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger > 4) || (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4))) {
            int random = rand() % 5;
            if (random == 0 || random == 1) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
        else if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4) {
            int random = rand() % 5;
            if (random == 0 || random == 1 || random == 2) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
    }
    for (; j > y - rad; --j) {
        if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && ((map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger > 4) || (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4))) {
            int random = rand() % 5;
            if (random == 0 || random == 1) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
        else if (rad <= stepT && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tHere && map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger <= 4 && map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].tiger.hunger <= 4) {
            int random = rand() % 5;
            if (random == 0 || random == 1 || random == 2) {
                find_empty_T(x, y, map);
                map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
                map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag = 1;
                return 1;
            }
        }
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
    //srand(time(NULL) * factorTime);
    //factorTime++;
    char flag = 0;
    for (int i = 0; i < 15; ++i) {
        int mod = stepT * 2 + 1;
        int addX = rand() % mod - stepT, addY = rand() % mod - stepT;
        //printf("%d   %d", (addX + x + SIZE) % SIZE, (addY + y + SIZE) % SIZE);
        if (addX == 0 && addY == 0) continue;
        if (!map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].flag && !map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].rHere && !map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tHere) {
            //printf("t = %d   age = %d   gender = %d   hunger = %d   ", map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere, map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age, map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender, map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger);
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].flag = 1;
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tHere = 1;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 0;
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.age = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.gender = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = 0;
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.hunger = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.pregnancy = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
            map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.pregTime = map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime;
            map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
            flag = 1;
            //printf("\nt = %d   age = %d   gender = %d   hunger = %d   ", map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tHere, map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.age, map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.gender, map[(x + addX + SIZE) % SIZE][(y + addY + SIZE) % SIZE].tiger.hunger);
        }
        if (flag) return;
    }
}

void tiger(int x, int y, WORLD map[][SIZE]) {
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age++;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger++;
    map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].flag = 1;
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age == ageTiger) {
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
        return;
    }
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger == death) {
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tHere = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.age = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.gender = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregnancy = 0;
        map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.pregTime = 0;
        return;
    }
    if (map[(x + SIZE) % SIZE][(y + SIZE) % SIZE].tiger.hunger > 3) {
        int r = 1, flag = 0;
        while (r != rangeT) {
            flag = huntT(x, y, map, r);
            if (flag) return;
            ++r;
        }
        if (!flag) {
            moveT(x, y, map);
        }
        //r = rangeT;
        //while (r != 0) {
        //    flag = loveT(x, y, map, r);
        //    if (flag) return;
        //    --r;
        //}
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
        //r = rangeT;
        // while (r != 0) {
        //    flag = huntT(x, y, map, r);
        //    if (flag) return;
        //    --r;
        //}
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
            else if (map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].rHere && !map[(i + SIZE) % SIZE][(j + SIZE) % SIZE].flag) {

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
    if (event.text.unicode <= 57 && event.text.unicode >= 48 && cnt <= 1 &&
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
    srand(time(NULL));
    static WORLD map[SIZE][SIZE];
    int show_start = 1;
    int show_flag_input = 0;
    int show_continue = 0;
    int flag_v = 0;
    int tigers = 0;
    int rabbits = 0;
    int grass = 0;
    int cnt = 0;
    int cnt1 = 0;
    int matrix = 0;
    int flag_constant_print = 0;
    sfVideoMode mode = { 800, 800, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "life", sfResize | sfClose, NULL);
    sfFont* font = sfFont_createFromFile("Monocraft.ttf");


    sfText* choose_text_grass = sfText_create();
    sfText_setString(choose_text_grass, "grass\namount");
    sfText_setFont(choose_text_grass, font);
    sfText_setFillColor(choose_text_grass, sfColor_fromRGB(0, 255, 0));
    sfText_setCharacterSize(choose_text_grass, 32);
    sfText_setPosition(choose_text_grass, (sfVector2f) { 120, 130 });

    sfText* choose_text_rabbits = sfText_create();
    sfText_setString(choose_text_rabbits, "rabbits\namount");
    sfText_setFont(choose_text_rabbits, font);
    sfText_setFillColor(choose_text_rabbits, sfCyan);
    sfText_setCharacterSize(choose_text_rabbits, 32);
    sfText_setPosition(choose_text_rabbits, (sfVector2f) { 120 + 140 + 80, 130 });

    sfText* choose_text_tigers = sfText_create();
    sfText_setString(choose_text_tigers, "tigers\namount");
    sfText_setFont(choose_text_tigers, font);
    sfText_setFillColor(choose_text_tigers, sfRed);
    sfText_setCharacterSize(choose_text_tigers, 32);
    sfText_setPosition(choose_text_tigers, (sfVector2f) { 120 + 140 + 80 + 140 + 80, 130 });

    sfRectangleShape* inputBox_grass;

    int i = 0;
    inputBox_grass = sfRectangleShape_create();
    sfRectangleShape_setSize(inputBox_grass, (sfVector2f) { 80.f, 50.f });
    sfRectangleShape_setFillColor(inputBox_grass, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox_grass, 4);
    sfRectangleShape_setOutlineColor(inputBox_grass, sfColor_fromRGB(0, 255, 0));
    sfRectangleShape_setPosition(inputBox_grass, (sfVector2f) { 140, 250 });
    sfText* inputText_grass;
    inputText_grass = sfText_create();
    sfText_setFont(inputText_grass, font);
    sfText_setCharacterSize(inputText_grass, 24);
    sfText_setFillColor(inputText_grass, sfBlack);
    sfText_setPosition(inputText_grass, (sfVector2f) { 140 + 10, 260 });

    sfRectangleShape* inputBox_rabbits;

    int j = 0;
    inputBox_rabbits = sfRectangleShape_create();
    sfRectangleShape_setSize(inputBox_rabbits, (sfVector2f) { 80.f, 50.f });
    sfRectangleShape_setFillColor(inputBox_rabbits, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox_rabbits, 4);
    sfRectangleShape_setOutlineColor(inputBox_rabbits, sfCyan);
    sfRectangleShape_setPosition(inputBox_rabbits, (sfVector2f) { 360, 250 });


    sfText* inputText_rabbits;
    inputText_rabbits = sfText_create();
    sfText_setFont(inputText_rabbits, font);
    sfText_setCharacterSize(inputText_rabbits, 24);
    sfText_setFillColor(inputText_rabbits, sfBlack);
    sfText_setPosition(inputText_rabbits, (sfVector2f) { 360 + 10, 260 });

    sfRectangleShape* inputBox_tigers;

    int k = 0;
    inputBox_tigers = sfRectangleShape_create();
    sfRectangleShape_setSize(inputBox_tigers, (sfVector2f) { 80.f, 50.f });
    sfRectangleShape_setFillColor(inputBox_tigers, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox_tigers, 4);
    sfRectangleShape_setOutlineColor(inputBox_tigers, sfRed);
    sfRectangleShape_setPosition(inputBox_tigers, (sfVector2f) { 580, 250 });


    sfText* inputText_tigers;
    inputText_tigers = sfText_create();
    sfText_setFont(inputText_tigers, font);
    sfText_setCharacterSize(inputText_tigers, 24);
    sfText_setFillColor(inputText_tigers, sfBlack);
    sfText_setPosition(inputText_tigers, (sfVector2f) { 580 + 10, 260 });

    sfTexture* rabbit_male = sfTexture_createFromFile(
        "RM1.png", NULL);

    sfSprite* sprite_rabbit_male = sfSprite_create();
    sfSprite_setTexture(sprite_rabbit_male, rabbit_male, sfTrue);

    sfTexture* rabbit_female = sfTexture_createFromFile(
        "RF.png", NULL);

    sfSprite* sprite_rabbit_female = sfSprite_create();
    sfSprite_setTexture(sprite_rabbit_female, rabbit_female, sfTrue);

    sfTexture* tiger_texture_male = sfTexture_createFromFile(
        "tigerM.png", NULL);

    sfSprite* sprite_tiger_male = sfSprite_create();
    sfSprite_setTexture(sprite_tiger_male, tiger_texture_male, sfTrue);

    sfTexture* tiger_texture_female = sfTexture_createFromFile(
        "tigerF.png", NULL);

    sfSprite* sprite_tiger_female = sfSprite_create();
    sfSprite_setTexture(sprite_tiger_female, tiger_texture_female, sfTrue);



    sfTexture* grass_texture = sfTexture_createFromFile(
        "textures\\block\\green_concrete_powder.png", NULL);


    sfTexture* dirt_texture = sfTexture_createFromFile(
        "textures\\block\\mycelium_top.png", NULL);
    sfSprite* sprite_dirt = sfSprite_create();
    sfSprite_setTexture(sprite_dirt, dirt_texture, sfTrue);
    sfSprite* sprite_grass = sfSprite_create();
    sfSprite_setTexture(sprite_grass, grass_texture, sfTrue);


    sfRectangleShape* button_exit = sfRectangleShape_create();
    sfTexture* texture_exit = sfTexture_createFromFile("image.png", NULL);
    make_texture(button_exit, texture_exit, 250, 90, 90, 650);

    sfRectangleShape* button_start = sfRectangleShape_create();
    sfTexture* texture_start = sfTexture_createFromFile("start.png", NULL);
    make_texture(button_start, texture_start, 300, 120, 440, 640);

    sfRectangleShape* button_continue = sfRectangleShape_create();
    sfTexture* texture_continue = sfTexture_createFromFile("continue.png",
        NULL);
    make_texture(button_continue, texture_continue, 300, 120, 440, 640);

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

                    if (x >= 105 && x <= 345 && y >= 690 && y <= 740) {
                        sfRenderWindow_close(window);
                    }
                    else if (x >= 468 && y >= 690 && x <= 700 && y <= 735 && show_continue == 0) {
                        show_start = 0;
                        show_flag_input = 1;
                    }
                    else if (x >= 468 && y >= 690 && x <= 700 && y <= 735 && flag_constant_print == 0) {
                        matrix = 1;
                        flag_constant_print = 1;


                        createGrass(grass, map);
                        createRabbit(rabbits, map);
                        createTiger(tigers, map);
                        show_flag_input = 0;


                        for (int n = 0; n < SIZE; n++) {
                            printf("\n");
                            for (int m = 0; m < SIZE; m++) {

                                sfRectangleShape* rectangle = sfRectangleShape_create();
                                sfVector2f size = { 64, 64 };
                                sfRectangleShape_setSize(rectangle, size);
                                sfColor color = sfBlack;
                                sfRectangleShape_setFillColor(rectangle, color);

                                sfVector2f pos = { 80 + n * 64, m * 64 };
                                sfRectangleShape_setPosition(rectangle, pos);
                                sfVector2f position = { 80 + n * 64, m * 64 };
                                sfSprite_setPosition(sprite_dirt, position);
                                sfVector2f scale = { 0.5 * 0.99, 0.5 * 0.99 };
                                sfSprite_setScale(sprite_dirt, scale);
                                for (int tmp = 0; tmp < 3; tmp++) {
                                    sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                    sfRenderWindow_drawSprite(window, sprite_dirt, NULL);
                                    sfRenderWindow_display(window);
                                }


                                if (map[m][n].gHere == 1) {
                                    sfVector2f position = { 80 + n * 64, m * 64 };
                                    sfSprite_setPosition(sprite_grass, position);
                                    sfVector2f scale = { 4 * 0.99, 4 * 0.99 };
                                    sfSprite_setScale(sprite_grass, scale);
                                    sfRectangleShape* rectangle = sfRectangleShape_create();
                                    sfVector2f size = { 64, 64 };
                                    sfRectangleShape_setSize(rectangle, size);
                                    sfColor color = sfBlack;
                                    sfRectangleShape_setFillColor(rectangle, color);
                                    sfVector2f pos = { 80 + n * 64, m * 64 };
                                    sfRectangleShape_setPosition(rectangle, pos);
                                    for (int tmp = 0; tmp < 2; tmp++) {
                                        sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                        sfRenderWindow_drawSprite(window, sprite_grass, NULL);
                                        sfRenderWindow_display(window);
                                    }
                                }
                                if (map[m][n].rHere == 1) {
                                    if (map[m][n].rabbit.gender == 1) {
                                        sfVector2f position = { 80 + n * 64, m * 64 };
                                        sfSprite_setPosition(sprite_rabbit_male, position);
                                        for (int tmp = 0; tmp < 4; tmp++) {

                                            sfRenderWindow_drawSprite(window, sprite_rabbit_male, NULL);
                                            sfRenderWindow_display(window);

                                        }
                                    }
                                    else {
                                        sfVector2f position = { 80 + n * 64, m * 64 };
                                        sfSprite_setPosition(sprite_rabbit_female, position);
                                        for (int tmp = 0; tmp < 3; tmp++) {

                                            sfRenderWindow_drawSprite(window, sprite_rabbit_female, NULL);
                                            sfRenderWindow_display(window);

                                        }
                                    }

                                }
                                if (map[m][n].tHere == 1) {
                                    if (map[m][n].tiger.gender == 1) {
                                        sfVector2f position = { 80 + n * 64, m * 64 };
                                        sfSprite_setPosition(sprite_tiger_male, position);
                                        for (int tmp = 0; tmp < 4; tmp++) {

                                            sfRenderWindow_drawSprite(window, sprite_tiger_male, NULL);
                                            sfRenderWindow_display(window);

                                        }
                                    }
                                    else {
                                        sfVector2f position = { 80 + n * 64, m * 64 };
                                        sfSprite_setPosition(sprite_tiger_female, position);
                                        for (int tmp = 0; tmp < 3; tmp++) {

                                            sfRenderWindow_drawSprite(window, sprite_tiger_female, NULL);
                                            sfRenderWindow_display(window);

                                        }
                                    }
                                }


                            }
                        }
                        break;
                    }
                    else if (x >= 468 && y >= 690 && x <= 700 && y <= 735 && flag_constant_print == 1) {
                        while (1) {

                            behavior(map);
                            for (int n = 0; n < SIZE; n++) {
                                printf("\n");
                                for (int m = 0; m < SIZE; m++) {

                                    sfRectangleShape* rectangle = sfRectangleShape_create();
                                    sfVector2f size = { 64, 64 };
                                    sfRectangleShape_setSize(rectangle, size);
                                    sfColor color = sfBlack;
                                    sfRectangleShape_setFillColor(rectangle, color);

                                    sfVector2f pos = { 80 + n * 64, m * 64 };
                                    sfRectangleShape_setPosition(rectangle, pos);
                                    sfVector2f position = { 80 + n * 64, m * 64 };
                                    sfSprite_setPosition(sprite_dirt, position);
                                    sfVector2f scale = { 0.5 * 0.99, 0.5 * 0.99 };
                                    sfSprite_setScale(sprite_dirt, scale);
                                    for (int tmp = 0; tmp < 3; tmp++) {
                                        sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                        sfRenderWindow_drawSprite(window, sprite_dirt, NULL);
                                        sfRenderWindow_display(window);
                                    }


                                    if (map[m][n].gHere == 1) {
                                        sfVector2f position = { 80 + n * 64, m * 64 };
                                        sfSprite_setPosition(sprite_grass, position);
                                        sfVector2f scale = { 4 * 0.99, 4 * 0.99 };
                                        sfSprite_setScale(sprite_grass, scale);
                                        sfRectangleShape* rectangle = sfRectangleShape_create();
                                        sfVector2f size = { 64, 64 };
                                        sfRectangleShape_setSize(rectangle, size);
                                        sfColor color = sfBlack;
                                        sfRectangleShape_setFillColor(rectangle, color);
                                        sfVector2f pos = { 80 + n * 64, m * 64 };
                                        sfRectangleShape_setPosition(rectangle, pos);
                                        for (int tmp = 0; tmp < 2; tmp++) {
                                            sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
                                            sfRenderWindow_drawSprite(window, sprite_grass, NULL);
                                            sfRenderWindow_display(window);
                                        }
                                    }
                                    if (map[m][n].rHere == 1) {
                                        if (map[m][n].rabbit.gender == 1) {
                                            sfVector2f position = { 80 + n * 64, m * 64 };
                                            sfSprite_setPosition(sprite_rabbit_male, position);
                                            for (int tmp = 0; tmp < 4; tmp++) {

                                                sfRenderWindow_drawSprite(window, sprite_rabbit_male, NULL);
                                                sfRenderWindow_display(window);

                                            }
                                        }
                                        else {
                                            sfVector2f position = { 80 + n * 64, m * 64 };
                                            sfSprite_setPosition(sprite_rabbit_female, position);
                                            for (int tmp = 0; tmp < 3; tmp++) {

                                                sfRenderWindow_drawSprite(window, sprite_rabbit_female, NULL);
                                                sfRenderWindow_display(window);

                                            }
                                        }

                                    }
                                    if (map[m][n].tHere == 1) {
                                        if (map[m][n].tiger.gender == 1) {
                                            sfVector2f position = { 80 + n * 64, m * 64 };
                                            sfSprite_setPosition(sprite_tiger_male, position);
                                            for (int tmp = 0; tmp < 4; tmp++) {

                                                sfRenderWindow_drawSprite(window, sprite_tiger_male, NULL);
                                                sfRenderWindow_display(window);

                                            }
                                        }
                                        else {
                                            sfVector2f position = { 80 + n * 64, m * 64 };
                                            sfSprite_setPosition(sprite_tiger_female, position);
                                            for (int tmp = 0; tmp < 3; tmp++) {

                                                sfRenderWindow_drawSprite(window, sprite_tiger_female, NULL);
                                                sfRenderWindow_display(window);

                                            }
                                        }
                                    }


                                }
                            }
                            //Sleep(10);
                            reset(map);
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
