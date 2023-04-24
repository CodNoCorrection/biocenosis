typedef struct animal {
    //char isAlive; хз это нужно или нет
    char hunger;
    char age;
    char gender;
    char pregnancy; // беременна или нет, самое главное особей мужского пола не сделать беременными
    char pregTime; //это время беременности, например у тигров 2 хода, у зайцев 1
} RAB;

typedef struct grass {
    char age; //если введём смерть от возраста
} GRS;

typedef struct world {
    char rHere;
    char tHere;
    char gHere; 
    RAB rabbit, tiger;
    GRS grass;
} WORLD;