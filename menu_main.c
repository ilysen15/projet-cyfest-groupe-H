#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "festivalier.h"
#include "maneger.h"

int main() {
    int choix;

   do{
   
    printf("\n=== Menu ===\n");
    printf("quel mode souhaitez vous utiliser?\n");
    printf("1. Mode Manager\n");
    printf("2. Mode Festivalier\n");
    printf("3. Quitter\n");
    printf("======================\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                choix_manager();
                break;
            case 2:
               choix_festivalier();
                break;
            case 3:
                printf("Reviens quand tu veux !\n");
                exit(0);
            default:
                printf("Erreur, réessaye.\n");
        } while (choix<1 || choix>3) {
    }

    return 0;
}
