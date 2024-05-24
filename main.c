#include <stdio.h>
#include<stdlib.h>
#include "manegar.h"
#include <string.h>
#include<menu.h>

int main() {
    // Création d'une salle
    Salle* ma_salle = creer_salle("Grande Salle", 20, 50, 5, 10, 1);

    // Attribution d'un concert à la salle
    Concert* mon_concert = attribuer_concert(ma_salle, "Concert de Rock", 100.0, 75.0, 50.0, "23:00");

    // Affichage de l'état de la salle
    afficher_etat_salle(ma_salle);

    // Libération de la mémoire
    liberer_concert(mon_concert);
    liberer_salle(ma_salle);

    return 0;
}

// Définition des fonctions

Salle* creer_salle(const char* nom, int nombre_rangees, int sieges_par_rangee, int nombre_rangees_a, int nombre_rangees_b, int a_fosse) {
    Salle* salle = (Salle*)malloc(sizeof(Salle));
    if (!salle) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la salle.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(salle->nom, nom);
    salle->nombre_rangees = nombre_rangees;
    salle->sieges_par_rangee = sieges_par_rangee;
    salle->nombre_rangees_a = nombre_rangees_a;
    salle->nombre_rangees_b = nombre_rangees_b;
    salle->a_fosse = a_fosse;

    salle->sieges = (Siege*)malloc(nombre_rangees * sieges_par_rangee * sizeof(Siege));
    if (!salle->sieges) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les sièges.\n");
        free(salle);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nombre_rangees; i++) {
        char categorie = 'C';
        if (a_fosse && i < nombre_rangees_a) {
            categorie = 'P';
        } else if (!a_fosse) {
            if (i < nombre_rangees_a) {
                categorie = 'A';
            } else if (i < nombre_rangees_a + nombre_rangees_b) {
                categorie = 'B';
            }
        }
        for (int j = 0; j < sieges_par_rangee; j++) {
            int index = i * sieges_par_rangee + j;
            salle->sieges[index].reserve = 0;
            salle->sieges[index].categorie = categorie;
        }
    }

    return salle;
}

Concert* attribuer_concert(Salle* salle, const char* nom, float prix_a, float prix_b, float prix_c, const char* heure_fin) {
    Concert* concert = (Concert*)malloc(sizeof(Concert));
    if (!concert) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le concert.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(concert->nom, nom);
    concert->salle = salle;
    concert->prix_a = prix_a;
    concert->prix_b = prix_b;
    concert->prix_c = prix_c;
    strcpy(concert->heure_fin, heure_fin);

    return concert;
}

void afficher_etat_salle(Salle* salle) {
    int total_sieges = salle->nombre_rangees * salle->sieges_par_rangee;
    int sieges_reserves = 0;
    for (int i = 0; i < total_sieges; i++) {
        if (salle->sieges[i].reserve) {
            sieges_reserves++;
        }
    }
    printf("Salle: %s\n", salle->nom);
    printf("Total de sièges: %d, Sièges réservés: %d\n", total_sieges, sieges_reserves);
    printf("Ratio de réservation: %.2f%%\n", (float)sieges_reserves / total_sieges * 100);
}

void liberer_salle(Salle* salle) {
    free(salle->sieges);
    free(salle);
}

void liberer_concert(Concert* concert) {
    free(concert);
}



