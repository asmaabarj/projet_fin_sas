#include<stdio.h>
#include<string.h>
#include<time.h>

typedef struct {
	int jour;
	int mois;
	int annee;
}delai;

typedef struct {
	int id;
	char titre[20];
	char description[100];
	delai d;
	char status[50];
}tache;

int identifiant=1,n=0,i,j;
tache t[100];

void ajouterUneSeuleTache(){
	t[n].id=identifiant;
	printf("id : %d\n",identifiant);
	printf("le titre :");
	scanf (" %s",&t[n].titre);
	printf("la description :");
	scanf (" %[^\n]",&t[n].description);
	printf("le delai (JJ/MM/AAAA):");
	scanf("%d/%d/%d",&t[n].d.jour,&t[n].d.mois,&t[n].d.annee);
	printf("le status (A REALISER / EN COURS DE REALISATION / FINALISEE):");
	scanf (" %[^\n]",&t[n].status);
	identifiant++;
    n++;
}


void ajouterPlusieursTaches(){
	int nbr;
    printf("veillez saisir le nombre des taches :");
    scanf("%d", &nbr);
	
    for (i=0;i<nbr;i++) {
        ajouterUneSeuleTache();
    }
}


void afficherTousLesTaches(){
    for (i=0;i<n;i++){
    printf("id : %d\n",t[i].id);
	printf("le titre :%s\n",t[i].titre);
    printf("la description :%s\n",t[i].description);
	printf("le delai :%d/%d/%d\n",t[i].d.jour,t[i].d.mois,t[i].d.annee);
	printf("le status : %s\n",t[i].status);
    }
}


void triParOrdreAlphabetique(){
    tache tmp;
    printf("tri des taches par ordre alphabetique :\n");
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(strcmp(t[j].titre,t[j+1].titre)>0){
                tmp =t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
        }
    }
    afficherTousLesTaches();
}


void triParDelai(){
    tache tmp;
     printf("tri des taches par delai :\n");
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
           if ((t[j].d.annee >t[j + 1].d.annee) || ((t[j].d.annee =t[j + 1].d.annee)&& (t[j].d.mois>t[j + 1].d.mois))||((t[j].d.annee =t[j + 1].d.annee) &&(t[j].d.mois=t[j + 1].d.mois)&&( t[j].d.jour>t[j+1].d.jour))) {
              tmp =t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
        }
    }
    afficherTousLesTaches();
}


void delaiDans3joursOuMoins() {
    time_t dateActuelle;
    time(&dateActuelle);

    printf("Affichage des taches avec un delai dans 3 jours ou moins :\n");
    for (i = 0; i < n; i++) {
        struct tm d;
        d.tm_year = t[i].d.annee - 1900;
        d.tm_mon = t[i].d.mois - 1;
        d.tm_mday = t[i].d.jour;

        time_t d_enSec = mktime(&d);

        
        double differenceEnSec = difftime(d_enSec, dateActuelle);
        int differenceEnJours = (int)(differenceEnSec / (24 * 3600));
        if (differenceEnJours <= 3 && differenceEnJours >= 0 ) {
            printf("Tache avec un delai dans %d jours ou moins :\n", differenceEnJours);
            printf("id : %d\n", t[i].id);
            printf("le titre : %s\n", t[i].titre);
            printf("la description : %s\n", t[i].description);
            printf("le delai : %d/%d/%d\n", t[i].d.jour, t[i].d.mois, t[i].d.annee);
            printf("le status : %s\n", t[i].status);
        //}else{
        //	printf("\n aucun tache aun delai de 3 jours ou moin");
		}
    }
}
 
 
void rechercheParId(){
     int ID;
     printf("veuillez saisir un identifiant :");
     scanf("%d",&ID);
      int found = 0;
      printf("tache avec le identifiant\"%d\":\n",ID);
     for(i=0;i<n;i++){
     	if(t[i].id==ID){
     	printf("la Tache existe \n");
            printf("id : %d\n", t[i].id);
            printf("le titre : %s\n", t[i].titre);
            printf("la description : %s\n", t[i].description);
            printf("le delai : %d/%d/%d\n", t[i].d.jour, t[i].d.mois, t[i].d.annee);
            printf("le statut : %s\n", t[i].status);
            found = 1; 
        }

     }if(!found){
        printf("Aucune tache existe pour le id : %d\n", ID);
        }
    }


void rechercheParTitre() {
    char TITRE[20];
    printf("Veuillez saisir un titre : ");
    scanf("%s", TITRE);
    int found=0;
    printf("Tâches avec le titre \"%s\" :\n", TITRE);

    for (i = 0; i < n; i++) {
        if (strcmp(t[i].titre, TITRE) == 0) {
            printf("Tache existe :\n");
            printf("id : %d\n", t[i].id);
            printf("le titre : %s\n", t[i].titre);
            printf("la description : %s\n", t[i].description);
            printf("le délai : %d/%d/%d\n", t[i].d.jour, t[i].d.mois, t[i].d.annee);
            printf("le statut : %s\n", t[i].status);
            found = 1; 
        }
        break;
    }

    if (!found) {
        printf("Aucune tache existe pour le titre : %s\n", TITRE);
    }
}


