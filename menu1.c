#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "festivalier.h"
#include "maneger.h"

nt main() {
    int choix;

    while (choix<1 || choix>3) {
        afficherMenu();
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
        }
    }

    return 0;
}
