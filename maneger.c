#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "managar.h>

// Structure pour un siège
typedef struct {
    char categorie;  // 'A', 'B', 'C', ou 'P' pour Pit (fosse)
    int reserve;     // 0 pour libre, 1 pour réservé
} Siege;

// Structure pour une rangée de sièges
typedef struct {
    Siege *sieges;   // Tableau de sièges
    int nombre_sieges; // Nombre de sièges dans la rangée
} Rangee;

// Structure pour une salle de concert
typedef struct {
    char nom[TAILLE];   // Nom de la salle
    int nombre_rangees; // Nombre de rangées
    int sieges_par_rangee; // Nombre de sièges par rangée
    Rangee *rangees; // Tableau de rangées
    int nombre_rangees_a; // Nombre de rangées en catégorie A
    int nombre_rangees_b; // Nombre de rangées en catégorie B
} Salle;

// Structure pour un concert
typedef struct {
    char nom[TAILLE];  // Nom du concert
    Salle *salle;   // Pointeur vers la salle
    int a_fosse;    // 0 pour non, 1 pour oui
    double prix_a;  // Prix pour catégorie A
    double prix_b;  // Prix pour catégorie B
    double prix_c;  // Prix pour catégorie C
    char heure_fin[10]; // Heure de fin du concert
} Concert;

// Fonction pour créer une salle
Salle* creer_salle(const char* nom, int nombre_rangees, int sieges_par_rangee) {
    Salle* salle = (Salle*)malloc(sizeof(Salle));
    strcpy(salle->nom, nom);
    salle->nombre_rangees = nombre_rangees;
    salle->sieges_par_rangee = sieges_par_rangee;
    salle->rangees = (Rangee*)malloc(nombre_rangees * sizeof(Rangee));

    for (int i = 0; i < nombre_rangees; i++) {
        salle->rangees[i].sieges = (Siege*)malloc(sieges_par_rangee * sizeof(Siege));
        salle->rangees[i].nombre_sieges = sieges_par_rangee;
        for (int j = 0; j < sieges_par_rangee; j++) {
            salle->rangees[i].sieges[j].reserve = 0;
            salle->rangees[i].sieges[j].categorie = 'C';
        }
    }

    return salle;
}

// Fonction pour configurer les catégories de sièges
void configurer_categories(Salle* salle, int nombre_rangees_a, int nombre_rangees_b) {
    salle->nombre_rangees_a = nombre_rangees_a;
    salle->nombre_rangees_b = nombre_rangees_b;

    for (int i = 0; i < salle->nombre_rangees; i++) {
        char categorie = 'C';
        if (i < nombre_rangees_a) {
            categorie = 'A';
        } else if (i < nombre_rangees_a + nombre_rangees_b) {
            categorie = 'B';
        }
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            salle->rangees[i].sieges[j].categorie = categorie;
        }
    }
}

// Fonction pour attribuer un concert à une salle
Concert* attribuer_concert(Salle* salle, const char* nom, int a_fosse, double prix_a, double prix_b, double prix_c, const char* heure_fin) {
    Concert* concert = (Concert*)malloc(sizeof(Concert));
    strcpy(concert->nom, nom);
    concert->salle = salle;
    concert->a_fosse = a_fosse;
    concert->prix_a = prix_a;
    concert->prix_b = prix_b;
    concert->prix_c = prix_c;
    strcpy(concert->heure_fin, heure_fin);

    if (a_fosse) {
        for (int i = 0; i < salle->nombre_rangees_a; i++) {
            for (int j = 0; j < salle->sieges_par_rangee; j++) {
                salle->rangees[i].sieges[j].categorie = 'P'; // 'P' pour Pit (fosse)
            }
        }
    }

    return concert;
}

// Fonction pour afficher l'état d'une salle
void afficher_etat_salle(Salle* salle) {
    int total_sieges = salle->nombre_rangees * salle->sieges_par_rangee;
    int sieges_reserves = 0;
    for (int i = 0; i < salle->nombre_rangees; i++) {
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            if (salle->rangees[i].sieges[j].reserve) {
                sieges_reserves++;
            }
        }
    }
    printf("Salle: %s\n", salle->nom);
    printf("Total de sièges: %d, Sièges réservés: %d\n", total_sieges, sieges_reserves);
    printf("Ratio de réservation: %.2f%%\n", (double)sieges_reserves / total_sieges * 100);
}

// Fonction pour libérer la mémoire d'une salle
void liberer_salle(Salle* salle) {
    for (int i = 0; i < salle->nombre_rangees; i++) {
        free(salle->rangees[i].sieges);
    }
    free(salle->rangees);
    free(salle);
}

// Fonction pour libérer la mémoire d'un concert
void liberer_concert(Concert* concert) {
    free(concert);
}

