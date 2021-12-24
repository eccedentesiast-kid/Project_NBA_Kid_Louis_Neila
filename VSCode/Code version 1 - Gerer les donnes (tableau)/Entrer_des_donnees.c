#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int noJoueur;
    char nom_prenom[50];
    char numUniforme[3];
    char poste[15];
    double points;
    double passes;
    double rebonds;
    char nomEquipe[50];
    char entraineurChef[50];
    char region[50];
}Joueurs;

/*********************printLine*******************/

void printLine(int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("_");
    }
    printf("\n");
}

/*************entrer_les_infors_Joueur*************/

void entrerInforJoueur(Joueurs *j, int id) {
    j->noJoueur = id;
    printf("+ Entrer le nom et le prenom du joueur: ");
    fflush(stdin); gets(j->nom_prenom);
    printf("+ Entrer le numero Uniforme du joueur: ");
    scanf("%s", &j->numUniforme);
    printf("+ Entrer le poste du joueur: ");
    scanf("%s", &j->poste);
    printf("+ Entrer les stats annne passe du joueur (Points, Passes, Rebonds): ");
    scanf("%lf %lf %lf", &j->points, &j->passes, &j->rebonds);
    printf("+ Entrer le nom d'equipe: ");
    fflush(stdin); gets(j->nomEquipe); 
    printf("+ Entrer l'entraineur chef d'equipe: ");
    fflush(stdin); gets(j->entraineurChef);
    printf("+ Entrer la region d'equipe: ");
    fflush(stdin); scanf("%s",&j->region);
}

void entrerJoueur(Joueurs jo[], int id, int n) {
    printf("\nEntrer le joueur %d: \n", n+1);
    entrerInforJoueur(&jo[n], id);
    printLine(70);
}

bool valideId(Joueurs jo[], int n, int id) {
    for (int j = 0; j < n; j++) {
        if (jo[j].noJoueur == id) {
            return false;
        }
    }
    return true;
}

void entrerTableauJoueur(Joueurs jo[], int *n) {
    printf("\nEntrer le nombre de joueur: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        bool valide = false; int id;
        while (!valide) {
            printf("\nEntrer l'id du joueur %d: ", i+1); scanf("%d",&id);
            valide = valideId(jo,i,id);
            if (!valide) { printf("\n=> Impossible d'ajouter un joueur car un identifiant en double existe deja!\n"); }
        }
        entrerJoueur(jo,id,i);
    }
}

/*************Afficher_les_Joueurs_dans_un_tableau*************/

void afficherJoueur(Joueurs jo) {
     printf("=> [No Joueurs = %d | Nom et Prenom: %s | Num Uniforme: %s | Poste: %s\n    Stats: Points = %0.2lf, Passes = %0.2lf, Rebonds = %0.2lf\n    Nom Equipe: %s | Entraineur Chef: %s | Region: %s]\n",jo.noJoueur, jo.nom_prenom, jo.numUniforme, jo.poste, jo.points, jo.passes, jo.rebonds,jo.nomEquipe,jo.entraineurChef,jo.region);
}

void afficherLesJoueurs(Joueurs j[], int n) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", j[i].noJoueur, j[i].nom_prenom, j[i].numUniforme, j[i].poste, j[i].points, j[i].passes, j[i].rebonds, j[i].nomEquipe, j[i].entraineurChef, j[i].region);
        printf("\n");
    }
}

/*************Trouver_le_meilleur_joueur_d'une_saison*************/

void trouverMVP(Joueurs jo[], int n) {
    double max = (jo[0].points + jo[0].passes + jo[0].rebonds)/3;
    Joueurs MVP = jo[0];
    for (int i = 0; i < n; i++) {
        if ((jo[i].points + jo[i].passes + jo[i].rebonds)/3 > max) {
            max = (jo[i].points + jo[i].passes + jo[i].rebonds)/3;
            MVP = jo[i];
        }
    }
    printf("\nLes informations de MVP: \n");
    afficherJoueur(MVP);
}

/*************Trouver_le_joueur_par_nom_et_prenom*************/

void trouverJoueurNom(Joueurs jo[], int n, char nom[]) {
    for (int i = 0; i < n; i++) {
        char temp[50]; strcpy(temp,jo[i].nom_prenom);
        if (strstr(strupr(temp), strupr(nom))) {
            printf("\nLes informations de joueur recherchee:\n");
            afficherJoueur(jo[i]);
            return;
        }
    }
    printf("\n=> Aucun joueur valide trouve!");
}