void modifierDescription(){
    int indice=-1;
	 int  Idrech;
	printf("veuillez saisir le id du tache qui vous voulez modifer sa discription");
	scanf("%d",&Idrech);

	for(i=0;i<n;i++){

		if(t[i].id==Idrech){
            indice = i;
            break;
        }
	}
      if (indice != -1)
    {


        char nouvellDescription[200];
        printf("Veuiller ecriver votre nouvelle description :");
        scanf(" %[^\n]", nouvellDescription);
        strcpy(t[i].description, nouvellDescription);
    }
    else
    {
        printf("Identifiant invalide.");
    }

    afficherTousLesTaches();

}


void modifierStatut(){
	int indice=-1;
	 int  Idrech;
	printf("veuillez saisir le id du tache qui vous voulez modifer son statut");
	scanf("%d",&Idrech);

	for(i=0;i<n;i++){
		if(t[i].id==Idrech){
            indice = i;
            break;
        }
    }
    if (indice != -1)
    {
        char nouveauStatut[200];
        printf("Veuiller ecriver votre nouveau statut :");
        scanf(" %[^\n]",nouveauStatut );
        strcpy(t[i].status, nouveauStatut);
    }
    else
    {
        printf("Identifiant invalide.");
    }
    afficherTousLesTaches();

}


void modifierDelai(){
	int indice=-1;
	 int  Idrech;
	printf("veuillez saisir le id du tache qui vous voulez modifer son delai");
	scanf("%d",&Idrech);

	for(i=0;i<n;i++){
		if(t[i].id==Idrech){
            indice = i;
            break;
        }
    }
    if (indice != -1)
    {
        int JOUR,MOIS,ANNEE;
        printf("Veuiller ecriver votre nouveau delai :");
        scanf(" %d/%d/%d",&JOUR,&MOIS,&ANNEE );
        t[i].d.jour=JOUR;
		t[i].d.mois=MOIS;
		t[i].d.annee =ANNEE;
    }
    else
    {
        printf("Identifiant invalide.");
    }
    afficherTousLesTaches();
}
void afficherNombreTaches(){
	int s=0;
	afficherTousLesTaches();
	s=s+i;
	printf("le nombre des taches est : %d",s);
}


void nombreTachesc() {
    printf("Tâches avec le statut 'finalise' ou 'en cours de ralisation' :\n");
    int s=0;
    for (i = 0; i < n; i++) {
        if (strcmp(t[i].status, "FINALISEE") == 0 || strcmp(t[i].status, "EN COURS DE REALISATION") == 0) {
            printf("id : %d\n", t[i].id);
            printf("le titre : %s\n", t[i].titre);
            printf("la description : %s\n", t[i].description);
            printf("le délai : %d/%d/%d\n", t[i].d.jour, t[i].d.mois, t[i].d.annee);
            printf("le statut : %s\n", t[i].status); 
			s++;
        }
    }printf("le nombre des taches est :%d",s);
}


void delaiJours() {
      time_t dateActuelle;
    time(&dateActuelle);

    printf("Affichage des taches avec un delai dans 3 jours ou moins :\n");
    for (i = 0; i < n; i++) {
        struct tm d;
        d.tm_year = t[i].d.annee - 1900;
        d.tm_mon = t[i].d.mois - 1;
        d.tm_mday = t[i].d.jour;


        time_t d_enSec = mktime(&d);

        
        double differenceEnSec = difftime(d_enSec, dateActuelle);
        int differenceEnJours = (int)(differenceEnSec / (24 * 3600));
         if (differenceEnJours>=0){
		 
            printf("id : %d\n", t[i].id);
            printf("le titre : %s\n", t[i].titre);
            printf("la description : %s\n", t[i].description);
            printf("le delai : %d/%d/%d\n", t[i].d.jour, t[i].d.mois, t[i].d.annee);
            printf("le status : %s\n", t[i].status);
             printf("le nombre de jours restants jusqu'au delai : %d\n",differenceEnJours);
        }else{
        	printf("la tache a depasser le delai");
		}
    }
}


void supprimerUneTache(){
      int iD;
    printf("Entrez l'ID de la tache a supprimer : ");
    scanf("%d", &iD);
    int index = -1;

    for ( i = 0; i < n; i++)
    {
        if (t[i].id ==iD)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
   
        for ( i = index; i < n - 1; i++)
        {
            t[i] = t[i + 1];
        } 
        n--; 
        printf("La tache avec l ID %d a ete supprimee.\n", iD);afficherTousLesTaches();
    }
    else
    {
        printf("Aucune tache avec cet ID n'a ete trouvee.\n");
    }
}



