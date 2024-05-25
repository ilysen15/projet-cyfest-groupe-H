#include "header.h"
int main() {
    Salle* salle = NULL;
    Concert* concert = NULL;
    int choix;

    // Vérification et création des répertoires si nécessaire
    //verifier_ou_creer_repertoire("salle");
    //verifier_ou_creer_repertoire("concert");

    // Charger les salles et concerts existants
    // Cette partie doit être implémentée en fonction de vos besoins

    do {
        printf("Menu Principal\n");
        printf("1. Menu Festivalier\n");
        printf("2. Menu Manager\n");
        printf("3. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            int choix_fest;
            do {
                choix_fest = choix_festivalier();
                switch (choix_fest) {
                    case 1: {
                        char nom_salle[100];
                        printf("Nom de la salle : ");
                        scanf("%s", nom_salle);
                        char nom_fichier[100];
                        sprintf(nom_fichier, "salle/%s.txt", nom_salle);
                        salle = lire_salle(nom_fichier);
                        if (salle) {
                            char nom_concert[100];
                            printf("Nom du concert : ");
                            scanf("%s", nom_concert);
                            sprintf(nom_fichier, "concert/%s.txt", nom_concert);
                            FILE *file = fopen(nom_fichier, "r");
                            if (file) {
                                concert = (Concert*)malloc(sizeof(Concert));
                                if (concert) {
                                    // Lire les informations du concert
                                    fscanf(file, "nom: %[^\n]\n", concert->nom);
                                    fscanf(file, "prix_a: %f\n", &concert->prix_a);
                                    fscanf(file, "prix_b: %f\n", &concert->prix_b);
                                    fscanf(file, "prix_c: %f\n", &concert->prix_c);
                                    fscanf(file, "heure_debut: %d:%d:%d\n", &concert->heure_debut.heure, &concert->heure_debut.min, &concert->heure_debut.sec);
                                    fscanf(file, "heure_fin: %d:%d:%d\n", &concert->heure_fin.heure, &concert->heure_fin.min, &concert->heure_fin.sec);
                                    fscanf(file, "date_debut: %d/%d/%d\n", &concert->date_debut.jour, &concert->date_debut.mois, &concert->date_debut.an);
                                    fscanf(file, "date_fin: %d/%d/%d\n", &concert->date_fin.jour, &concert->date_fin.mois, &concert->date_fin.an);
                                    concert->salle = salle;
                                    fclose(file);

                                    int rangee, siege;
                                    char nom[100], prenom[100];
                                    printf("Nom : ");
                                    scanf("%s", nom);
                                    printf("Prénom : ");
                                    scanf("%s", prenom);
                                    printf("Numéro de la rangée : ");
                                    scanf("%d", &rangee);
                                    printf("Numéro du siège : ");
                                    scanf("%d", &siege);
                                    float prix = reserver_sieges(salle, concert, rangee - 1, siege - 1, nom, prenom);
                                    if (prix > 0) {
                                        printf("Prix total de la réservation : %.2f\n", prix);
                                    }
                                } else {
                                    printf("Erreur d'allocation mémoire pour le concert.\n");
                                }
                            } else {
                                printf("Concert non trouvé.\n");
                            }
                        } else {
                            printf("Salle non trouvée.\n");
                        }
                        break;
                    }

                    case 2: {
                        char nom_salle[100];
                        printf("Nom de la salle : ");
                        scanf("%s", nom_salle);
                        char nom_fichier[100];
                        sprintf(nom_fichier, "salle/%s.txt", nom_salle);
                        salle = lire_salle(nom_fichier);
                        if (salle) {
                            afficher_sieges_salle(salle);
                        } else {
                            printf("Salle non trouvée.\n");
                        }
                        break;
                    }
                    case 3: {
                        Date date_courante;
                        Heure heure_courante;
                        printf("Date actuelle (jour mois année) : ");
                        scanf("%d %d %d", &date_courante.jour, &date_courante.mois, &date_courante.an);
                        printf("Heure actuelle (heure minute seconde) : ");
                        scanf("%d %d %d", &heure_courante.heure, &heure_courante.min, &heure_courante.sec);

                        // Cette partie doit être remplie avec les concerts existants
                        // Exemple de concert pour tester
                        Concert concerts[1] = {
                            {"Concert Test", salle, 50.0, 40.0, 30.0, {20, 0, 0}, {23, 0, 0}, {24, 5, 2024}, {24, 5, 2024}}
                        };
                        afficher_concerts_en_cours(concerts, 1, date_courante, heure_courante);
                        break;
                    }
                    case 4:
                        printf("Retour au menu principal.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                        break;
                }
            } while (choix_fest != 4);
        } else if (choix == 2) {
            int choix_man;
            do {
                choix_man = choix_manager();
                switch (choix_man) {
                    case 1:
                        salle = creer_salle();
                        char nom_fichier[100];
                        strcpy(nom_fichier, "salle/");
                        strcat(nom_fichier, salle->nom);
                        strcat(nom_fichier, ".txt");

                        sauvegarder_salle(salle, nom_fichier);
                        break;
                    case 2:
                        if (salle == NULL) {
                            printf("Vous devez d'abord créer une salle.\n");
                        } else {
                            concert = attribuer_concert(salle);
                            char nom_fichier2[100];
                            strcpy(nom_fichier2, "concert/");
                            strcat(nom_fichier2, concert->nom);
                            strcat(nom_fichier2, ".txt");
                            sauvegarder_concert(concert, nom_fichier2);
                        }
                        break;
                    case 3:
                        if (salle == NULL) {
                            printf("Vous devez d'abord créer une salle.\n");
                        } else {
                            afficher_etat_salle(salle);
                        }
                        break;
                    case 4:
                        printf("Retour au menu principal.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                        break;
                }
            } while (choix_man != 4);
        }
    } while (choix != 3);

    if (salle) {
        free(salle);
    }
    if (concert) {
        free(concert);
    }

    return 0;
}