/*************Trouver_le_joueur_par_nom_d'equipe*************/

void afficherJoueursParNomEquipe(Joueurs j[], int n, char nomGroupe[]) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    bool valide = false;
    for (int i = 0; i < n; i++) {
        char temp[50]; strcpy(temp, j[i].nomEquipe);
        if (strstr(strupr(temp), strupr(nomGroupe))) {
            printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", j[i].noJoueur, j[i].nom_prenom, j[i].numUniforme, j[i].poste, j[i].points, j[i].passes, j[i].rebonds, j[i].nomEquipe, j[i].entraineurChef, j[i].region);
            printf("\n");
            valide = true;
        }
    }
    if (!valide) { printf("\n=> Aucun equipe valide trouve!"); }
}

/*************Trouver_le_joueur_par_poste*************/

void afficherJoueursParPoste(Joueurs j[], int n, char nomPoste[]) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    bool valide = false;
    for (int i = 0; i < n; i++) {
        char temp[50]; strcpy(temp, j[i].poste);
        if (strcmp(strupr(temp), strupr(nomPoste)) == 0) {
            printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", j[i].noJoueur, j[i].nom_prenom, j[i].numUniforme, j[i].poste, j[i].points, j[i].passes, j[i].rebonds, j[i].nomEquipe, j[i].entraineurChef, j[i].region);
            printf("\n");
            valide = true;
        }
    }
    if (!valide) { printf("\n=> Aucun joueur valide trouve!"); }
}

/*************Exporter_les_infors_vers_un_fichier*************/

void exporterVersFichier(Joueurs jo[], int n) {
    FILE *file = fopen("joueurs.txt","wb");
    if (file != NULL) {
        //Nombre de joueurs
        fwrite(&n, sizeof(n), 1, file);
        //Les infors des joueurs
        for (int i = 0; i < n; i++) {
            fwrite(&jo[i],sizeof(Joueurs), 1, file);
        }
    }
    fclose(file);
}

/*************Importer_des_infors_à_partir_d'un_fichier*************/

void importerAPartirFichier(Joueurs jo[], int *n) {
    FILE *file = fopen("joueurs.txt","rb");
    Joueurs j[150];
    if (file != NULL) {
        //Nombre de joueurs
        fread(n, sizeof(*n), 1, file);
        //Les infors des joueurs
        for (int i = 0; i < *n; i++) {
            fread(&jo[i],sizeof(Joueurs),1,file);
        }
    }
    fclose(file);
}

/*************trier_les_joueurs_dans_l'ordre_croissant*************/

void trierCroissant(Joueurs jo[], int n) {
    for (int i = 0; i < n-1; i++ ) {
        for (int j = i+1; j < n; j++) {
            if (jo[i].noJoueur > jo[j].noJoueur) {
                Joueurs temp;
                temp = jo[i];
                jo[i] = jo[j];
                jo[j] = temp;
            }
        }
    }
}

/*************trier_les_joueurs_dans_l'ordre_decroissant*************/

void trierDecroissant(Joueurs jo[], int n) {
    for (int i = 0; i < n-1; i++ ) {
        for (int j = i+1; j < n; j++) {
            if (jo[i].noJoueur < jo[j].noJoueur) {
                Joueurs temp;
                temp = jo[i];
                jo[i] = jo[j];
                jo[j] = temp;
            }
        }
    }
}

/*************ajouter_un_nouveau_joueur*************/

void ajouterNouveauJoueur(Joueurs jo[], int *n) {
    int id;
    printf("\nEntrer l'id du joueur %d: ", (*n)+1); scanf("%d",&id);
    bool valide = valideId(jo,*n,id);
    if (!valide) {
        printf("\n=> Impossible d'ajouter un joueur car un identifiant en double existe deja!");
        return;
    }
    entrerJoueur(jo,id,(*n));
    (*n)++;
    exporterVersFichier(jo,(*n));
    printf("\n=> Ajoute le joueur et mis a jour le joueur dans le fichier avec succes!");
}

/*************supprimer_un_joueur*************/

