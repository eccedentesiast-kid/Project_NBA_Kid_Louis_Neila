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

typedef struct Node {
    Joueurs joueur;
    struct Node* gauche;
    struct Node* droite;
    int height;
}Node;

/*********************printLine*******************/

void printLine(int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("_");
    }
    printf("\n");
}

/*********************Creer_Nouveau_Node*******************/

Node* creerNouveauNode(Joueurs jo) {
    Node* nouveau = (Node*)malloc(sizeof(Node));
    nouveau->joueur = jo;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    nouveau->height = 1;
    return nouveau;
}

/*************Les_fonctions_balance_arbre_AVL_TREE*************/

int max(int a, int b) {
  return (a > b) ? a : b;
}

int height(struct Node *root) {
  if (root == NULL)
    return 0;
  return root->height;
}

Node* rightRotate(Node *y) { //rotation à droite
    Node *x = y->gauche;
    Node *T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->height = max(height(y->gauche), height(y->droite)) + 1;
    x->height = max(height(x->gauche), height(x->droite)) + 1;

    return x;
}

Node *leftRotate(struct Node *x) { //rotation à gauche
    Node *y = x->droite;
    Node *T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->height = max(height(x->gauche), height(x->droite)) + 1;
    y->height = max(height(y->gauche), height(y->droite)) + 1;

    return y;
}

// Obtenir le facteur d'équilibre
int getBalance(Node *root) {
    if (root == NULL)
        return 0;
    return height(root->gauche) - height(root->droite);
}

// Node* insert(Node* root, Joueurs jo) {
//     if (root == NULL) {
//         root = creerNouveauNode(jo);
//         return root;
//     } else if (jo.noJoueur < root->joueur.noJoueur) {
//         root->gauche = insert(root->gauche,jo);
//     } else {
//         root->droite = insert(root->droite,jo);
//     }
//     return root;
// }

// Insert node
Node* insert(Node *root, Joueurs jo) {
    // Trouvez la bonne position pour insérer Node le nœud et insérez-le Node it
    if (root == NULL)
        return creerNouveauNode(jo);

    if (jo.noJoueur < root->joueur.noJoueur)
        root->gauche = insert(root->gauche, jo);
    else if (jo.noJoueur > root->joueur.noJoueur)
        root->droite = insert(root->droite, jo);

    // Mettre à jour le facteur d'équilibre de chaque nœud et
    // Équilibrer l'arbre
    root->height = 1 + max(height(root->gauche),height(root->droite));

    int balance = getBalance(root);
    if (balance > 1 && jo.noJoueur < root->gauche->joueur.noJoueur)
        return rightRotate(root);

    if (balance < -1 && jo.noJoueur > root->droite->joueur.noJoueur)
        return leftRotate(root);

    if (balance > 1 && jo.noJoueur > root->gauche->joueur.noJoueur) {
        root->gauche = leftRotate(root->gauche);
        return rightRotate(root);
    }

    if (balance < -1 && jo.noJoueur < root->droite->joueur.noJoueur) {
        root->droite = rightRotate(root->droite);
        return leftRotate(root);
    }

    return root;
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

void entrerJoueur(Joueurs *jo, int id, int n) {
    printf("\nEntrer le joueur %d: \n", n+1);
    entrerInforJoueur(jo, id);
    printLine(70);
}

bool valideId(Node* root, int id) { //fonction pour rechercher
    if (root == NULL) {
        return false;
    } else if (root->joueur.noJoueur == id) {
        return true;
    } else if (id < root->joueur.noJoueur) {
        return valideId(root->gauche,id);
    } else if (id > root->joueur.noJoueur) {
        return valideId(root->droite,id);
    }
}

Node* entrerArbreJoueur(Node* root, int* n) {
    printf("\nEntrer le nombre de joueur: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        Joueurs jo; bool valide = true; int id;
        while (valide == true) { //c.à.d il existe un id double
            printf("\nEntrer l'id du joueur %d: ", i+1); scanf("%d",&id);
            valide = valideId(root,id);
            if (valide == true) {
                printf("\n=> Impossible d'ajouter un joueur car un identifiant en double existe deja!\n");
            }
        }
        entrerJoueur(&jo,id,i);
        root = insert(root, jo);
    }
    return root;
}

/*************Afficher_les_Joueurs_dans_un_tableau*************/

void afficherJoueur(Joueurs jo) {
     printf("=> [No Joueurs = %d | Nom et Prenom: %s | Num Uniforme: %s | Poste: %s\n    Stats: Points = %0.2lf, Passes = %0.2lf, Rebonds = %0.2lf\n    Nom Equipe: %s | Entraineur Chef: %s | Region: %s]\n",jo.noJoueur, jo.nom_prenom, jo.numUniforme, jo.poste, jo.points, jo.passes, jo.rebonds,jo.nomEquipe,jo.entraineurChef,jo.region);
}

void afficherTuplesJoueurs(Node* root) {
    if (root == NULL) { return; }
    printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", root->joueur.noJoueur, root->joueur.nom_prenom, root->joueur.numUniforme, root->joueur.poste, root->joueur.points, root->joueur.passes, root->joueur.rebonds, root->joueur.nomEquipe, root->joueur.entraineurChef, root->joueur.region);
    printf("\n");
    afficherTuplesJoueurs(root->gauche);
    afficherTuplesJoueurs(root->droite);
}

void afficherLesJoueurs(Node* root) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    afficherTuplesJoueurs(root);
}

