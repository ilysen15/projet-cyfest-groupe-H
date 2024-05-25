#include "header.h"

int main() {
    int choix;
    do {
        printf("Menu Principal\n");
        printf("1. Menu Festivalier\n");
        printf("2. Menu Manager\n");
        printf("3. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            int choix_fest;
            do {
                choix_fest = choix_festivalier();
                // Gérer les choix du festivalier ici
            } while (choix_fest != 4);
        } else if (choix == 2) {
            int choix_man;
            do {
                choix_man = choix_manager();
                // Gérer les choix du manager ici
            } while (choix_man != 4);
        }
    } while (choix != 3);

    return 0;
}