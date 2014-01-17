#include "headers.h"

char mainMenu[256];
char user[256];
typedef struct Character{
  char name[256];
  int atk;
  int def;
  int spd;
} Character;

Character * Player;

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
      Player->atk = rand_lim(15) + 1;
      Player->def = rand_lim(12) + 6;
      Player->spd = rand_lim(100) + 6;
      printf("Generating Stats\n");
      printf("Name: %s\n Attack: %d\n Defense: %d\n Speed: %d\n",Player->name, Player->atk, Player->def, Player->spd);
      break;
    }
    else if(strcmp("Exit\n",mainMenu) == 0){
      printf("Goodbye\n");
      break;
    }
    else{
      printf("Sorry. I do not understand what you said\n");
    }
  }
  return 1;
}

int rand_lim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retval;

    srand(time(NULL));
    retval = rand();
    printf("%d\n",divisor);
    while(retval >= limit){
      retval = retval - divisor;
    }

    return retval;
}
