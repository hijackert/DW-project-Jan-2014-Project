#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void generatePlayer();
void printStats();
void generateRoom();
void interpretGame();
void battle();
void levelUp();
void printRoomInfo();
void generateEnemy();
int rand_lim(int limit);
void DisplayHelp();
void nameGenerator();
void dump();
int load();
