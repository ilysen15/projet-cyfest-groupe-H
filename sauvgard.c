#include<stdio.h>
#include<stdlib.h>
#include"sauvgard.h"
#include "manegar.h"


void enrigistresalle(const Salle* salle) {
  FILE *file;
  recovertext();

  remove("save.txt");//supprime le contenue du file
  file=fopen("save.txt","w");
     if (file == NULL) {
        printf("fichier n'existe pas.\n");
        exit(0);
    }
  fprintf(file, "%s", recovertext(partie));
  fclose(file);
  printf("Votre partie a bien ete enregistre!");
}


