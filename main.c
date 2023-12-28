#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bus* tete = NULL;
struct voyageur {
    char nom_v[20];
    char prenom_v[20];
    long long id_v;
    long long N_tel;
    int age;
};

struct bus {
    long long id_bus;
    int nb_places;
    double puissance;
    struct bus* suiv;
};

struct reservation {
    struct voyageur v;
    struct bus b;
    char depart[20];
    char arrive[20];
    char date[20];
    long long N_res;
    float prix;
    char heur_depart[6];
    char heur_arrive[6];
};

void ajouter_bus(long long id, int nb_p, double puiss, struct bus** tete) {
    struct bus* b = malloc(sizeof(struct bus));
    if (b == NULL) {
        printf("Erreur d'allocation m�moire.\n");
        return;
    }

    b->id_bus = id;
    b->nb_places = nb_p;
    b->puissance = puiss;
    b->suiv = *tete;

    *tete = b;
    printf("Ajout effectu� avec succ�s.\n");
}

int nbr_des_bus(struct bus* tete) {
    if (tete == NULL) {
        return 0;
    } else {
        return 1 + nbr_des_bus(tete->suiv);
    }
}

struct bus* supprimer_bus(long long id, struct bus* tete) {
    int k = 1;
    int NB_bus = nbr_des_bus(tete);
    struct bus* aux = tete;
    struct bus* p;

    while (aux != NULL && aux->id_bus != id && k <= NB_bus) {
        aux = aux->suiv;
        k += 1;
    }

    if (k >= 1) {
        if (k == 1 && aux != NULL) {
            tete = aux->suiv;
            free(aux);
        } else if (aux != NULL) {
            int i = 1;
            while (i < k - 1) {
                aux = aux->suiv;
                i += 1;
            }
            p = aux->suiv;
            aux->suiv = p->suiv;
            free(p);
        }
    }

    return tete;
}


void enregistrer_voyageur(struct voyageur compte) {
    FILE *fichier;


    fichier = fopen("voyageurs.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }


    fprintf(fichier, "Nom : %s\n", compte.nom_v);
    fprintf(fichier, "Pr�nom : %s\n", compte.prenom_v);
    fprintf(fichier, "ID : %lld\n", compte.id_v);
    fprintf(fichier, "Num�ro de t�l�phone : %lld\n", compte.N_tel);
    fprintf(fichier, "�ge : %d\n", compte.age);
    fprintf(fichier, "-----------------\n");


    fclose(fichier);
}

struct voyageur creer_compte(long long idv) {
    struct voyageur compte;
    printf("Merci de nous donner votre nom : ");
    scanf("%s", compte.nom_v);
    printf("Merci de nous donner votre pr�nom : ");
    scanf("%s", compte.prenom_v);
    printf("Merci de nous donner votre num�ro de t�l�phone : ");
    scanf("%lld", &compte.N_tel);
    printf("Merci de nous donner votre �ge : ");
    scanf("%d", &compte.age);
    compte.id_v=idv;
    printf("Gardez votre identifiant, vous en aurez besoin : %d\n", idv);

    return compte;
}
struct voyageur lire_voyageur(long long id) {
    struct voyageur compte;
    FILE *fichier;
    char buffer[100];

    fichier = fopen("voyageurs.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return compte;
    }


    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        sscanf(buffer, "ID : %lld", &compte.id_v);
        if (compte.id_v == id) {

            fgets(buffer, sizeof(buffer), fichier);
            sscanf(buffer, "Nom : %[^\n]", compte.nom_v);

            fgets(buffer, sizeof(buffer), fichier);
            sscanf(buffer, "Pr�nom : %[^\n]", compte.prenom_v);

            fgets(buffer, sizeof(buffer), fichier);
            sscanf(buffer, "Num�ro de t�l�phone : %lld", &compte.N_tel);

            fgets(buffer, sizeof(buffer), fichier);
            sscanf(buffer, "�ge : %d", &compte.age);

            break;
        }
    }

    fclose(fichier);

    return compte;
}



