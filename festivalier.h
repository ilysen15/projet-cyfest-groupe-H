#include "header.h"

Salle* lire_salle(const char* nom_fichier);
void afficher_sieges_salle(Salle* salle);
float reserver_sieges(Salle* salle, Concert* concert, int rangee, int siege);
int concert_en_cours(Concert* concert, Date date_courante, Heure heure_courante);
void afficher_concerts_en_cours(Concert* concerts, int nombre_concerts, Date date_courante, Heure heure_courante);
int choix_festivalier();

