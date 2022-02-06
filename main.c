#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Définiton des types liste et noeud

typedef struct Noeud Noeud;
struct Noeud
{
    int data;
    Noeud *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Noeud *premier;
};

// Fonctions de base pour les listes

void initList( Liste *L )
{
    // On pointe le premier élément de la liste sur NULL
    L -> premier = NULL;
}

void remplirNoeud( Noeud *N )
{
    // On récupère une valeur saisie par l'utilisateur puis on l'enrégistre dans le noeud
    printf("Entrez votre valeur :");
    scanf("%d" , &N -> data );

    // On pointe l'élément suivant du noeud vers NULL
    N -> suivant = NULL;
}

void ajouterNoeud( Liste *L , Noeud *N )
{
    // On crée dynamiquement un noeud
    Noeud *N1 = malloc(sizeof(Noeud));

    // On lui assigne les valeurs contenues dans le noeud passé en paramètre a la fonction
    N1 -> data = N -> data;
    N1 -> suivant = NULL;

    // On vérifie si le premier element est null
    if ( L -> premier == NULL )
    {
        // Si c'est le cas on lui assigne N1
        L -> premier = N1;
    }
    else
    {
        // Si non on met le nouvel element en tête de liste
        N1 -> suivant = L -> premier;
        L -> premier = N1;
    }
}

void afficherListe( Liste L )
{
    printf("Votre liste est :\n");

    // Si la liste est vide , on envoi un message
    if ( L.premier == NULL )
        printf("La liste est vide\n");

    else
    {
        // Si non on crée un noeud auquel on assigne le premier element de la liste
        Noeud *N = L.premier;

        // On parcours la liste et on affiche pour chaque élement sa valeur
        do
        {
            printf("%d\n" , N -> data );

            N = N -> suivant;
        } while ( N != NULL );
    }
}




// Variables globales DU programme

static int continuer = 1;
    // Déclaration d'une liste et d'un noeud
Liste liste , listeFusion;
Noeud noeud , noeudFusion;



// Entetes des fonctions secondaires

void creerListe( Liste * L , Noeud * N );
void ajoutTeteListe( Liste *L , Noeud *N );
void ajoutQueueListe( Liste *L );
void trierListe( Liste *L );
void supprimerElement( Liste *L );
void supprimerDoublons( Liste *L );
void supprimerDernierElement( Liste *L );
void fusionnerListes();
void inverserListe( Liste * L);
void verifierPalyndrome( Liste *L );
void menuOptions();
void menu(int option);
void processStart();
void stopProcess();

// Programme principal

int main()
{
    processStart();
    return 0;
}


// Corps des fonctions secondaires

void creerListe( Liste * L , Noeud * N )
{
    char creer = 'O';
    initList(L);
    while ( creer == 'O' )
    {
        remplirNoeud(N);
        ajouterNoeud(L , N );

        printf("Voulez vous ajouter un element a liste ?? O ou N ?\n");
        getchar();
        scanf("%c" , &creer );
        creer = toupper(creer);

    }
}

void ajoutTeteListe( Liste *L , Noeud *N )
{
    // On remplis le noeud
    remplirNoeud(N);

    // On ajoute ce noeud en tete de liste
    ajouterNoeud(L , N );
}

void ajoutQueueListe( Liste *L )
{

    // On alloue dynamiquement un noeud
    Noeud *N1 = malloc( sizeof(Noeud) );

    // On recupere la saisie de la valeur par l'utilisateur dans le noeud et on initialise son pointeur vers null
    printf("Saisir une valeur :\n");
    scanf("%d" , &N1 -> data );
    N1 -> suivant = NULL;

    // Si le premier element de la liste est null , on met notre noeud en tete
    if ( L -> premier == NULL )
        L -> premier = N1;
    else
    {
        // Si non on le met en queue de liste
        Noeud *ptr = L -> premier;
        int q = 0;
        do
        {
            if ( ptr -> suivant  == NULL )
            {
                ptr -> suivant = N1;
                q = 1;
            }
            ptr = ptr -> suivant;

        } while ( q == 0 );
    }
}

