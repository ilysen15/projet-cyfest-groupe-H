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

void afficher_sieges_salle(Salle* salle) {
    printf("Plan de la salle : %s\n", salle->nom);
    for (int i = 0; i < salle->nombre_rangees; i++) {
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            
            if (verifier_reservation(salle->nom, i, j)) {
                printf("R "); // Siège réservé
            } else {
                printf("%c ", salle->rangees[i][j].categorie); // Afficher la catégorie du siège
            }
        }
        printf("\n");
    }
}
int verifier_reservation(const char* nom_fichier, int rangee, int siege) {
    const char* dossier = "reservation/";
    const char* txt = ".txt";
    char chemin[256];

    // Initialiser le chemin avec le dossier
    strcpy(chemin, dossier);
    // Ajouter le nom du fichier
    strcat(chemin, nom_fichier);
    // Ajouter l'extension
    strcat(chemin, txt);

    FILE* file = fopen(chemin, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", chemin);
        return 0; // Retourne 0 si le fichier ne peut pas être ouvert
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        int ligne_rangee, ligne_siege;
        sscanf(buffer, "Siège réservé: Rangée %d Siège %d\n",
               &ligne_siege, &ligne_rangee);
        
        
        if (ligne_siege == siege && ligne_rangee == rangee) {
            fclose(file);
            return 1;  // Réservation trouvée
        }
    }
    fclose(file);
    return 0;  // Réservation non trouvée
}
float reserver_sieges(Salle* salle, Concert* concert, int rangee, int siege, const char* nom, const char* prenom) {
    if (rangee < 0 || rangee >= salle->nombre_rangees || siege < 0 || siege >= salle->sieges_par_rangee) {
        printf("Numéro de rangée ou de siège invalide.\n");
        return 0;
    }
    if (verifier_reservation(salle->nom, rangee, siege)) {
        printf("Le siège est déjà réservé.\n");
        return 0;
    } else {
        salle->rangees[rangee][siege].reserve = 1;
        printf("Le siège %d dans la rangée %d a été réservé.\n", siege, rangee);
       
        // Enregistrement de la réservation dans le fichier de la salle
        FILE* salle_file = fopen("reservation.txt", "a");
        if (salle_file != NULL) {
            fprintf(salle_file, "Réservation pour %s %s, Siège: %d, Rangée: %d, Concert: %s\n", nom, prenom, siege, rangee, concert->nom);
            fclose(salle_file);
        } else {
            printf("Erreur lors de l'ouverture du fichier de réservation de la salle.\n");
        }
        
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

        sauvegarder_reservation(nom, prenom,salle->nom,rangee, siege);

        return prix;
    }
}

void sauvegarder_reservation(const char* nom, const char* prenom, const char* nom_salle, int rangee, int siege) {
    char nom_fichier[100];
    sprintf(nom_fichier, "reservation/%s.txt", nom_salle);
    FILE *file = fopen(nom_fichier, "a");
    if (file) {
        fprintf(file, "Nom: %s\n", nom);
        fprintf(file, "Prénom: %s\n", prenom);
        fprintf(file, "Siège réservé: Rangée %d Siège %d\n\n", rangee, siege);
        fclose(file);
        printf("Informations de réservation sauvegardées dans %s.\n", nom_fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
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
            printf("Nom du concert : %s\n", concerts[i].nom);
            printf("Heure de début : %d:%d:%d\n", concerts[i].heure_debut.heure, concerts[i].heure_debut.min, concerts[i].heure_debut.sec);
            printf("Heure de fin : %d:%d:%d\n", concerts[i].heure_fin.heure, concerts[i].heure_fin.min, concerts[i].heure_fin.sec);
            printf("Date de début : %d/%d/%d\n", concerts[i].date_debut.jour, concerts[i].date_debut.mois, concerts[i].date_debut.an);
            printf("Date de fin : %d/%d/%d\n", concerts[i].date_fin.jour, concerts[i].date_fin.mois, concerts[i].date_fin.an);
            printf("Salle : %s\n", concerts[i].salle->nom);
            printf("Prix A : %.2f\n", concerts[i].prix_a);
            printf("Prix B : %.2f\n", concerts[i].prix_b);
            printf("Prix C : %.2f\n\n", concerts[i].prix_c);
        }
    }
}

Concert lire_concert(const char* nom_fichier) {
    FILE *file = fopen(nom_fichier, "r");
    Concert concert;
    if (file) {
        // Lire chaque ligne du fichier et stocker les informations dans la structure Concert
        fscanf(file, "nom: %[^\n]", concert.nom);
        fscanf(file, "prix_a: %f", &concert.prix_a);
        fscanf(file, "prix_b: %f", &concert.prix_b);
        fscanf(file, "prix_c: %f", &concert.prix_c);
        fscanf(file, "heure_debut: %d %d %d", &concert.heure_debut.heure, &concert.heure_debut.min, &concert.heure_debut.sec);
        fscanf(file, "heure_fin: %d %d %d", &concert.heure_fin.heure, &concert.heure_fin.min, &concert.heure_fin.sec);
        fscanf(file, "date_debut: %d %d %d", &concert.date_debut.jour, &concert.date_debut.mois, &concert.date_debut.an);
        fscanf(file, "date_fin: %d %d %d", &concert.date_fin.jour, &concert.date_fin.mois, &concert.date_fin.an);
        // Lire le champ "salle_nom" si nécessaire
        char salle_nom[100];
        if (fscanf(file, "salle_nom: %s", salle_nom) == 1) {
            // Utilisez salle_nom pour initialiser le champ salle de la structure Concert si nécessaire
        }
        fclose(file);
    }
    return concert;
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
