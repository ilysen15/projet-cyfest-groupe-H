#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Mode Manager\n");
    printf("2. Mode Festivalier\n");
    printf("3. Quitter\n");
    printf("======================\n");
}


int modeManager(void){
int salle;
 do {
        printf("=== Mode Manager ===\n");
        printf("choissiez 1 pour salle de classe A \n");
        printf("choissiez 2 pour salle de classe B \n");
        printf("choissiez 3 pour salle de classe C \n");
        printf("choissiez 4 pour creer une salle \n");
        printf("Entrez votre salle : ");
        scanf("%d", &salle); 
        while(getchar()!='\n'){
          
        }
   

        switch (salle) {
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
    } while ((salle<0 || salle >4) || getchar()!='\n');

    return 0;
}


void modeFestivalier() {
    printf("\n--- Mode Festivalier ---\n");
}



int main() {
    int choix;

    while (choix<1 || choix>3) {
        afficherMenu();
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                modeManager();
                break;
            case 2:
                modeFestivalier();
                break;
            case 3:
                printf("Reviens quand tu veux !\n");
                exit(0);
            default:
                printf("Erreur, réessaye.\n");
        }
    }

    return 0;
}
