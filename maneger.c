#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 100
 
//structure pour la date de concert
typedef struct{
int jour;
int mois;
int an;
}Date;
 

//structure l'heure de debut de la fin de concert
typedef struct{
int heure[23];
int min[59];
int sec[59];
}Heure;

// Structure pour un siège
typedef struct {
    char categorie;  // 'A', 'B', 'C', ou 'P' pour Pit (fosse)
    int reserve;     // 0 pour libre, 1 pour réservé
} Siege;

// Structure pour une salle de concert
typedef struct {
    char nom[TAILLE];   // Nom de la salle
    int nombre_rangees; // Nombre de rangées
    int siege_range;    // Nombre de sièges par rangée
    int siege_A;        // Nombre de sièges dans la catégorie A
    int siege_B;        // Nombre de sièges dans la catégorie B
    int siege_C;        // Nombre de sièges dans la catégorie C
} Salle;

// Structure pour un concert
typedef struct {
    char nom[TAILLE];  // Nom du concert
    Salle *salle;      // Pointeur vers la salle
    int   fosse;       // 0 pour non, 1 pour oui
    float prix_a;      // Prix pour catégorie A
    float prix_b;      // Prix pour catégorie B
    float prix_c;      // Prix pour catégorie C
    Heure * heure_debut; // Heure de debut du concert
    Heure * heure_fin; // Heure de fin du concert
    Date *date_debut; //date de debut de concert 
    Date *date_fin;//date de fin de concert
} Concert;

// Fonction pour créer une salle
Salle *creer_salle(){
    int nombre_salles;
    printf("Entrer le nombre de salles : ");
    scanf("%d", &nombre_salles);

    Salle* s = (Salle*)malloc(nombre_salles * sizeof(Salle));

    for (int i = 0; i < nombre_salles; i++) {
        printf("Entrer le nom de la salle %d : ", i + 1);
        scanf("%s", s[i].nom);
        printf("Entrer le nombre de rangées pour la salle %d : ", i + 1);
        scanf("%d", &s[i].nombre_rangees);
        printf("Entrer le nombre de sièges par rangée pour la salle %d : ", i + 1);
        scanf("%d", &s[i].siege_range);
        printf("Entrer le nombre de sièges pour la catégorie A pour la salle %d : ", i + 1);
        scanf("%d", &s[i].siege_A);
        printf("Entrer le nombre de sièges pour la catégorie B pour la salle %d : ", i + 1);
        scanf("%d", &s[i].siege_B);
        printf("Entrer le nombre de sièges pour la catégorie C pour la salle %d : ", i + 1);
        scanf("%d", &s[i].siege_C);

        // ouvrir le fichier
        FILE *fp = fopen("salle.txt", "a");

        if (fp == NULL) {
            printf("Error opening file!\n");
            return 1;
        }

        fprintf(fp, "Nom de la salle : %s\nNombre de rangées : %d\nNombre de sièges par rangée : %d\nNombre de sièges pour la catégorie A : %d\nNombre de sièges pour la catégorie B : %d\nNombre de sièges pour la catégorie C : %d\n\n", s[i].nom, s[i].nombre_rangees, s[i].siege_range, s[i].siege_A, s[i].siege_B, s[i].siege_C);

        fclose(fp);
    }

    return s;
    
}


// Fonction pour configurer les catégories de sièges
//void configurer_categories(Salle* salle, int nombre_rangees_a, int nombre_rangees_b) {
 //   salle->nombre_rangees_a = nombre_rangees_a;
   // salle->nombre_rangees_b = nombre_rangees_b;

   // for (int i = 0; i < salle->nombre_rangees; i++) {
      //  char categorie = 'C';
        //if (i < nombre_rangees_a) {
          //  categorie = 'A';
        //} else if (i < nombre_rangees_a + nombre_rangees_b) {
          //  categorie = 'B';
       // }
       // for (int j = 0; j < salle->sieges_par_rangee; j++) {
        //    salle->rangees[i].sieges[j].categorie = categorie;
        //}
    //}
//}

// Fonction pour attribuer un concert à une salle
Concert* attribuer_concert(Salle* salle, ) {
    Concert* concert = (Concert*)malloc(sizeof(Concert));
    strcpy(concert->nom, nom);
    concert->salle = salle;
    concert-> fosse = fosse;
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

