#include "headers.h"

char buffer[256];

int main(){
  while(1){
    printf("Welcome\n");
    fgets(buffer, sizeof(buffer), stdin);
    if(strcmp("Play\n", buffer) == 0){
      printf("Game is Go\n");
    }
    else if(strcmp("Exit\n",buffer) == 0){
      printf("Goodbye\n");
      break;
    }
    else{
      printf("Sorry. I do not understand what you said\n");
    }
  }
  return 1;
}
