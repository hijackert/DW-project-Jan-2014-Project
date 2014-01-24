#include "headers.h"

char enemyNames[3][256];
int nameSize = 2;

char mainMenu[256];
char user[256];
char input[256];
char statUp[256];

Character * Player;
Character * Enemy;
Room * DRoom;

int left_to_reseed = 4;
int seed;

int main(){
  nameGenerator();
  srand(time(NULL));
  seed = getpid();
  system("clear");
  while(1){
    printf("Welcome to Generic Crawler #545!\nType Play to start playing, or Exit to Quit the game.\n");
    fgets(mainMenu, sizeof(mainMenu), stdin);
    if(strcasecmp("Play\n", mainMenu) == 0){
      /// printf("Game is Go\n");
      printf("Load Game?\n");
      fgets(input,sizeof(input), stdin);
      int bob = 2;
      if(strcasecmp(input,"Yes\n") == 0)
	bob = 1;
      switch(bob){
      case 1:
	if(!load()){
	  printf("Test\n");
	  break;
	}
      case 2:
	Player = (Character *)calloc(1, sizeof(Character));
	printf("Please enter your Name:\n");
	fgets(user,sizeof(user),stdin);
	strcpy(Player->name,user);
	printf("Generating Stats\n");
	generatePlayer();
	printStats();
	system("clear");
	printf("Would You Like to see the Help Page?\n");
	while(1){
	  fgets(input,sizeof(input),stdin);
	  if(strcasecmp("Yes\n",input) == 0){
	    DisplayHelp();
	    break;
	  }
	  else if(strcasecmp("No\n",input) == 0){
	    system("clear");
	    break;
	  }
	  else{
	    printf("Sorry. I don't understand what you said\n");
	  }	  
	}
	DRoom = calloc(1,sizeof(Room));
	generateRoom();
      }
      while(Player->hp > 0){
	system("clear");
	printf("What would you like to do?\n");
	fgets(input,sizeof(input), stdin);
	interpretGame();
      }
      printf("YOU LOST!\n");
      sleep(2);
    }
    else if(strcasecmp("Exit\n",mainMenu) == 0){
      printf("Goodbye\n");
      break;
    }
    else if(strcasecmp("What What?\n",mainMenu) == 0){
      printf("NO. WE ARE NOT DOING THAT!\n");
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

/*int rand_lim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retval;

    retval = rand();
    while(retval >= limit){
      retval = retval - limit;
    }

    return retval;
    }*/
int rand_lim(int limit) {
  if(left_to_reseed){
    srand(seed);
    left_to_reseed = (int)((double)12 * ( rand()/(double)RAND_MAX));
    seed++;
  }
  else
  left_to_reseed--;
  return (int)((double)limit * ( rand()/(double)RAND_MAX));
}

void generateRoom(){
  int room = DRoom -> room;
  DRoom -> room = DRoom -> room + 1;
  generateEnemy();
  printf("There is a %s in this room\n", Enemy->name);
  DRoom -> roomClear= 0;
  DRoom -> roomXp = rand_lim(Player->level) + Player->level + room;
}

void generateEnemy(){
  int room = DRoom -> room;
  DRoom -> Enemy.atk = rand_lim(10 + room) + Player->level;
  DRoom -> Enemy.def = rand_lim(10 + room) + Player->level;
  DRoom -> Enemy.spd = rand_lim(10 + room) + Player->level;
  DRoom -> Enemy.hp = rand_lim(10 + room) + Player->level;
  int temp = rand_lim(nameSize);
  strcpy(DRoom -> Enemy.name,enemyNames[temp]);
  Enemy = &(DRoom -> Enemy);
  //int temp = rand_lime(2);
  //strcpy(EnemyList[temp],Enemy->name);
}

void printStats(){
  printf("Name: %s\nAttack: %d\nDefense: %d\nSpeed: %d\nHealth: %d\nLevel : %d\nCurrent XP : %d\nXP until until next level: %d\n",Player->name, Player->atk, Player->def, Player->spd,Player->hp,Player->level,Player->xp,(Player->xpOffset - Player->xp));
  printf("\n Press enter to continue \n");
  getchar();
}

void DisplayHelp(){
  printf("\nCOMMANDS AND FUNCTIONS\nPlease type everything with a leading Capital!\nStats - Displays your Attack, Defense, Speed, Current XP, XP until next level, and Health\nRoom - Current Room information\nInventory - Display your current Inventory\nHelp - Displays the Help\nAttack - Attacks the monster if there is one in the room\nAdvance: Moves you to the next room if it is possible\n");
  printf("\n Press enter to continue \n");
  getchar();
}

void printRoomInfo(){
  printf("This is Room %d\n", DRoom -> room);
  if(!DRoom -> roomClear){
    printf("There is a monster in this room\n");
  }
  else{
    printf("There is no monster in this room\n");
  }
  sleep(2);
}

void interpretGame(){
  if(strcasecmp(input,"Help\n") == 0){
    system("clear");
    DisplayHelp();
  }
  else if(strcasecmp(input,"Stats\n") == 0){
    system("clear");
    printStats();
  }
  else if(strcasecmp(input,"Room\n") == 0){
    system("clear");
    printRoomInfo();
  }
  else if(strcasecmp(input,"Attack\n") == 0){
    battle();
  }
  else if(strcasecmp(input,"Advance\n") == 0){
    if(!DRoom -> roomClear){
      printf("The room isn't clear yet!\n");
      sleep(1);
    }
    else{
      printf("You move into the next room\n");
      generateRoom();
    }
  }
  else if(!strcasecmp(input,"Save\n")){
    dump();
    printf("Game saved\n");
  }
  else{
    printf("Sorry, I don't understand that\n");
    sleep(1);
    system("clear");
  }
}

void battle(){
  int roomXp = DRoom -> roomXp;
  if(Enemy->hp <= 0){
    printf("There is no monster in this room\n");
    sleep(1);
  }
  else{
    int dmg;
    if(Player->spd >= Enemy->spd){
      dmg = rand_lim(Player->atk) + Player->atk - Enemy->def;
      if(dmg < 0)
	dmg = 0;
      printf("You dealt %d damage to the %s\n", dmg,Enemy->name);
      Enemy->hp = Enemy->hp - dmg;
      sleep(1);
      if(Enemy->hp > 0){
	dmg = rand_lim(Enemy->atk) + Enemy->atk - Player->def;
	if(dmg < 0)
	  dmg = 0;
	printf("The %s dealt %d damage to you\n", Enemy->name, dmg);
	sleep(1);
	Player->hp = Player->hp - dmg;
      }
      else{
	printf("The %s died!\n", Enemy->name);
	sleep(1);
	DRoom -> roomClear = 1;
	Player->xp = Player->xp + roomXp;
	while(Player->xp >= Player->xpOffset){
	  levelUp();
	}
      }
    }
    else{
      dmg = rand_lim(Enemy->atk) + Enemy->atk - Player->def;
      if(dmg < 0)
	dmg = 0;
      printf("The %s dealt %d damage to you\n", Enemy->name, dmg);
      Player->hp = Player->hp - dmg;
      sleep(1);
      if(Player->hp > 0){
	dmg = rand_lim(Player->atk) + Player->atk - Enemy->def;
	if(dmg < 0)
	  dmg = 0;
	printf("You dealt %d damage to the %s\n", dmg, Enemy->name);
	sleep(1);
	Enemy->hp = Enemy->hp - dmg;
	if(Enemy->hp <= 0){
	  printf("The %s  died!\n", Enemy->name);
	  sleep(1);
	  DRoom -> roomClear = 1;
	  Player->xp = Player->xp + roomXp;
	  while(Player->xp >= Player->xpOffset){
	    levelUp();
	  }
	}
      }
    }
  }
}

void levelUp(){
  int skillPoints = 3;
  Player->level = Player->level + 1;
  printf("You have leveled up. You are now level %d\n", Player->level);
  Player->xp = Player->xp - Player->xpOffset;
  Player->xpOffset = (Player->level * 10);
  while(skillPoints > 0){
    printf("You have %d skill points remaining. What would you like to increase?\n", skillPoints);
    fgets(statUp,sizeof(statUp), stdin);
    skillPoints = skillPoints - 1;
    if(strcmp("Attack\n",statUp) == 0)
      Player->atk = Player->atk + 1;
    else if(strcmp("Defense\n",statUp) == 0)
      Player->def = Player->def + 1;
    else if(strcmp("Speed\n",statUp) == 0)
      Player->spd = Player->spd + 1;
    else if(strcmp("Hp\n",statUp) == 0)
    Player->hp = Player->hp + 1;
    else{
      printf("Sorry, that is not a valid stat.\n");
      skillPoints = skillPoints + 1;
    }
  }
}

void nameGenerator(){
  strcpy(enemyNames[0],"Giant");
  strcpy(enemyNames[1],"Rat");
  strcpy(enemyNames[2],"Skeleton");
}

void dump(){
  int fd = open("savefile.file", O_RDWR | O_CREAT, 0666);
  write(fd, Player, sizeof(Character));
  //DRoom -> Enemy = *Enemy
  write(fd, DRoom, sizeof(Room));
  close(fd);
}
int load(){
  int fd = open("savefile.file", O_RDWR);
  if(fd == -1)
    return -1;
  Player = (Character *) calloc(1, sizeof(Room));
  read(fd, Player, sizeof(Character));
  DRoom = (Room *) calloc(1, sizeof(Room));
  read(fd, DRoom, sizeof(Room));
  Enemy = &(DRoom -> Enemy);
  close(fd);
  return 0;
}