void trierListe( Liste *L )
{
    Noeud *next , *courant;
    int temp , permute = 1;
    courant = L -> premier;

    while ( permute == 1 )
    {
        permute = 0;

        for ( courant = L -> premier ; courant -> suivant != NULL ; courant = courant -> suivant )
        {
            if ( courant -> suivant != NULL )
            {
                next = courant -> suivant;
                if ( courant -> data > next -> data )
                {
                    temp = next -> data;
                    next -> data = courant -> data;
                    courant -> data = temp;
                    permute = 1;
                }
            }
        }
    }
}
void supprimerElement( Liste *L )
{
    // Variable pour verifier si l'élément est contenu dans  la liste
    int trouvé = 0 , count = 0 , element;

    // Si la liste est vide on envoi un message
    if ( L -> premier == NULL )
    {
        printf("La liste est vide !! \nRemplissez la d'abord avant de supprimer un élément.\n\n");
    }

    // Si non on supprime l'élément
    else
    {
        printf("Entrez la valeur : \n");
        scanf("%d" , &element );

        Noeud *ptr = L -> premier;
        Noeud *precedent = L -> premier;
        do
        {
            if ( ptr -> data == element )
            {
                // On confirme que l'élément est trouvé
                trouvé = 1;
                precedent -> suivant = ptr -> suivant;
                free(ptr);
            }
            else
            {
                ptr = ptr -> suivant;
                count++;
                if ( count > 1 )
                precedent = precedent -> suivant;
            }
        } while ( ptr -> suivant != NULL && trouvé == 0 );

        // Si l'élement n'est pas contenu dans la liste on envoi un message
        if ( trouvé == 0 )
            printf("L'élement que vous cherchez à supprimer n'est pas dans la liste !\n");
    }
}

void supprimerDoublons( Liste *L )
{
     // On déclare une variable noeud qu'on initialise avec l'élement en tete
     Noeud *lTemp = L -> premier;

     // Tant que notre noeud n'est pas null
     while ( lTemp )
     {
        // On declare et initialise deux variables noeuds.La première recoit le noeud ltemp et
        // la seconde recoit son suivant
        Noeud *lPrecd = lTemp;
        Noeud *lSuiv = lTemp -> suivant;

      while ( lSuiv )
      {
            // Si on trouve un doublon on le supprime
            if ( lSuiv -> data == lTemp -> data )
            {
                lPrecd -> suivant = lSuiv -> suivant;
                lSuiv = lPrecd -> suivant;
            }

            // Si non on evolue dans la liste
            else
            {
                lPrecd = lSuiv;
                lSuiv = lSuiv -> suivant;
            }
      }

      lTemp = lTemp -> suivant;
    }
}

void supprimerDernierElement( Liste *L )
{
    // On crée une variable count et une variable q qu'on initialise
    int count = 0 , q = 0;

    // Si la liste est vide on envoie un message
    if ( L == NULL ) printf("La liste est vide\n");

    // On cree deux noeuds precedent et suivant (ptr)
    Noeud *precedent , *ptr;

    // On affecte a ptr et precedent la tete de la liste
    ptr = L -> premier;
    precedent = L -> premier;

    if ( ptr -> suivant == NULL )
    {
        free( ptr -> suivant );
        precedent -> suivant = NULL;
    }
    else
    {
        // On parcours la liste  avec le suivant
        do
        {
            // Lorsque le suivant pointera vers une adresse nulle on supprime cet element et on pointe l'element
            //qui le précède vers null
            if ( ptr -> suivant == NULL )
            {
                precedent -> suivant = NULL;
                free(ptr);
                q = 1;
            }
            ptr = ptr -> suivant;
            count++;
            if ( count > 1 ) precedent = precedent -> suivant;
        } while ( q == 0 );
    }
}

void fusionnerListes( Liste *L , Noeud *N )
{
    //  On cree une seconde liste
    printf("Creer une seconde liste pour la fusion : \n");
    creerListe( &listeFusion , &noeudFusion );
    afficherListe( listeFusion );

    // Si la premiere liste est vide , on assigne la tete de la deuxieme liste a sa tete
    if ( L -> premier == NULL )
    {
        L -> premier = listeFusion.premier;
    }

    // Si non
    else
    {

        // On cree deux noeuds et une variable de poursuite qu'on initialise
        Noeud *ptr = L -> premier , *ptrF = listeFusion.premier;
        int q = 0;

        // Si la premiere liste est vide , on la remplace par la seconde
        do
            {
                // Lorsque le suivant pointera vers une adresse nulle on supprime cet element et on pointe l'element
                //qui le précède vers le premier element de la seconde liste
                if ( ptr -> suivant == NULL )
                {
                    ptr -> suivant = ptrF;
                    q = 1;
                }
                ptr = ptr -> suivant;
            } while ( q == 0 );
        }
    // On utilise la fonction tri pour trier la liste qu'on obtient
    trierListe( L );

    // On utilise la fonction supprimer doublons pour supprimer les doublons
    supprimerDoublons( L );
}