/*************Trouver_le_meilleur_joueur_d'une_saison*************/

void countStatsMax(Node* root, Joueurs *MVP) {
    if (root == NULL) { return; }
    double max = (MVP->points + MVP->passes + MVP->rebonds) /3;
    if (((root->joueur).points+(root->joueur).passes+(root->joueur).rebonds)/3 > max) {
        *MVP = root->joueur;
    }
    countStatsMax(root->gauche,MVP);
    countStatsMax(root->droite,MVP);
}

void trouverMVP(Node* root) {
    if (root == NULL) { return; }
    Joueurs MVP = root->joueur;
    countStatsMax(root,&MVP);
    printf("\nLes informations de MVP: \n");
    afficherJoueur(MVP);
}

/*************Trouver_le_joueur_par_nom_et_prenom*************/

void trouverNom(Node* root, char nom[], Joueurs *joTrouve) {
    if (root == NULL) { return; }
    char temp[50]; strcpy(temp, root->joueur.nom_prenom);
    if (strstr(strupr(temp), strupr(nom))) {
        *joTrouve = root->joueur;
        return;
    } else {
        trouverNom(root->gauche,nom,joTrouve);
        trouverNom(root->droite,nom,joTrouve);
    }
}

void trouverJoueurNom(Node* root, char nom[]) {
    Joueurs jo; jo.noJoueur = 0;
    trouverNom(root,nom,&jo);
    if (jo.noJoueur != 0) {
        printf("\nLes informations de joueur recherchee:\n");
        afficherJoueur(jo);
    } else {
        printf("\n=> Aucun joueur valide trouve!");
    }
}

/*************Trouver_le_joueur_par_nom_d'equipe*************/

void afficherTuplesJoueursParNomEquipe(Node* root, char nomGroupe[], bool* valide) {
    if (root == NULL) { return; }
    char temp[50]; strcpy(temp, root->joueur.nomEquipe);
    afficherTuplesJoueursParNomEquipe(root->gauche,nomGroupe,valide);
    if (strstr(strupr(temp), strupr(nomGroupe))) {
        printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", root->joueur.noJoueur, root->joueur.nom_prenom, root->joueur.numUniforme, root->joueur.poste, root->joueur.points, root->joueur.passes, root->joueur.rebonds, root->joueur.nomEquipe, root->joueur.entraineurChef, root->joueur.region);
        printf("\n");
        *valide = true;
    }
    afficherTuplesJoueursParNomEquipe(root->droite,nomGroupe,valide);
}

void afficherJoueursParNomEquipe(Node* root, char nomGroupe[]) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    bool valide = false;
    afficherTuplesJoueursParNomEquipe(root,nomGroupe,&valide);
    if (!valide) { printf("\n=> Aucun equipe valide trouve!"); }
}

/*************Trouver_le_joueur_par_poste*************/

void afficherTuplesJoueursParPoste(Node* root, char nomPoste[], bool* valide) {
    if (root == NULL) { return; }
    char temp[50]; strcpy(temp, root->joueur.poste);
    afficherTuplesJoueursParPoste(root->gauche,nomPoste,valide);
    if (strcmp(strupr(temp), strupr(nomPoste)) == 0) {
        printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", root->joueur.noJoueur, root->joueur.nom_prenom, root->joueur.numUniforme, root->joueur.poste, root->joueur.points, root->joueur.passes, root->joueur.rebonds, root->joueur.nomEquipe, root->joueur.entraineurChef, root->joueur.region);
        printf("\n");
        *valide = true;
    }
    afficherTuplesJoueursParPoste(root->droite,nomPoste,valide);
}