void supprimerUnJoueur(Joueurs jo[], int *n, int idTrouve) {
    for (int i = 0; i < (*n); i++) {
        if (jo[i].noJoueur == idTrouve) {
            for (int j = i; j < (*n)-1; j++) {
                jo[j] = jo[j+1];
            }
            (*n)--;
            exporterVersFichier(jo,(*n));
            printf("\n=> Supprime le joueur avec l'id '%d' et mis a jour le fichier avec succes!", idTrouve);
            return;
        }
    }
    printf("\n=> Impossible de supprimer un joueur car il n'existe pas l'id correspondant!");
}

/*************trier_alphabetique*************/

// void trierAlphabetique(Joueurs jo[], int n) {
//     for (int i = 0; i < n-1; i++ ) {
//         for (int j = i+1; j < n; j++) {
//             if (strcmp(jo[i].nom_prenom, jo[j].nom_prenom) > 0) {
//                 Joueurs temp;
//                 temp = jo[i];
//                 jo[i] = jo[j];
//                 jo[j] = temp;
//             }
//         }
//     }
// }

/*************fontion_main_tester_toutes_les_fonctions*************/

int main() {
    //Nos données n'ont que 150 joueurs
    /*Dans le cas vous voulez ajouter un nouveau joueur
    alors nous avons mis 200 joueurs pour un tableau*/
	Joueurs jo[200];
	int n, choix;
	do {

	    printf("\nMENU DE PROJET KNL - NBA:");
		printf("\n1  - Entrer la liste de joueurs");
		printf("\n2  - Afficher la liste de joueurs");
		printf("\n3  - Trouver le meilleur joueur d'une saison (MVP)");
		printf("\n4  - Trouver un joueur par nom et prenom");
		printf("\n5  - Afficher la liste de joueur par nom d'equipe");
		printf("\n6  - Afficher la liste de joueur par poste");
		printf("\n7  - Trier les joueurs par l'ordre croissant d'identifiant");
		printf("\n8  - Trier les joueurs par l'ordre decroissant d'identifiant");
		printf("\n9  - Ajouter un nouveau joueur");
		printf("\n10 - Supprimer un joueur par id");
		printf("\n11 - Importer des informations de joueur a partir d'un fichier");
		printf("\n12 - Exporter les informations de joueur vers un fichier");
		printf("\n0  - Quitter");
        printf("\n=> Entrer votre choix: ");
		scanf("%d", &choix);
		
		switch(choix){
			case 1:
                printLine(70);
                entrerTableauJoueur(jo,&n);
                printLine(70);
                break;
            case 2:
                printLine(70);
                afficherLesJoueurs(jo,n);
                printLine(70);
                break;
            case 3:
                printLine(70);
                trouverMVP(jo,n);
                printLine(70);
                break;
            case 4:
                printLine(70);
                char nomPrenom[50];
                printf("\nEntrer le nom et prenom de joueur pour trouver: "); fflush(stdin);
                gets(nomPrenom);
                trouverJoueurNom(jo,n,nomPrenom);
                printLine(70);
                break;
            case 5:
                printLine(70);
                char nomGroupe[50];
                printf("\nEntrer le nom d'equipe pour afficher les joueurs: "); fflush(stdin);
                gets(nomGroupe);
                afficherJoueursParNomEquipe(jo,n,nomGroupe);
                printLine(70);
                break;
            case 6:
                printLine(70);
                char nomPoste[50];
                printf("\nEntrer le nom de poste pour afficher les joueurs: "); fflush(stdin);
                gets(nomPoste);
                afficherJoueursParPoste(jo,n,nomPoste);
                printLine(70);
                break;
            case 7:
                printLine(70);
                trierCroissant(jo,n);
                printf("\n=> Trier dans l'ordre croissant succes!");
                printLine(70);
                break;
            case 8:
                printLine(70);
                trierDecroissant(jo,n);
                printf("\n=> Trier dans l'ordre decroissant succes!");
                printLine(70);
                break;
            case 9:
                printLine(70);
                ajouterNouveauJoueur(jo,&n);
                printLine(70);
                break;
            case 10:
                printLine(70);
                int idSupprimer;
                printf("\nEntrer le numero de joueur que vous voulez supprimer: "); scanf("%d", &idSupprimer);
                supprimerUnJoueur(jo,&n,idSupprimer);
                printLine(70);
                break;
            case 11:
                printLine(70);
                importerAPartirFichier(jo,&n);
                printf("\nImporter succes!");
                printLine(70);
                break;
            case 12:
                printLine(70);
                exporterVersFichier(jo,n);
                printf("\nExporter succes!");
                printLine(70);
                break;
		}
	} while(choix!=0);
}

