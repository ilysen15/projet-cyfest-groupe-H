#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"manger.h"
#define TAILLE 100
 
//structure pour la date de concert
typedef struct{
int jour;
int mois;
int an;
}Date;
 

//structure l'heure de debut de la fin de concert
typedef struct{
int heure;
int min;
int sec;
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
    char nom[TAILLE];           // Nom du concert
    char nom_chanteur[TAILLE];  // Nom de chanteur
    Salle *salle;               // Pointeur vers la salle
    int   fosse;                // 0 pour non, 1 pour oui
    float prix_a;               // Prix pour catégorie A
    float prix_b;               // Prix pour catégorie B
    float prix_c;               // Prix pour catégorie C
    Heure heure_debut;          // Heure de debut du concert
    Heure heure_fin;            // Heure de fin du concert
    Date  date_debut;           // date de debut de concert 
    Date  date_fin;             // date de fin de concert
} Concert;

void Listesalle() {
    FILE *f1 = fopen("salle1.txt", "r");
    FILE *f2 = fopen("salle2.txt", "r");
    FILE *f3 = fopen("salle3.txt", "r");
    
    char nom[TAILLE];
    int nb_rangees;
    int nb_rangees_A;
    int nb_rangees_B;
    int nb_sieges_par_rangee;
    char artiste[TAILLE];
    char date[TAILLE];
    char heure[TAILLE];
    
    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    printf("Voici la liste des salles disponibles :\n");
    printf("----------------------------------------\n");

    // Fonction pour lire et afficher le contenu d'un fichier salle
    void lire_et_afficher(FILE *f) {
        // Lire les informations de la salle
        fscanf(f, "nom: %s\n", nom);
        fscanf(f, "nombre_rangees: %d\n", &nb_rangees);
        fscanf(f, "le nombre de sièges par rangée: %d\n", &nb_sieges_par_rangee);
        fscanf(f, "le nombre de rangées pour la catégorie A: %d\n", &nb_rangees_A);
        fscanf(f, "le nombre de rangées pour la catégorie B: %d\n", &nb_rangees_B);
        
        // Lire les informations du concert
        fscanf(f, "CONCERT :\n");
        fscanf(f, "Artiste : %[^\n]\n", artiste); // Lire jusqu'à la fin de la ligne
        fscanf(f, "Date : %s\n", date);
        fscanf(f, "Heure : %[^\n]\n", heure); // Lire jusqu'à la fin de la ligne

        // Afficher les informations lues
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

    // Lire et afficher les informations des fichiers
    lire_et_afficher(f1);
    lire_et_afficher(f2);
    lire_et_afficher(f3);
    
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

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

     // Enregistrement des données dans un fichier
    FILE *f = fopen("nouvelles_salles.txt", "a"); // Ouvre le fichier en mode ajout
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    fprintf(f, "Nom: %s\n", s->nom);
    fprintf(f, "Nombre de rangées: %d\n", s->nombre_rangees);
    fprintf(f, "Nombre de sièges par rangée: %d\n", s->sieges_par_rangee);
    fprintf(f, "Nombre de sièges pour la catégorie A: %d\n", s->sieges_A);
    fprintf(f, "Nombre de sièges pour la catégorie B: %d\n", s->sieges_B);
    fprintf(f, "Nombre de sièges pour la catégorie C: %d\n", s->sieges_C);
    fprintf(f, "\n");

    fclose(f);

    return s;
    }

  

// Fonction pour attribuer un concert à une salle
Concert* attribuer_concert(Salle* salle,  char* nom,char nom_chanteur, int fosse, float prix_a, float prix_b, float prix_c, Heure* heure_fin, Heure* heure_debut) {
    Concert* concert = malloc(sizeof(Concert*));
    strcpy(concert->nom, nom);
    strcpy(concert->nom_chanteur, nom_chanteur);
    concert->salle = salle;
    salle=creer_salle();
    concert-> fosse = fosse;
    concert->prix_a = prix_a;
    concert->prix_b = prix_b;
    concert->prix_c = prix_c;
    concert-> heure_fin= heure_fin;
    concert-> heure_debut= heure_debut;
    strcpy(concert->heure_fin, heure_fin);

    if (fosse) {
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
    printf("Ratio de réservation: %f%%\n", (float)sieges_reserves / total_sieges * 100);
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


int main(){
 