void afficherJoueursParPoste(Node* root, char nomPoste[]) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    bool valide = false;
    afficherTuplesJoueursParPoste(root,nomPoste,&valide);
    if (!valide) { printf("\n=> Aucun equipe valide trouve!"); }
}

/*************Exporter_les_infors_vers_un_fichier*************/

void writeToFile(Node* root, FILE* file) {
    if (root == NULL) { return; }
    Joueurs jo = root->joueur; 
    fwrite(&jo,sizeof(Joueurs),1,file);
    writeToFile(root->gauche,file);
    writeToFile(root->droite,file);
}

void exporterVersFichier(Node* root, int n) {
    FILE *file = fopen("joueurs.txt","wb");
    if (file != NULL) {
        //Nombre de joueurs
        fwrite(&n, sizeof(n), 1, file);
        //Les infors des joueurs
        writeToFile(root,file);
    }
    fclose(file);
}

/*************Importer_des_infors_à_partir_d'un_fichier*************/

void importerAPartirFichier(Node** root, int *n) {
    FILE *file = fopen("joueurs.txt","rb");
    if (file != NULL) {
        //Nombre de joueurs
        fread(n, sizeof(*n), 1, file);
        //Les infors des joueurs
        for (int i = 0; i < *n; i++) {
            Joueurs jo;
            fread(&jo,sizeof(Joueurs),1,file);
            *root = insert(*root,jo);
        }
    }
    fclose(file);
}

/*************afficher_les_joueurs_dans_l'ordre_croissant*************/

void afficherTuplesJoueursCroissant(Node* root) {
    if (root == NULL) { return; }
    afficherTuplesJoueursCroissant(root->gauche);
    printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", root->joueur.noJoueur, root->joueur.nom_prenom, root->joueur.numUniforme, root->joueur.poste, root->joueur.points, root->joueur.passes, root->joueur.rebonds, root->joueur.nomEquipe, root->joueur.entraineurChef, root->joueur.region);
    printf("\n");
    afficherTuplesJoueursCroissant(root->droite);
}

void afficherCroissant(Node* root) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    afficherTuplesJoueursCroissant(root);
}

/*************trier_les_joueurs_dans_l'ordre_decroissant*************/

void afficherTuplesJoueursDecroissant(Node* root) {
    if (root == NULL) { return; }
    afficherTuplesJoueursDecroissant(root->droite);
    printf("%5d \t %25s \t %20s \t %15s \t %7.2lf \t %7.2lf \t %7.2lf \t %25s \t %20s \t %10s", root->joueur.noJoueur, root->joueur.nom_prenom, root->joueur.numUniforme, root->joueur.poste, root->joueur.points, root->joueur.passes, root->joueur.rebonds, root->joueur.nomEquipe, root->joueur.entraineurChef, root->joueur.region);
    printf("\n");
    afficherTuplesJoueursDecroissant(root->gauche);
}

void afficherDecroissant(Node* root) {
    printf("\n%5s \t %25s \t %20s \t %15s \t %7s \t %7s \t %7s \t %25s \t %20s \t %10s", "No", "Nom et Prenom", "Numero d'uniforme", "Poste", "Points", "Passes", "Rebonds", "Nom Equipe", "Nom entraineur chef", "Nom region");
	printf("\n");
    afficherTuplesJoueursDecroissant(root);
}

/*************ajouter_un_nouveau_joueur*************/

void ajouterNouveauJoueur(Node* root, int *n) {
    int id;
    printf("\nEntrer l'id du joueur %d: ", (*n)+1); scanf("%d",&id);
    bool valide = valideId(root,id);
    if (valide == true) { //c.à.d il existe un id double
        printf("\n=> Impossible d'ajouter un joueur car un identifiant en double existe deja!");
        return;
    }
    Joueurs jo; entrerJoueur(&jo,id,(*n)); root = insert(root,jo);
    (*n)++;
    exporterVersFichier(root,(*n));
    printf("\n=> Ajoute le joueur et mis a jour le joueur dans le fichier avec succes!");
}

/*************supprimer_un_joueur*************/

