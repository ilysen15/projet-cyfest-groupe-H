CY-Fest


Description

CY-Fest est un programme de gestion de festival permettant aux organisateurs de gérer les différentes scènes et concerts du festival CY’FEST. Les participants peuvent payer et réserver leurs places pour les différents concerts. Le projet utilise des techniques avancées telles que la gestion des fichiers, l'allocation dynamique de mémoire et l'affichage d'une interface utilisateur.
 
Fonctionnalités principales

- Gestion des salles de concert avec des sièges disposés en rangées, chacun ayant une catégorie de prix différente.
- Sauvegarde des états des salles de concert et des réservations dans des fichiers entre chaque exécution.
- Mode Manager pour les gestionnaires du festival permettant la création et la gestion des salles et des concerts.
- Mode Festivalier pour les participants permettant de réserver et de consulter leurs réservations.
- Navigation fluide entre les modes sans stopper le programme.
- Gestion dynamique de la mémoire.

Installation

Prérequis

Un compilateur C (par exemple, GCC)
Système d'exploitation compatible (Linux, macOS, Windows)
Instructions
1. Clonez le dépôt 
git clone https://github.com/username/cy-fest.git
cd cy-fest
 
2. Compilez le programme
gcc -o cy-fest main.c
 
 
 Utilisation
Mode Manager
1. Lancez le programme 
./cy-fest
 
2. Choisissez le mode Manager.
3. Créez une nouvelle salle de concert :
1. Entrez le nom de la salle.
2. Définissez le nombre de rangées et de sièges par rangée.
3. Attribuez des catégories de prix aux sièges (A, B, C).
4. Attribuez un concert à une salle existante et configurez la fosse et les prix des catégories.
5. Observez l'état des salles et consultez le ratio sièges réservés / nombre total de sièges.
 
Mode Festivalier
1. Lancez le programme et choisissez le mode Festivalier.
2. Consultez les salles de concert disponibles et réservez des sièges.
3. Visualisez le plan de la salle et choisissez les sièges disponibles.
4. Confirmez la réservation et consultez le prix total.
 
 
 
 
Auteurs
Ilyan SENOUNE 
Aghilas CHEMMI
Karin ATTIA
