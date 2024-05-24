#include<stdio.h>
#include<stdlib.h>
#include"save.h"
#include "maneger.h"


void enrigistresalle(const Salle* salle) {
  FILE *file;
  ();

  remove("save.txt");//supprime le contenue du file
  file=fopen("save.txt","w");
     if (file == NULL) {
        printf("fichier n'existe pas.\n");
        exit(0);
    }
  fprintf(file, "%s", (salle));
  fclose(file);
  printf("Votre partie a bien ete enregistre!");
}



