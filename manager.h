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
void Listesalle() ;
void lire_et_afficher(FILE *f) ;

Salle *creer_salle();
Concert* attribuer_concert(Salle* salle,  char* nom,char nom_chanteur, int fosse, float prix_a, float prix_b, float prix_c, Heure* heure_fin, Heure* heure_debut) {
void afficher_etat_salle(Salle* salle) ;
void liberer_salle(Salle* salle) ;
void liberer_concert(Concert* concert) ;
int choix_manger() ;