Node* minValueNode(Node *node) {
    Node* current = node;

    while (current->gauche != NULL)
        current = current->gauche;

    return current;
}

// Delete a nodes
Node* deleteNode(Node *root, int id) {
  // Trouver le node et le supprimer
    if (root == NULL) {
        return root;
    } else if (id < root->joueur.noJoueur) {
        root->gauche = deleteNode(root->gauche, id);
    } else if (id > root->joueur.noJoueur) {
        root->droite = deleteNode(root->droite, id);
    } else { //Woooh , il a été trouvé...
        if ((root->gauche == NULL) || (root->droite == NULL)) {
            Node *temp = root->gauche ? root->gauche : root->droite;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = minValueNode(root->droite);
            root->joueur = temp->joueur;
            root->gauche = deleteNode(root->gauche, temp->joueur.noJoueur);
        }
    }

    if (root == NULL)
        return root;

    // Mettre à jour le facteur d'équilibre de chaque nœud et
    // Équilibrer l'arbre
    root->height = 1 + max(height(root->gauche),height(root->droite));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->gauche) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->gauche) < 0) {
        root->gauche = leftRotate(root->gauche);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->droite) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->droite) > 0) {
        root->droite = rightRotate(root->droite);
        return leftRotate(root);
    }

    return root;
}

void supprimerUnJoueur(Node* root, int *n, int idTrouve) {
    bool valide = valideId(root,idTrouve);
    if (valide == false) {
        printf("\n=> Impossible de supprimer un joueur car il n'existe pas l'id correspondant!");
        return;
    }
    root = deleteNode(root,idTrouve);
    (*n)--;
    exporterVersFichier(root,(*n));
    printf("\n=> Supprime le joueur avec l'id '%d' et mis a jour le fichier avec succes!", idTrouve);
}

/*************free_Binary_Search_Tree*************/

void freeBST(Node* root) {
    if (root != NULL) {
        freeBST(root->gauche);
        freeBST(root->droite);
        free(root);
    }
}

/*************fonction_main_tester_toutes_les_fonctions*************/

int main() {
    //Nos données n'ont que 150 joueurs
    /*Dans le cas vous voulez ajouter un nouveau joueur
    alors nous avons mis 200 joueurs pour un tableau*/
	Node* root = NULL;
	int choix, n;
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
                // entrerTableauJoueur(jo,&n);
                root = entrerArbreJoueur(root, &n);
                printLine(70);
                break;
            case 2:
                printLine(70);
                afficherLesJoueurs(root);
                printLine(70);
                break;
            case 3:
                printLine(70);
                trouverMVP(root);
                printLine(70);
                break;
            case 4:
                printLine(70);
                char nomPrenom[50];
                printf("\nEntrer le nom et prenom de joueur pour trouver: "); fflush(stdin);
                gets(nomPrenom);
                trouverJoueurNom(root,nomPrenom);
                printLine(70);
                break;
            case 5:
                printLine(70);
                char nomGroupe[50];
                printf("\nEntrer le nom d'equipe pour afficher les joueurs: "); fflush(stdin);
                gets(nomGroupe);
                afficherJoueursParNomEquipe(root,nomGroupe);
                printLine(70);
                break;
            case 6:
                printLine(70);
                char nomPoste[50];
                printf("\nEntrer le nom de poste pour afficher les joueurs: "); fflush(stdin);
                gets(nomPoste);
                afficherJoueursParPoste(root,nomPoste);
                printLine(70);
                break;
            case 7:
                printLine(70);
                afficherCroissant(root);
                printLine(70);
                break;
            case 8:
                printLine(70);
                afficherDecroissant(root);
                printLine(70);
                break;
            case 9:
                printLine(70);
                ajouterNouveauJoueur(root,&n);
                printLine(70);
                break;
            case 10:
                printLine(70);
                int idSupprimer;
                printf("\nEntrer le numero de joueur que vous voulez supprimer: "); scanf("%d", &idSupprimer);
                supprimerUnJoueur(root,&n,idSupprimer);
                printLine(70);
                break;
            case 11:
                printLine(70);
                importerAPartirFichier(&root,&n);
                printf("\nImporter succes!");
                printLine(70);
                break;
            case 12:
                printLine(70);
                exporterVersFichier(root,n);
                printf("\nExporter succes!");
                printLine(70);
                break;
		}
	} while(choix!=0);
    freeBST(root);
}