void modifier_compte(long long id, int champ, const char *nouvelle_valeur) {
    FILE *fichier;
    FILE *temp;
    char buffer[100];
    struct voyageur compte;

    fichier = fopen("voyageurs.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }


    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        fputs(buffer, temp);
    }

    fclose(fichier);
    fclose(temp);


    temp = fopen("temp.txt", "a");


    fichier = fopen("voyageurs.txt", "r");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }


    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        sscanf(buffer, "ID : %lld", &compte.id_v);


        if (compte.id_v == id) {
            switch (champ) {
                case 1:
                    // Modification du nom
                    fprintf(temp, "Nom : %s\n", nouvelle_valeur);
                    break;
                case 2:

                    fprintf(temp, "Pr�nom : %s\n", nouvelle_valeur);
                    break;
                case 3:

                    fprintf(temp, "Num�ro de t�l�phone : %s\n", nouvelle_valeur);
                    break;
                case 4:

                    fprintf(temp, "�ge : %s\n", nouvelle_valeur);
                    break;
                default:

                    fputs(buffer, temp);
            }
        } else {

            fputs(buffer, temp);
        }
    }

    fclose(fichier);
    fclose(temp);


    remove("voyageurs.txt");
    rename("temp.txt", "voyageurs.txt");
}






void afficherVoyageurs() {
    FILE *fichier;
    char ligne[100];

    fichier = fopen("voyageurs.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    struct voyageur voyageur;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "ID : %lld", &voyageur.id_v);

        fgets(ligne, sizeof(ligne), fichier);
        sscanf(ligne, "Nom : %[^\n]", voyageur.nom_v);

        fgets(ligne, sizeof(ligne), fichier);
        sscanf(ligne, "Pr�nom : %[^\n]", voyageur.prenom_v);

        fgets(ligne, sizeof(ligne), fichier);
        sscanf(ligne, "Num�ro de t�l�phone : %lld", &voyageur.N_tel);

        fgets(ligne, sizeof(ligne), fichier);
        sscanf(ligne, "�ge : %d", &voyageur.age);

        // Afficher les informations du voyageur
        printf("ID : %lld\n", voyageur.id_v);
        printf("Nom : %s\n", voyageur.nom_v);
        printf("Pr�nom : %s\n", voyageur.prenom_v);
        printf("Num�ro de t�l�phone : %lld\n", voyageur.N_tel);
        printf("�ge : %d\n\n", voyageur.age);
    }

    fclose(fichier);
}





int nres=0;
struct reservation reserver(long long idv) {
    struct reservation r;
    nres+=1;
    r.N_res=nres;
    printf("Tapez votre depart: \n");
    scanf("%s",r.depart);
    printf("Tapez votre destination: \n");
    scanf("%s",r.arrive);
    printf("� quelle date voulez-vous voyager? \n");
    printf("Merci de ddonner la date sous la forme: jj/mm/aaaa\n");

    scanf("%s",r.date);
    FILE *fichierPrix = fopen("prix.txt", "r");
    if (fichierPrix == NULL) {
        perror("Erreur lors de l'ouverture de prix.txt");
        exit(EXIT_FAILURE);
    }

    char ligne[100];
    char arrive[50], depart[50], heur_arrive[10], heur_depart[10];
    float prix;

    while (fgets(ligne, sizeof(ligne), fichierPrix) != NULL) {

        if (sscanf(ligne, "%s %s %s %s %f", arrive, depart, heur_arrive, heur_depart, &prix) == 5) {

            if (strcmp(r.depart, depart) == 0 && strcmp(r.arrive, arrive) == 0) {
                strcpy(r.heur_arrive, heur_arrive);
                strcpy(r.heur_depart, heur_depart);
                r.prix = prix;
                break;
            }
        }
    }

    fclose(fichierPrix);
    printf("depart � : %s ",r.heur_depart);
    printf("arriv� � : %s ",r.heur_arrive);
    printf("prix : %s",r.prix);
    return r;

}


void modifier_reservation(){

}
void afficher_detail_bus(struct bus *tete) {
    struct bus *aux;
    aux = tete;

    while (aux != NULL) {
        printf("ID du bus : %lld\n", aux->id_bus);
        printf("Nombre de places : %d\n", aux->nb_places);
        printf("Puissance du bus : %.2lf\n", aux->puissance);
        aux = aux->suiv;
    }
}




