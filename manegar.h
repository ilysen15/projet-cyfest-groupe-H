#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 100


Salle* creer_salle(const char* nom, int nombre_rangees, int sieges_par_rangee);
void configurer_categories(Salle* salle, int nombre_rangees_a, int nombre_rangees_b);
Concert* attribuer_concert(Salle* salle, const char* nom, int a_fosse, double prix_a, double prix_b, double prix_c, const char* heure_fin);
void afficher_etat_salle(Salle* salle) ;
