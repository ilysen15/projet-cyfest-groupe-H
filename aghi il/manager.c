
#include "header.h"

// Fonction pour créer une salle
Salle* creer_salle() {
    Salle* salle = (Salle*)malloc(sizeof(Salle));
    if (!salle) {
        printf("Erreur d'allocation mémoire pour la salle.\n");
        return NULL;
    }

    printf("Nom de la salle : ");
    scanf("%s", salle->nom);
    printf("Nombre de rangées : ");
    scanf("%d", &salle->nombre_rangees);
    printf("Nombre de sièges par rangée : ");
    scanf("%d", &salle->sieges_par_rangee);

    salle->rangees = (Siege**)malloc(salle->nombre_rangees * sizeof(Siege*));
    for (int i = 0; i < salle->nombre_rangees; i++) {
        salle->rangees[i] = (Siege*)malloc(salle->sieges_par_rangee * sizeof(Siege));
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            salle->rangees[i][j].reserve = 0;
            salle->rangees[i][j].categorie = 'C'; // Par défaut, catégorie C
        }
    }

    return salle;
}

// Fonction pour attribuer un concert à une salle
Concert* attribuer_concert(Salle* salle) {
    Concert* concert = (Concert*)malloc(sizeof(Concert));
    if (!concert) {
        printf("Erreur d'allocation mémoire pour le concert.\n");
        return NULL;
    }

    printf("Nom du concert : ");
    scanf("%s", concert->nom);
    concert->salle = salle;
    printf("Prix catégorie A : ");
    scanf("%f", &concert->prix_a);
    printf("Prix catégorie B : ");
    scanf("%f", &concert->prix_b);
    printf("Prix catégorie C : ");
    scanf("%f", &concert->prix_c);
    printf("Heure de début (hh mm ss) : ");
    scanf("%d %d %d", &concert->heure_debut.heure, &concert->heure_debut.min, &concert->heure_debut.sec);
    printf("Heure de fin (hh mm ss) : ");
    scanf("%d %d %d", &concert->heure_fin.heure, &concert->heure_fin.min, &concert->heure_fin.sec);
    printf("Date de début (jj mm aaaa) : ");
    scanf("%d %d %d", &concert->date_debut.jour, &concert->date_debut.mois, &concert->date_debut.an);
    printf("Date de fin (jj mm aaaa) : ");
    scanf("%d %d %d", &concert->date_fin.jour, &concert->date_fin.mois, &concert->date_fin.an);

    return concert;
}

// Fonction pour afficher l'état des sièges d'une salle
void afficher_etat_salle(Salle* salle) {
    printf("Plan de la salle : %s\n", salle->nom);
    for (int i = 0; i < salle->nombre_rangees; i++) {
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            if (salle->rangees[i][j].reserve) {
                printf("$ "); // Siège réservé
            } else {
                printf("%c ", salle->rangees[i][j].categorie); // Afficher la catégorie du siège
            }
        }
        printf("\n");
    }
}


// Menu pour les managers
int choix_manager() {
    printf("Menu Manager\n");
    printf("1. Créer une salle\n");
    printf("2. Attribuer un concert à une salle\n");
    printf("3. Afficher l'état des sièges d'une salle\n");
    printf("4. Quitter\n");

    int choix;
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}