void inverserListe( Liste *L )
{
    // On déclare trois noeuds..Un recoit la tete de la liste et le reste est intialisé
    // à null
    Noeud *p = L -> premier , *q = NULL , *r = NULL;

    // On inverse la liste
    while ( p )
    {
        r = p -> suivant;
        p -> suivant = q;
        q = p;
        p = r;
    }
    L -> premier = q;

    // On affiche la liste apres son inversion
    printf("Votre liste est :\n");
    if ( L -> premier == NULL )
        printf("La liste est vide\n");
    else
    {
        Noeud *N = L -> premier;
        do
        {
            printf("%d\n" , N -> data );

            N = N -> suivant;
        } while ( N != NULL );
    }


}

void verifierPalyndrome( Liste *L )
{
    // On déclare une variable de poursuite
    int cont = 1;

    // On déclare deux noeuds et on initialise l'un avec le premier element de la liste
    Noeud *a = L -> premier , *b ;

    // On déclare une variable reverseList , on l'inverse puis on stocke son premier element dans le second noeud
    Liste *reverseList = L;
    inverserListe( reverseList );
    b = reverseList -> premier;

    // On parcours les deux listes
    do
    {
        // Tant qu'il y a equivalence entre les occurences on laisse la boucle tourner
        if ( a -> data != b -> data )
        {
            cont = 0;
        }

        //  Si on arrive en fin de liste on sors de la boucle
        if ( a -> suivant == NULL || b -> suivant == NULL ) break;

        // On passe à l'element suivant
        a = a -> suivant;
        b = b -> suivant;
    } while ( cont == 1 );

    // Affichage du message
    if ( cont == 1 ) printf("Cette liste est un palyndrome !\n");
    else printf("Cette liste n'est pas un palyndrome\n");
}

void menuOptions()
{
    printf("**************************Bienvenue dans ce programme***************************\n");
    printf("                                    MENU                            \n");
    printf("1-Creer une liste chainée d'entier\n");
    printf("2-Ajouter un élément en tête de liste\n");
    printf("3-Ajouter un élément en queue de liste\n");
    printf("4-Trier une liste\n");
    printf("5-Supprimer un élément donné de la liste\n");
    printf("6-Supprimer les doublons de la liste\n");
    printf("7-Supprimer le dernier élément de la liste\n");
    printf("8-Fusionnner deux listes\n");
    printf("9-Inverser une liste\n");
    printf("10-Vérifier si une liste est un palyndrome\n");
    printf("11-Quitter\n");
    printf("*******************************************************************************\n");
}
void menu(int option)
{
    switch (option)
    {
        case 1 :
            // Creer une liste chainée
            creerListe( &liste , &noeud );
            afficherListe(liste);
            break;
        case 2 :
            // Ajouter un élément en tete de liste
            ajoutTeteListe( &liste , &noeud );
            break;
        case 3 :
            ajoutQueueListe( &liste );
            break;
        case 4 :
            trierListe( &liste );
            break;
        case 5 :
            supprimerElement(&liste);
            break;
        case 6 :
            supprimerDoublons( &liste );
            break;
        case 7 :
            supprimerDernierElement( &liste );
            afficherListe(liste);
            break;
        case 8 :
            fusionnerListes( &liste , &noeud );
            break;
        case 9 :
            inverserListe( &liste );
            break;
        case 10 :
            verifierPalyndrome( &liste );
            break;
        case 11 :
            stopProcess();
            break;
        case 12 :
            afficherListe(liste);
            break;
        default :
            system("clear");
            processStart();
    }
}

void stopProcess()
{
    char choice = 'O';
    do
    {
        printf("Êtes vous sur de vouloir quitter le programme ? O ou N ?\n");
        scanf( "%c" , &choice );
        choice = toupper(choice);
    } while ( choice != 'O' && choice != 'N' );

    if ( choice == 'O' )
    {
        printf("_________________________________( BYE !!!!! )________________________________\n");
        continuer = 0;
    }

    else
    {
        system("clear");
        processStart();
    }
}

void processStart()
{
    int option;
    while (continuer)
    {
        menuOptions();
        printf("Entrez votre choix :\n");
        scanf( "%d", &option);
        menu(option);
    }

}
