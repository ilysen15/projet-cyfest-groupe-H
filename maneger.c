#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char categorie;  // 'A', 'B', 'C', ou 'P' pour Pit (fosse)
    int reserve;     // 0 pour libre, 1 pour réservé
} Siege;

typedef struct {
    Siege *sieges;
    int nombre_sieges;
} Rangee;

typedef struct {
    char nom[100];  // Utilisation d'un tableau de char pour stocker le nom de la salle
    int nombre_rangees; // Nombre de rangées
    int sieges_par_rangee;  // Nombre de sièges par rangée
    Rangee *rangees;
    int nombre_rangees_a;
    int nombre_rangees_b;
} Salle;

typedef struct {
    char nom[100];
    Salle *salle;
    int a_fosse;    // 0 pour non, 1 pour oui
    double prix_a;
    double prix_b;
    double prix_c;
    char heure_fin[10];
} Concert;

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
                salle->rangees[i].sieges[j].categorie = 'P'; // P pour Pit (fosse)
            }
        }
    }

    return concert;
}

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

void liberer_salle(Salle* salle) {
    for (int i = 0; i < salle->nombre_rangees; i++) {
        free(salle->rangees[i].sieges);
    }
    free(salle->rangees);
    free(salle);
}

void liberer_concert(Concert* concert) {
    free(concert);
}

int main() {
    int nombre_salles;
    printf("Entrer le nombre de salles : ");
    scanf("%d", &nombre_salles);

    Salle** salles = (Salle*)malloc(nombre_salles * sizeof(Salle));

    for (int i = 0; i < nombre_salles; i++) {
        char nom[100];
        int nombre_rangees, sieges_par_rangee, nombre_rangees_a, nombre_rangees_b;

        printf("Entrer le nom de la salle %d : ", i + 1);
        scanf("%s", nom);
        fgets(nom, 50, stdin);
        nom[strlen(nom) - 1] = '\0';
        printf("Entrer le nombre de rangées pour la salle %d : ", i + 1);
        scanf("%d", &nombre_rangees);
        printf("Entrer le nombre de sièges par rangée pour la salle %d : ", i + 1);
        scanf("%d", &sieges_par_rangee);
        printf("Entrer le nombre de rangées pour la catégorie A pour la salle %d : ", i + 1);
        scanf("%d", &nombre_rangees_a);
        printf("Entrer le nombre de rangées pour la catégorie B pour la salle %d : ", i + 1);
        scanf("%d", &nombre_rangees_b);
       
        // ouvrir le fichier
       FILE *fp = fopen("salle.txt", "a"); 

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "nom: %s\n nombre_rangees: %d\n le nombre de sièges par rangée: %d\n le nombre de rangées pour la catégorie A: %d\n le nombre de rangées pour la catégorie B: %d\n\n", nom, nombre_rangees, sieges_par_rangee,nombre_rangees_a, nombre_rangees_b);
        
    fclose(fp);

        salles[i] = creer_salle(nom, nombre_rangees, sieges_par_rangee);
        configurer_categories(salles[i], nombre_rangees_a, nombre_rangees_b);
    }

    // Attribuer un concert à la première salle comme exemple
    Concert* concert = attribuer_concert(salles[0], "Concert Rock", 1, 100.0, 75.0, 50.0, "22:00");
    afficher_etat_salle(salles[0]);

    // Libérer la mémoire
    liberer_concert(concert);
    for (int i = 0; i < nombre_salles; i++) {
        liberer_salle(salles[i]);
    }
    free(salles);

    return 0;
}



