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
  printf("Name: %s\nAttack: %d\nDefense: %d\nSpeed: %d\nHealth: %d\nLevel : %d\nCurrent XP : %d\nXP until until next level: %d\n",Player->name, Player->atk, Player->def, Player->spd,Player->hp,Player->level,Player->xp,(Player->xpOffset - Player->xp));
  sleep(3);
}

void DisplayHelp(){
  printf("\nCOMMANDS AND FUNCTIONS\nPlease type everything with a leading Capital!\nStats - Displays your Attack, Defense, Speed, Current XP, XP until next level, and Health\nRoom - Current Room information\nInventory - Display your current Inventory\nHelp - Displays the Help\nAdvance: Moves you to the next room if it is possible\n");
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
  else if(strcmp(input,"Attack\n") == 0){
    battle();
  }
  else if(strcmp(input,"Advance\n") == 0){
    if(!roomClear)
      printf("The room isn't clear yet!\n");
    else{
      printf("You move into the next room\n");
      generateRoom();
    }
  }
  else{
    printf("Sorry, I don't understand that\n");
    sleep(1);
    system("clear");
  }
}

void battle(){
  if(Enemy->hp <= 0){
    printf("There is no monster in this room");
  }
  else{
    int dmg;
    if(Player->spd >= Enemy->spd){
      dmg = rand_lim(Player->atk) + Player->atk - Enemy->def;
      printf("You dealt %d Damage to the monster\n", dmg);
      Enemy->hp = Enemy->hp - dmg;
      sleep(1);
      if(Enemy->hp > 0){
	dmg = rand_lim(Enemy->atk) + Enemy->atk - Player->def;
	printf("The monster dealt %d damage to you", dmg);
	Player->hp = Player->hp - dmg;
      }
      else{
	printf("The monster Died!\n");
	roomClear = 1;
	Player->xp = Player->xp + roomXp;
	while(Player->xp > Player->xpOffset){
	  levelUp();
	}
      }
    }
    else{
      dmg = rand_lim(Enemy->atk) + Enemy->atk - Player->def;
      printf("The monster dealt %d damage to you", dmg);
      Player->hp = Player->hp - dmg;
      sleep(1);
      if(Player->hp > 0){
	dmg = rand_lim(Player->atk) + Player->atk - Enemy->def;
	printf("You dealt %d Damage to the monster\n", dmg);
	Enemy->hp = Enemy->hp - dmg;
	if(Enemy->hp <= 0){
	  roomClear = 1;
	  Player->xp = Player->xp + roomXp;
	  while(Player->xp > Player->xpOffset){
	    levelUp();
	  }
	}
      }
    }
  }
}

void levelUp(){
  Player->level = Player->level + 1;
  printf("You have leveled up. You are now level %d\n", Player->level);
  Player->xp = Player->xp - Player->xpOffset;
  Player->xpOffset = (Player->level * 10);
}
