Structures de données :

struct voyageur : Représente les informations d'un voyageur, telles que le nom, le prénom, l'identifiant, le numéro de téléphone et l'âge.
struct bus : Représente les informations d'un bus, telles que l'identifiant du bus, le nombre de places et la puissance du moteur.
struct reservation : Représente les informations d'une réservation, comprenant le voyageur, le bus, le lieu de départ, le lieu d'arrivée, la date, le numéro de réservation, le prix, l'heure de départ et l'heure d'arrivée.
Fonctions pour la gestion des bus :

ajouter_bus() : Ajoute un nouveau bus à la liste des bus.
nbr_des_bus() : Calcule le nombre de bus dans la liste.
supprimer_bus() : Supprime un bus de la liste en fonction de son identifiant.
Fonctions pour la gestion des voyageurs :

enregistrer_voyageur() : Enregistre les informations d'un voyageur dans un fichier texte.
creer_compte() : Crée un nouveau compte voyageur avec un identifiant unique.
lire_voyageur() : Lit les informations d'un voyageur à partir du fichier texte en fonction de son identifiant.
modifier_compte() : Modifie les informations d'un voyageur dans le fichier texte en fonction de son identifiant.
afficherVoyageurs() : Affiche la liste des voyageurs à partir du fichier texte.
Fonctions pour la gestion des réservations :

reserver() : Effectue une réservation en demandant des informations sur le départ, la destination et la date. Lit également les informations de prix à partir d'un fichier texte.
modifier_reservation() : (Non implémenté dans le code fourni, mais mentionné dans le prototype).
Fonction principale (main) :

Le programme principal commence par afficher un menu pour choisir entre l'entrée en tant qu'administrateur ou voyageur.
En tant qu'administrateur, il propose des options pour créer/ajouter un nouveau bus, supprimer un bus existant, afficher la liste des bus, et afficher la liste des voyageurs.
En tant que voyageur, le programme propose des options pour effectuer une réservation ou modifier son compte.
Les données sont stockées dans des fichiers texte (voyageurs.txt, prix.txt).
