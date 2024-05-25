#include "header.h"

// Fonction pour sauvegarder une salle dans un fichier
void sauvegarder_salle(Salle* salle, const char* nom_fichier) {
    FILE *file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
        return;
    }

    fprintf(file, "nom: %s\n", salle->nom);
    fprintf(file, "nombre_rangees: %d\n", salle->nombre_rangees);
    fprintf(file, "le nombre de sièges par rangée: %d\n", salle->sieges_par_rangee);

    for (int i = 0; i < salle->nombre_rangees; i++) {
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            fprintf(file, "siege: %d %d %c %d\n", i, j, salle->rangees[i][j].categorie, salle->rangees[i][j].reserve);
        }
    }

    fclose(file);
}

// Fonction pour charger une salle depuis un fichier
Salle* charger_salle(const char* nom_fichier) {
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

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "nom: %[^\n]\n", salle->nom);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "nombre_rangees: %d\n", &salle->nombre_rangees);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "le nombre de sièges par rangée: %d\n", &salle->sieges_par_rangee);

    salle->rangees = (Siege**)malloc(salle->nombre_rangees * sizeof(Siege*));
    for (int i = 0; i < salle->nombre_rangees; i++) {
        salle->rangees[i] = (Siege*)malloc(salle->sieges_par_rangee * sizeof(Siege));
        for (int j = 0; j < salle->sieges_par_rangee; j++) {
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "siege: %d %d %c %d\n", &i, &j, &salle->rangees[i][j].categorie, &salle->rangees[i][j].reserve);
        }
    }

    fclose(file);
    return salle;
}

// Fonction pour sauvegarder un concert dans un fichier
void sauvegarder_concert(Concert* concert, const char* nom_fichier) {
    FILE *file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
        return;
    }

    fprintf(file, "nom: %s\n", concert->nom);
    fprintf(file, "prix_a: %.2f\n", concert->prix_a);
    fprintf(file, "prix_b: %.2f\n", concert->prix_b);
    fprintf(file, "prix_c: %.2f\n", concert->prix_c);

    fprintf(file, "heure_debut: %d %d %d\n", concert->heure_debut.heure, concert->heure_debut.min, concert->heure_debut.sec);
    fprintf(file, "heure_fin: %d %d %d\n", concert->heure_fin.heure, concert->heure_fin.min, concert->heure_fin.sec);

    fprintf(file, "date_debut: %d %d %d\n", concert->date_debut.jour, concert->date_debut.mois, concert->date_debut.an);
    fprintf(file, "date_fin: %d %d %d\n", concert->date_fin.jour, concert->date_fin.mois, concert->date_fin.an);

    fprintf(file, "salle_nom: %s\n", concert->salle->nom);

    fclose(file);
}

// Fonction pour charger un concert depuis un fichier
Concert* charger_concert(const char* nom_fichier, Salle* salle) {
    FILE *file = fopen(nom_fichier, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
        return NULL;
    }

    Concert* concert = (Concert*)malloc(sizeof(Concert));
    if (!concert) {
        printf("Erreur d'allocation mémoire pour le concert.\n");
        fclose(file);
        return NULL;
    }

    char buffer[100];

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "nom: %[^\n]\n", concert->nom);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "prix_a: %f\n", &concert->prix_a);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "prix_b: %f\n", &concert->prix_b);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "prix_c: %f\n", &concert->prix_c);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "heure_debut: %d %d %d\n", &concert->heure_debut.heure, &concert->heure_debut.min, &concert->heure_debut.sec);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "heure_fin: %d %d %d\n", &concert->heure_fin.heure, &concert->heure_fin.min, &concert->heure_fin.sec);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "date_debut: %d %d %d\n", &concert->date_debut.jour, &concert->date_debut.mois, &concert->date_debut.an);

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "date_fin: %d %d %d\n", &concert->date_fin.jour, &concert->date_fin.mois, &concert->date_fin.an);

    concert->salle = salle;

    fclose(file);
    return concert;
}