int idv = 0;
int idb = 0;

int main(){
    printf(" _____________________________________________ \n");
    printf("| -----------------Bienvenu-------------------|\n");
    printf("|       1-entrer en tant qu'administrateur     |\n");
    printf("|        2-entrer en tant que voyageur        |\n");
    printf("|                  0-quitter                  |\n");
    printf("|_____________________________________________|\n");
    printf("Merci de choisir le mode d'entr�e : ");
    int entrer;
    scanf("%d", &entrer);

    if (entrer == 1) {
         printf("_______________________________________________\n");
        printf("| --------------Bienvenu----------------------|\n");
        printf("|          1-cr�er et ajouter un nouveau bus  |\n");
        printf("|          2-supprimer un bus existant        |\n");
        printf("|          3-afficher la liste de bus         |\n");
        printf("|          4-afficher la liste de voyageurs   |\n");
        printf("|_____________________________________________|\n");
        printf("Merci de choisir votre commande : ");
        int gerer;
        scanf("%d", &gerer);

        if (gerer == 1) {
            idb += 1;
            int nb_p, puiss;
            printf("Donner les caract�ristiques du bus � ajouter : \n");
            printf("Nombre de places : ");
            scanf("%d", &nb_p);
            printf("Puissance du moteur : ");
            scanf("%d", &puiss);
            ajouter_bus(idb, nb_p, puiss, &tete);
        }

        if (gerer == 2) {
            printf("Donner l'identifiant du bus � supprimer : \n");
            long long id;
            scanf("%lld", &id);
            tete = supprimer_bus(id, tete);
        }

        if (gerer == 3){
            afficher_detail_bus(tete);
        }

        if(gerer==4){
            afficherVoyageurs();

        }
    }

    if (entrer == 2) {
        printf("_______________________\n");
        printf("|------Bienvenu-------|\n");
        printf("| Avez-vous un compte?|\n");
        printf("|       1-oui         |\n");
        printf("|       2-non         |\n");
        printf("|_____________________| \n");
        int reponse;
        scanf("%d", &reponse);

        if (reponse == 1) {
            int choix;
            printf("_____________________________________\n");
            printf("|    1-effectuer une r�servation     |\n");
            printf("|      2-modifier votre compte      |\n");
            printf("|___________________________________|\n");
            printf("choisir l'operation que vous voulez effectuer : ");
            scanf("%d", &choix);
            printf("donner votre identifiant");
            scanf("%d",&idv);

            if (choix == 1) {

                reserver(idv);
            }

            if (choix == 2){
                int champ;
                char nouvelle_valeur[20];
                struct voyageur compte;
                compte=lire_voyageur(idv);

                printf("Pr�ciser le champ � modifier : ");
                printf("1-nom\n");
                printf("2-pr�nom\n");
                printf("3-N_tel\n");
                printf("4-age\n");
                scanf("%d", &champ);

        switch (champ) {
            case 1:
                printf("Nouveau nom : ");
                scanf("%s", nouvelle_valeur);
                modifier_compte(compte.id_v, 1, nouvelle_valeur);
                break;
            case 2:
                printf("Nouveau pr�nom : ");
                scanf("%s", nouvelle_valeur);
                modifier_compte(compte.id_v, 2, nouvelle_valeur);
                break;
            case 3:
                printf("Nouveau num�ro de t�l�phone : ");
                scanf("%s", nouvelle_valeur);
                modifier_compte(compte.id_v, 3, nouvelle_valeur);
                break;
            case 4:
                printf("Nouvel �ge : ");
                scanf("%s", nouvelle_valeur);
                modifier_compte(compte.id_v, 4, nouvelle_valeur);
                break;
            default:
                printf("Choix non reconnu.\n");
        }



            }
                }





        if (reponse == 2) {
            idv=idv+1;
            struct voyageur compte =creer_compte(idv);
            enregistrer_voyageur(compte);
    }

    if (entrer == 0) {
        printf("Fermeture du programme...\n");
    }

    return 0;
}
}
