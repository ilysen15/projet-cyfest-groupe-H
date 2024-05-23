#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Mode Manager\n");
    printf("2. Mode Festivalier\n");
    printf("3. Quitter\n");
    printf("======================\n");
}


void modeManager() {
    printf("\n--- Mode Manager ---\n");
}


void modeFestivalier() {
    printf("\n--- Mode Festivalier ---\n");
}



int main() {
    int choix;

    while (choix<1 || choix>3) {
        afficherMenu();
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                modeManager();
                break;
            case 2:
                modeFestivalier();
                break;
            case 3:
                printf("Reviens quand tu veux !\n");
                exit(0);
            default:
                printf("Erreur, réessaye.\n");
        }
    }

    return 0;
}
