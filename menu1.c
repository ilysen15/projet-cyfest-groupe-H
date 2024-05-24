#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "festivalier.h"
#include "maneger.h"

int afficherMenu() {
    int choix;
    printf("\n=== Menu ===\n");
    printf("quel mode souhaitez vous utiliser?\n");
    printf("1. Mode Manager\n");
    printf("2. Mode Festivalier\n");
    printf("3. Quitter\n");
    printf("======================\n");
    
  do{
      printf("Mode : ");
      scanf("%d", &choix);
  }while(choix<0 || choix>3);
  
  if(choix = 1){
      return 1;
  }
  else if(choix = 2){
      return 2;
  }
  else{
      return 3;
  }
  
  return 0 ;
}
