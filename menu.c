#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "menu.h"

int choixsalle(void){
int choix;
 do {
        printf("Menu \n");
        printf("choissiez 1 pour salle de classe A \n");
        printf("choissiez 2 pour salle de classe B \n");
        printf("choissiez 1 pour salle de classe C \n");
        printf("choissiez 4 pour creer une salle \n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        while(getchar()!='\n'){
          
        }
   

        switch (choix) {
            case 1:
                fopen( "salle1.txt");
             

                break;
            case 2:
                fopen("salle2.txt");
              
                break;
               
            case 3:
               fopen("salle3.txt");
                exit(0);
                break;
            case 4:
               fopen("salle3.txt");
                exit(0);
                break;
            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
                break;
        }
    } while ((choix<0 || choix >4) || getchar()!='\n');

    return 0;
}
