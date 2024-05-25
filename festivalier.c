#include "header.h"

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
    if ((concert->date_debut.an < date_courante.an || 
        (concert->date_debut.an == date_courante.an && concert->date_debut.mois < date_courante.mois) ||
        (concert->date_debut.an == date_courante.an && concert->date_debut.mois == date_courante.mois && concert->date_debut.jour < date_courante.jour)) &&
        (concert->date_fin.an > date_courante.an || 
        (concert->date_fin.an == date_courante.an && concert->date_fin.mois > date_courante.mois) ||
        (concert->date_fin.an == date_courante.an && concert->date_fin.mois == date_courante.mois && concert->date_fin.jour > date_courante.jour))) {
        return 1;
    } else if ((concert->date_debut.jour == date_courante.jour) && (concert->date_debut.mois == date_courante.mois) && (concert->date_debut.an == date_courante.an) && 
    (concert->heure_debut.heure < heure_courante.heure || 
    (concert->heure_debut.heure == heure_courante.heure && concert->heure_debut.min < heure_courante.min) || 
    (concert->heure_debut.heure == heure_courante.heure && concert->heure_debut.min == heure_courante.min && concert->heure_debut.sec <= heure_courante.sec))) {
        return 1;
    }
    return 0;
}

// Fonction pour afficher les concerts en cours
void afficher_concerts_en_cours(Concert* concerts, int nombre_concerts, Date date_courante, Heure heure_courante) {
    printf("Concerts en cours :\n");
    for (int i = 0; i < nombre_concerts; i++) {
        if (concert_en_cours(&concerts[i], date_courante, heure_courante)) {
            printf("%s\n", concerts[i].nom);
        }
    }
}

// Menu pour les festivaliers
int choix_festivalier() {
    printf("Menu Festivalier\n");
    printf("1. Réserver des sièges\n");
    printf("2. Afficher les sièges d'une salle\n");
    printf("3. Afficher les concerts en cours\n");
    printf("4. Quitter\n");

    int choix;
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}
