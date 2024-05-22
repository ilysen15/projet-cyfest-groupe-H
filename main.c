#include <stdio.h>
#include<stdlib.h>
#include"manegar.h>
#include <string.h>
#include<menu.h>

int main() {
    int nombre_salles;
    printf("Entrer le nombre de salles : ");
    scanf("%d", &nombre_salles);

    Salle** salles = (Salle*)malloc(nombre_salles * sizeof(Salle));

    for (int i = 0; i < nombre_salles; i++) {
        char nom[100];
        int nombre_rangees, sieges_par_rangee, nombre_rangees_a, nombre_rangees_b;

        printf("Entrer le nom de la salle %d : ", i + 1);
        scanf("%s", nom);
        fgets(nom, 50, stdin);
        nom[strlen(nom) - 1] = '\0';
        printf("Entrer le nombre de rangées pour la salle %d : ", i + 1);
        scanf("%d", &nombre_rangees);
        printf("Entrer le nombre de sièges par rangée pour la salle %d : ", i + 1);
        scanf("%d", &sieges_par_rangee);
        printf("Entrer le nombre de rangées pour la catégorie A pour la salle %d : ", i + 1);
        scanf("%d", &nombre_rangees_a);
        printf("Entrer le nombre de rangées pour la catégorie B pour la salle %d : ", i + 1);
        scanf("%d", &nombre_rangees_b);
       
        // ouvrir le fichier
       FILE *fp = fopen("salle.txt", "a"); 

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "nom: %s\n nombre_rangees: %d\n le nombre de sièges par rangée: %d\n le nombre de rangées pour la catégorie A: %d\n le nombre de rangées pour la catégorie B: %d\n\n", nom, nombre_rangees, sieges_par_rangee,nombre_rangees_a, nombre_rangees_b);
        
    fclose(fp);
        
        salles[i] = creer_salle(nom, nombre_rangees, sieges_par_rangee);
        configurer_categories(salles[i], nombre_rangees_a, nombre_rangees_b);
    }

    // Exemple d'attribution de concert
    Concert* concert = attribuer_concert(salles[0], "Concert Rock", 1, 100.0, 75.0, 50.0, "22:00");
    afficher_etat_salle(salles[0]);

    // Libérer la mémoire
    liberer_concert(concert);
    for (int i = 0; i < nombre_salles; i++) {
        liberer_salle(salles[i]);
    }
    free(salles);

    return 0;
}
