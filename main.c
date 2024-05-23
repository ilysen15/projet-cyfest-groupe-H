#include <stdio.h>
#include<stdlib.h>
#include "manegar.h"
#include <string.h>
#include<menu.h>


int main() {
    Salle *salles = creer_salle();

    if (salles == NULL) {
        printf("Erreur lors de la création des salles.\n");
        return 1;
    }

    printf("Salles créées avec succès.\n");

    // Afficher les informations des salles
    for (int i = 0; i < 1; i++) { // afficher uniquement la première salle pour l'exemple
        printf("Salle %d :\n", i + 1);
        printf("  Nom : %s\n", salles[i].nom);
        printf("  Nombre de rangées : %d\n", salles[i].nombre_rangees);
        printf("  Nombre de sièges par rangée : %d\n", salles[i].siege_range);
        printf("  Nombre de sièges pour la catégorie A : %d\n", salles[i].siege_A);
        printf("  Nombre de sièges pour la catégorie B : %d\n", salles[i].siege_B);
        printf("  Nombre de sièges pour la catégorie C : %d\n", salles[i].siege_C);
    }

    free(salles);

    return 0;
}
