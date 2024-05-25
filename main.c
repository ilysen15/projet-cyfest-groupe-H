#include "header.h"

int main() {
    Salle* salle = NULL;
    Concert* concert = NULL;
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
                switch (choix_man) {
                    case 1:
                        salle = creer_salle();
                        sauvegarder_salle(salle, "salle.txt");
                        break;
                    case 2:
                        if (salle == NULL) {
                            printf("Vous devez d'abord créer une salle.\n");
                        } else {
                            concert = attribuer_concert(salle);
                            sauvegarder_concert(concert, "concert.txt");
                        }
                        break;
                    case 3:
                        if (salle == NULL) {
                            printf("Vous devez d'abord créer une salle.\n");
                        } else {
                            afficher_etat_salle(salle);
                        }
                        break;
                    case 4:
                        printf("Retour au menu principal.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                        break;
                }
            } while (choix_man != 4);
        }
    } while (choix != 3);

    if (salle) {
        free(salle);
    }
    if (concert) {
        free(concert);
    }

    return 0;
}
