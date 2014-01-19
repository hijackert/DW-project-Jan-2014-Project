#include "headers.h"

int room;
int roomClear;
int roomXp;
char mainMenu[256];
char user[256];
char input[256];
typedef struct Character{
  char name[256];
  int atk;
  int def;
  int spd;
  int hp;
  int xp;
  int level;
  int xpOffset;
} Character;

Character * Player;
Character * Enemy;

int main(){
  system("clear");
  while(1){
    printf("Welcome\n");
    fgets(mainMenu, sizeof(mainMenu), stdin);
    if(strcmp("Play\n", mainMenu) == 0){
      printf("Game is Go\n");
      Player = (Character *)calloc(1, sizeof(Character));
      printf("Please enter your Name:\n");
      fgets(user,sizeof(user),stdin);
      strcpy(Player->name,user);
      srand(time(NULL));
      printf("Generating Stats\n");
      generatePlayer();
      printStats();
      system("clear");
      printf("Would You Like to see the Help Page?\n");
      while(1){
	fgets(input,sizeof(input),stdin);
	if(strcmp("Yes\n",input) == 0){
	  DisplayHelp();
	  break;
	}
	else if(strcmp("No\n",input) == 0){
	  system("clear");
	  break;
	}
	else{
	printf("Sorry. I don't understand what you said\n");
	}	  
      }
      generateRoom();
      while(Player->hp > 0){
	printf("What would you like to do?\n");
	fgets(input,sizeof(input), stdin);
	interpretGame();
      }
      break;
    }
    else if(strcmp("Exit\n",mainMenu) == 0){
      printf("Goodbye\n");
      break;
    }
    else{
      printf("Sorry. I don't understand what you said\n");
    }
  }
  return 1;
}

void generatePlayer(){
  Player->atk = rand_lim(12) + 6;
  Player->def = rand_lim(12) + 6;
  Player->spd = rand_lim(12) + 6;
  Player->hp = rand_lim(12) + 6;
  Player->xp = 0;
  Player->level = 1;
  Player->xpOffset = 10;
}

int rand_lim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retval;

    retval = rand();
    while(retval >= limit){
      retval = retval - limit;
    }

    return retval;
}

void generateRoom(){
  room = room + 1;
  generateEnemy();
  roomClear= 0;
  roomXp = rand_lim(Player->level) + Player->level + room;
}

void generateEnemy(){
  Enemy = (Character *)calloc(1, sizeof(Enemy));
  Enemy->atk = rand_lim(5 + room) + Player->level;
  Enemy->def = rand_lim(5 + room) + Player->level;
  Enemy->spd = rand_lim(5 + room) + Player->level;
  Enemy->hp = rand_lim(5 + room) + Player->level;
  //int temp = rand_lime(2);
  //strcpy(EnemyList[temp],Enemy->name);
}

void printStats(){
  printf("Name: %s\nAttack: %d\nDefense: %d\nSpeed: %d\nHealth: %d\nLevel : %d\nCurrent XP : %d\n XP until until next level: %d\n",Player->name, Player->atk, Player->def, Player->spd,Player->hp,Player->level,Player->xp,(Player->xpOffset - Player->xp));
  sleep(3);
}

void DisplayHelp(){
  printf("\n COMMANDS AND FUNCTIONS\nPlease type everything with a leading Capital!\nStats - Displays your Attack, Defense, Speed, Current XP, XP until next level, and Health - You current HP\nRoom - Current Room information\nInventory - Display your current Inventory\nHelp - Displays the Help\n");
  sleep(3);
}

void printRoomInfo(){
  printf("This is Room %d\n", room);
  if(!roomClear){
    printf("There is a monster in this room\n");
  }
  else{
    printf("There is no monster in this room\n");
  }
  sleep(2);
}

void interpretGame(){
  if(strcmp(input,"Help\n") == 0){
    system("clear");
    DisplayHelp();
  }
  else if(strcmp(input,"Stats\n") == 0){
    system("clear");
    printStats();
  }
  else if(strcmp(input,"Room\n") == 0){
    system("clear");
    printRoomInfo();
  }
  else{
    printf("Sorry, I don't understand that\n");
    sleep(1);
    system("clear");
  }
}


