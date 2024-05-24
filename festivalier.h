typedef struct {
    char categorie;  // 'A', 'B', 'C', ou 'P' pour Pit (fosse)
    int reserve;     // 0 pour libre, 1 pour réservé
} Siege;

typedef struct {
    char nom[100];    // Nom de la salle
    int nombre_rangees; // Nombre de rangées
    int sieges_par_rangee; // Nombre de sièges par rangée
    Siege** rangees;   // Tableau de pointeurs vers les rangées de sièges
} Salle;

typedef struct {
    int jour;
    int mois;
    int an;
} Date;

typedef struct {
    int heure;
    int min;
    int sec;
} Heure;

typedef struct {
    char nom[100];           // Nom du concert
    Salle *salle;            // Pointeur vers la salle
    float prix_a;            // Prix pour catégorie A
    float prix_b;            // Prix pour catégorie B
    float prix_c;            // Prix pour catégorie C
    Heure heure_debut;       // Heure de début du concert
    Heure heure_fin;         // Heure de fin du concert
    Date date_debut;         // Date de début du concert
    Date date_fin;           // Date de fin du concert
} Concert;

