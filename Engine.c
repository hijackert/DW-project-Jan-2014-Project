#include "headers.h"

int roomNum;
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
} Character;

Character * Player;
Character * Enemy;

int main(){
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
      printf("Name: %s\nAttack: %d\nDefense: %d\nSpeed: %d\nHealth: %d\n",Player->name, Player->atk, Player->def, Player->spd,Player->hp);
      sleep(3);
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

void DisplayHelp(){
  printf("\n COMMANDS AND FUNCTIONS\nPlease type everything with a leading Capital!\nStats - Displays your Attack, Defense, Speed, Current XP\nand XP until next level\nHealth - You current HP\nRoom - Current Room information\nInventory - Display your current Inventory\nHelp - Displays the Help\n");
  
}