int main() {
    int choix,choixAjouter, choixTri, choixRecherche,choixModification, choixAffichage;

    do {
        printf("\n      _____________________________________Menu Principal_________________________________________\n");
        printf("     |                                                                                            |\n ");
        printf("    |                             1 - Ajouter des taches                                         |\n");
        printf("     |                             2 - Afficher les taches                                        | \n");
        printf("     |                             3 - Menu de Modifications                                      |\n");
        printf("     |                             4 - Supprimer une tache                                        |\n");
        printf("     |                             5 - Menu de Recherches                                         | \n");
        printf("     |                             6 - statistique                                                | \n");
        printf("     |                             0 - Quitter                                                    | \n");
        printf("     |____________________________________________________________________________________________|\n\n ");
        printf("\n                              Donnez un choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:

                printf(" \n       ******************************* Menu d'ajouter **********************************  \n");
                printf("\n ");
                printf("                             1 - Ajouter une seule tache \n");
                printf("                              2 - Ajouter plusieurs taches \n");
                printf("                              0 - Retour au menu principal\n\n");
                printf("                              Donnez un choix : ");
                scanf("%d", &choixAjouter);
                switch (choixAjouter) {
                    case 1:
                        ajouterUneSeuleTache();
                        break;
                    case 2:
                        ajouterPlusieursTaches();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Choix invalide. Reessayez.\n");
                }break;

            case 2:

                printf("\n  ******************************* Menu d'affichage ******************************* \n");
                printf("\n ");
                printf("                       1 - Tri par titre\n");
                printf("                        2 - Tri par délai\n");
                printf("                        3 - Afficher les taches avec un délai dans 3 jours ou moins\n");
                printf("                        0 - Retour au menu principal\n\n");
                printf("                        Donnez un choix : ");
                scanf("%d", &choixTri);

                switch (choixTri) {
                    case 1:
                        triParOrdreAlphabetique();
                        break;
                    case 2:
                        triParDelai();
                        break;
                    case 3:
                    	delaiDans3joursOuMoins();
                    	break;
                    case 0:
                        break; 
                    default:
                        printf("Choix invalide. Reessayez.\n");
                }break;

                case 3:
                

                printf("\n  ******************************* Menu de Modifications *******************************\n\n");
                printf("                           1 - Modifier la description d une tache\n");
                printf("                           2 - Modifier le statut d une tache\n");
                printf("                           3 - Modifier le delai d une tache\n");
                printf("                           0 - Retour au menu principal\n\n");
                printf("                                Donnez un choix : ");
                scanf("%d", &choixModification);

                switch (choixModification) {
                    case 1:
                        modifierDescription();
                        break;
                    case 2:
                        modifierStatut();
                        break;
                    case 3:
                        modifierDelai();
                        break;
                    case 0:
                        break; 
                    default:
                        printf("Choix invalide. Reessayez.\n");
                }
                break;

            case 4:
                supprimerUneTache();
                break;



            case 5:
                

                printf("\n  ******************************* Menu de Recherches *******************************\n\n");
                printf("                           1 - Rechercher une tache par ID\n");
                printf("                           2 - Rechercher une tache par titre\n");
                printf("                           0 - Retour au menu principal\n\n");
                printf("                               Donnez un choix : ");
                scanf("%d", &choixRecherche);

                switch (choixRecherche) {
                    case 1:
                        rechercheParId();
                        break;
                    case 2:
                        rechercheParTitre();
                        break;
                    case 0:
                        break; 
                    default:
                        printf("Choix invalide. Reessayez.\n");
                }
                break;


            case 6:
               

                printf("\n\n  ******************************* statistique *******************************\n\n");
                printf("                    1 - Afficher le nombre total des taches\n");
                printf("                    2 - Afficher le nombre de taches completes et incompletes\n");
                printf("                    3 - Afficher le nombre de jours restants jusqu au delai de chaque tache\n");
                printf("                    0 - Retour au menu principal\n\n");
                printf("                              Donnez un choix : ");
                scanf("%d", &choixAffichage);

                switch (choixAffichage) {
                    case 1:
                        afficherNombreTaches();
                        break;
                    case 2:
                        nombreTachesc();
                        break;
                    case 3:
                        delaiJours();
                        break;
                    case 0:
                        break; 
                    default:
                        printf("Choix invalide. Reessayez.\n");
                }
                break;
                case 0:
                printf("Au revoir !\n");
                break;
                default:
                printf("Choix invalide. Reessayez.\n");


        }
}while(choix!=0);

return 0;
}
