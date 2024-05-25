#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE 100

typedef struct {
    char categorie;  // 'A', 'B', 'C', ou 'P' pour Pit (fosse)
    int reserve;     // 0 pour libre, 1 pour réservé
} Siege;


typedef struct {
    char nom[100];    // Nom de la salle
    int nombre_rangees; // Nombre de rangées
    int sieges_par_rangee; // Nombre de sièges par rangée
    Siege** rangees;   // Tableau de pointeurs vers les rangées de sièges
} Salle;

typedef struct {
    int jour;
    int mois;
    int an;
} Date;

typedef struct {
    int heure;
    int min;
    int sec;
} Heure;

typedef struct {
    char nom[100];           // Nom du concert
    Salle *salle;            // Pointeur vers la salle
    float prix_a;            // Prix pour catégorie A
    float prix_b;            // Prix pour catégorie B
    float prix_c;            // Prix pour catégorie C
    Heure heure_debut;       // Heure de début du concert
    Heure heure_fin;         // Heure de fin du concert
    Date date_debut;         // Date de début du concert
    Date date_fin;           // Date de fin du concert
} Concert;

Salle* lire_salle(const char* nom_fichier);
void afficher_sieges_salle(Salle* salle);
float reserver_sieges(Salle* salle, Concert* concert, int rangee, int siege);
int concert_en_cours(Concert* concert, Date date_courante, Heure heure_courante);
void afficher_concerts_en_cours(Concert* concerts, int nombre_concerts, Date date_courante, Heure heure_courante);
int choix_festivalier();



void Listesalle();
void lire_et_afficher(FILE *f);
Salle* creer_salle();
Concert* attribuer_concert(Salle* salle);
void afficher_etat_salle(Salle* salle);
int choix_manager();

void sauvegarder_concert(Concert* concert, const char* nom_fichier);
void sauvegarder_salle(Salle* salle, const char* nom_fichier);
Salle* charger_salle(const char* nom_fichier);

int main();
