#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"manager.h"


void Listesalle() {
    FILE *f1 = fopen("salle1.txt", "r");
    FILE *f2 = fopen("salle2.txt", "r");
    FILE *f3 = fopen("salle3.txt", "r");

    char nom[TAILLE];
    int nb_rangees;
    int nb_sieges_par_rangee;
    int nb_rangees_A;
    int nb_rangees_B;
    char artiste[TAILLE];
    char date[TAILLE];
    char heure[TAILLE];

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("Voici la liste des salles disponibles :\n");
    printf("----------------------------------------\n");

    void lire_et_afficher(FILE *f) {
        fscanf(f, "nom: %[^\n]\n", nom);
        fscanf(f, "nombre_rangees: %d\n", &nb_rangees);
        fscanf(f, "le nombre de sièges par rangée: %d\n", &nb_sieges_par_rangee);
        fscanf(f, "le nombre de rangées pour la catégorie A: %d\n", &nb_rangees_A);
        fscanf(f, "le nombre de rangées pour la catégorie B: %d\n", &nb_rangees_B);
        fscanf(f, "CONCERT :\n");
        fscanf(f, "Artiste : %[^\n]\n", artiste);
        fscanf(f, "Date : %[^\n]\n", date);
        fscanf(f, "Heure : %[^\n]\n", heure);

        printf("Nom de la salle : %s\n", nom);
        printf("Nombre de rangées : %d\n", nb_rangees);
        printf("Nombre de sièges par rangée : %d\n", nb_sieges_par_rangee);
        printf("Nombre de rangées pour la catégorie A : %d\n", nb_rangees_A);
        printf("Nombre de rangées pour la catégorie B : %d\n", nb_rangees_B);
        printf("Artiste : %s\n", artiste);
        printf("Date : %s\n", date);
        printf("Heure : %s\n", heure);
        printf("----------------------------------------\n");
    }

    lire_et_afficher(f1);
    lire_et_afficher(f2);
    lire_et_afficher(f3);

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

Salle* creer_salle() {
    Salle* s = (Salle*)malloc(sizeof(Salle));

    printf("Entrer le nom de la salle : ");
    scanf("%s", s->nom);
    printf("Entrer le nombre de rangées : ");
    scanf("%d", &s->nombre_rangees);
    printf("Entrer le nombre de sièges par rangée : ");
    scanf("%d", &s->sieges_par_rangee);
    printf("Entrer le nombre de sièges pour la catégorie A : ");
    scanf("%d", &s->sieges_A);
    printf("Entrer le nombre de sièges pour la catégorie B : ");
    scanf("%d", &s->sieges_B);
    printf("Entrer le nombre de sièges pour la catégorie C : ");
    scanf("%d", &s->sieges_C);

    return s;
}

Concert* attribuer_concert(Salle* salle) {
    Concert* concert = (Concert*)malloc(sizeof(Concert));

    printf("Entrer le nom du concert : ");
    scanf("%s", concert->nom);
    printf("Entrer le nom du chanteur : ");
    scanf("%s", concert->nom_chanteur);
    concert->salle = salle;
    printf("Le concert aura-t-il une fosse (0 pour non, 1 pour oui) ? ");
    scanf("%d", &concert->fosse);
    printf("Entrer le prix pour la catégorie A : ");
    scanf("%f", &concert->prix_a);
    printf("Entrer le prix pour la catégorie B : ");
    scanf("%f", &concert->prix_b);
    printf("Entrer le prix pour la catégorie C : ");
    scanf("%f", &concert->prix_c);
    printf("Entrer l'heure de début (hh mm ss) : ");
    scanf("%d %d %d", &concert->heure_debut.heure, &concert->heure_debut.min, &concert->heure_debut.sec);
    printf("Entrer l'heure de fin (hh mm ss) : ");
    scanf("%d %d %d", &concert->heure_fin.heure, &concert->heure_fin.min, &concert->heure_fin.sec);
    printf("Entrer la date du concert (jj mm aaaa) : ");
    scanf("%d %d %d", &concert->date.jour, &concert->date.mois, &concert->date.an);

    return concert;
}

void afficher_etat_salle(Salle* salle) {
    printf("Salle: %s\n", salle->nom);
    printf("Nombre de rangées: %d\n", salle->nombre_rangees);
    printf("Nombre de sièges par rangée: %d\n", salle->sieges_par_rangee);
    printf("Sièges en catégorie A: %d\n", salle->sieges_A);
    printf("Sièges en catégorie B: %d\n", salle->sieges_B);
    printf("Sièges en catégorie C: %d\n", salle->sieges_C);
}

int main() {
    int choix;
    Salle* salle = NULL;
    Concert* concert = NULL;

    while (1) {
        printf("Menu:\n");
        printf("1. Afficher les salles existantes et choisir une salle\n");
        printf("2. Créer une nouvelle salle et y attribuer un concert\n");
        printf("3. Afficher l'état de la salle\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                Listesalle();
                printf("Choisissez une salle existante (1, 2, 3) ou 0 pour retourner au menu principal : ");
                int salle_choix;
                scanf("%d", &salle_choix);
                if (salle_choix == 0) {
                    break;
                } else if (salle_choix == 1 || salle_choix == 2 || salle_choix == 3) {
                    salle = creer_salle();
                    concert = attribuer_concert(salle);
                } else {
                    printf("Choix invalide. Retour au menu principal.\n");
                }
                break;
            case 2:
                salle = creer_salle();
                concert = attribuer_concert(salle);
                break;
            case 3:
                if (salle != NULL) {
                    afficher_etat_salle(salle);
                } else {
                    printf("Veuillez d'abord créer ou choisir une salle.\n");
                }
                break;
            case 4:
                if (salle != NULL) {
                    free(salle);
                }
                if (concert != NULL) {
                    free(concert);
                }
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}

