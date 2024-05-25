#include "header.h"

void Listesalle();
void lire_et_afficher(FILE *f);
Salle* creer_salle();
Concert* attribuer_concert(Salle* salle);
void afficher_etat_salle(Salle* salle);
int choix_manager();
