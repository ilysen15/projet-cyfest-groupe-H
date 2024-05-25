
#include "header.h"
void sauvegarder_salle(Salle* salle, const char* nom_fichier);
Salle* charger_salle(const char* nom_fichier);

void sauvegarder_concert(Concert* concert, const char* nom_fichier);Concert* charger_concert(const char* nom_fichier, Salle* salle);