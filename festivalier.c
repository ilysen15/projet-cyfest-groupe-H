#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"festivalier.h"
#define TAILLE 100

// Structures et fonctions de base (déjà existantes)...

// Fonction pour lire les informations d'une salle depuis un fichier
Salle* lire_salle(const char* nom_fichier) {
    FILE *file = fopen(nom_fichier, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
        return NULL;
    }

    Salle* salle = (Salle*)malloc(sizeof(Salle));
    if (!salle) {
        printf("Erreur d'allocation mémoire pour la salle.\n");
        fclose(file);
        return NULL;
    }

    char buffer[100];

    // Lire les informations de la salle depuis le fichier
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "nom: %[^\n]\n", salle->nom);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "nombre_rangees: %d\n", &salle->nombre_rangees);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "le nombre de sièges par rangée: %d\n", &salle->sieges_par_rangee);

    // Allouer de la mémoire pour les rangées de sièges
    salle->rangees = (Siege**)malloc(salle->nombre_rangees * sizeof(Siege*));
    for (int i = 0; i < salle->nombre_rangees; i++) {
        salle->rangees[i] = (Siege*)malloc(salle->sieges_par_rangee * sizeof(Siege));
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            salle->rangees[i][j].reserve = 0;
            salle->rangees[i][j].categorie = 'C'; // Par défaut, catégorie C
        }
    }

    fclose(file);
    return salle;
}

// Fonction pour afficher les sièges d'une salle avec leurs catégories
void afficher_sieges_salle(Salle* salle) {
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

// Fonction pour réserver des sièges et calculer le prix total
float reserver_sieges(Salle* salle, Concert* concert, int rangee, int siege) {
    if (rangee < 0 || rangee >= salle->nombre_rangees || siege < 0 || siege >= salle->sieges_par_rangee) {
        printf("Numéro de rangée ou de siège invalide.\n");
        return 0;
    }
    if (salle->rangees[rangee][siege].reserve) {
        printf("Le siège est déjà réservé.\n");
        return 0;
    } else {
        salle->rangees[rangee][siege].reserve = 1;
        printf("Le siège %d dans la rangée %d a été réservé.\n", siege + 1, rangee + 1);
        
        // Calcul du prix
        float prix = 0;
        switch (salle->rangees[rangee][siege].categorie) {
            case 'A':
                prix = concert->prix_a;
                break;
            case 'B':
                prix = concert->prix_b;
                break;
            case 'C':
                prix = concert->prix_c;
                break;
        }
        return prix;
    }
}

// Fonction pour vérifier si un concert est en cours
int concert_en_cours(Concert* concert, Date date_courante, Heure heure_courante) {
    if ((concert->date_debut.an < date_courante.an || (concert->date_debut.an == date_courante.an && concert->date_debut.mois < date_courante.mois) || 
        (concert->date_debut.an == date_courante.an && concert->date_debut.mois == date_courante.mois && concert->date_debut.jour < date_courante.jour)) &&
        (concert->date_fin.an > date_courante.an || (concert->date_fin.an == date_courante.an && concert->date_fin.mois > date_courante.mois) || 
        (concert->date_fin.an == date_courante.an && concert->date_fin.mois == date_courante.mois && concert->date_fin.jour > date_courante.jour))) {
        return 1;
    }
    return 0;
}

// Fonction pour afficher les salles avec des concerts en cours
void afficher_concerts_en_cours(Concert* concerts, int nombre_concerts, Date date_courante, Heure heure_courante) {
    for (int i = 0; i < nombre_concerts; i++) {
        if (concert_en_cours(&concerts[i], date_courante, heure_courante)) {
            printf("Concert en cours : %s\n", concerts[i].nom);
            afficher_sieges_salle(concerts[i].salle);
        }
    }
}

int choix_festivalier() {
    // Lire les informations de la salle depuis le fichier
    Salle* salle = lire_salle_("salle1.txt");
    if (!salle) {
        return 1;
    }

    // Afficher le plan initial de la salle
    afficher_sieges_salle(salle);

    // Initialiser un concert pour la salle lue
    Concert concerts[1];
    strcpy(concerts[0].nom, "Concert Rock");
    concerts[0].salle = salle;
    concerts[0].prix_a = 100.0f;
    concerts[0].prix_b = 75.0f;
    concerts[0].prix_c = 50.0f;
    concerts[0].date_debut = (Date){24, 5, 2024};
    concerts[0].date_fin = (Date){25, 5, 2024};
    concerts[0].heure_debut = (Heure){19, 0, 0};
    concerts[0].heure_fin = (Heure){22, 0, 0};

    // Définir la date et l'heure actuelles
    Date date_courante = {24, 5, 2024};
    Heure heure_courante = {20, 0, 0};

    // Afficher les concerts en cours
    afficher_concerts_en_cours(concerts, 1, date_courante, heure_courante);

    // Réservation de sièges
    float total_prix = 0;
    total_prix += reserver_sieges(salle, &concerts[0], 0, 0);
    total_prix += reserver_sieges(salle, &concerts[0], 0, 1);

    // Afficher le plan de la salle après les réservations
    afficher_sieges_salle(salle);
    printf("Prix total des places réservées : %.2f\n", total_prix);

    // Libérer la mémoire
    
    for (int i = 0; i < salle->nombre_rangees; i++) {
        free(salle->rangees[i]);
    }
    free(salle->rangees);
    free(salle);


}
