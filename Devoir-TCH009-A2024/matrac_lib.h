#ifndef MATRAC_LIB_H        // pour eviter d'inclure plusieurs fois le meme module
#define MATRAC_LIB_H

/*
Auteur: David Marche
Date: Automne 2016

Ce module contient les constantes et prototypes des fonctions d'analyse de traces GPS

*/

//Constantes physiques
#define PI  3.14159
#define RAYON_TERRE 6366     // Rayon de la terre (en km) pour les calculs de distances

// prototypes
/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: lire_donnees_gps
	Auteur: David Marche
	Description:
		Cette fonction lit un fichier de donnees GPS et place toutes les donnees de lattitude, longitude,altitude et
		temps dans des tableaux statiques fournis en parametres. Le format du fichier est le suivant :
		No,Latitude,Longitude,Altitude,Date,Time
		1,49.192273,-123.178443,-44.6,2013/06/21,11:02:00
		2,49.192272,-123.178318,-44.6,2013/06/21,11:02:03
		3,49.192184,-123.178061,-41.7,2013/06/21,11:02:10
		...

	Parametres:
		nom_fichier         nom du fichier a lire
		tab_latitudes	    tableau a remplir avec les valeurs de latitude
		tab_longitudes		tableau a remplir avec les valeurs de longitude
		tab_altitudes		tableau a remplir avec les valeurs d'altitude
		taille_max		    nombre maximum de valeurs pouvant etre chargees dans les tableaux

	Valeur de retour:
		Le nombre de points lus, 0 si aucun, -1 si probleme d'ouverture/lecture de fichier,
	Note:
		- Les tableaux donnees en parametre sont modifies;
		- Les valeurs de temps presentes dans le fichier sont ignores.
	Cas particuliers:
		- Si le fichier ne peut pas etre ouvert la fonction renvoie -1;
		- Si la ligne d'en tete n'est pas presente en premiere ligne du fichier, la fonction renvoie -1;
		- Si le nombre de valeurs du fichier depasse la capacite du tableau, les valeurs en trop sont ignorees.
*/
int lire_donnees_gps(char nom_fichier[],
	                 double tab_latitudes[],
	                 double tab_longitudes[],
	                 double tab_altitudes[],
	                 int taille_max);




/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: convertir_en_radian
	Auteur:
	Description:
		Cette fonction convertit en radians une valeur d'angle donnee initialement en degres.
	Parametres:
		angle		 la valeur en degres
	Valeur de retour:
		la valeur correspondante en radians.
*/
double convertir_en_radian(double angle);

/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: distance_entre_2_points
	Auteur:
	Description:
		Cette fonction calcule la distance entre 2 points decrits par leurs latitudes, longitudes et altitudes
	Parametres:
		latitude1	latitude du premier point
		longitude1	longitude du premier point
		altidute1	altidute du premier point en metre
		latitude2	lattitude du second point
		longitude2	longitude du second point
		altidute2	altidute du second point en metre
	Valeur de retour:
		la distance calculee en km
	Note:
		- Vous devez utiliser une constante definissant le rayon de la terre (RAYONTERRE) en km;
		- Vous devez utiliser des fonctions de la librairie math.h (asin, sin, cos, pow, sqrt).
	Source:
		Calcul inspire d'une formule de www.partir_en_vtt.com. Cette formule est decrite en annexe de l'enonce du devoir.
*/
double distance_entre_2_points(double latitude1,
	                           double longitude1,
	                           double latitude2,
	                           double longitude2,
	                           double altidute1,
	                           double altidute2);

/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: afficher_tableau
	Auteur:
	Description:
		Cette fonction affiche le contenu d'un tableau 1D de double (1 valeur par ligne).
	Parametres:
		tableau		le tableau de valeurs (type double)
		nb_valeurs	le nombre de valuer a afficher
	Valeur de retour:
		Aucune.
	Note:
		- Le tableau n'est pas modifie;
		- Aucune verification sur la validite de nb_valeur n'est effectuee (ex: nb_valeur>taille du tableau)
*/
void afficher_tableau(double tableau[], int nb_valeurs);

/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: distance_totale
	Auteur:
	Description:
		Cette fonction calcule la distance parcourue par une trace definie par des tableaux avec les informations GPS de
		tous les points de la trace. debut et fin permettent de preciser les indices des points entre lesquels la
		distance doit etre calculee. Si debut=0 et fin=taille-1, c'est la distance totale qui est calculee.
	Parametres:
		tab_latitudes		tableau des valeurs de latitude
		tab_longitudes		tableau des valeurs de longitude
		tab_altitudes		tableau des valeurs d'altitude
		taille			    nombre de valeurs valides presentes dans les tableaux
		debut			    indice du premier point gps a prendre en compte dans le calcul
		fin				    indice du dernier point gps a prendre en compte dans le calcul
	Valeur de retour:
		La distance calculee en km.
	Cas particuliers:
		Si un des deux index est invalide (plus petit que 0 ou plus grand que taille) la distance renvoyee est 0.

*/
double distance_totale(double tab_latitudes[],
	                   double tab_longitudes[],
	                   double tab_altitudes[],
	                   int taille,
	                   int debut,
	                   int fin);

/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: minimum_tableau
	Auteur:
	Description:
		Cette fonction retourne la valeur minimale d'un tableau de reels.
	Parametres:
		taille	    nombre de points present dans le tableau
		tableau		tableau des valeurs dans lequel la recherche du minimum doit se faire
		minimum	    valeur minimale trouvee dans le tableau (recu par adresse)
	Valeur de retour:
		1 en cas de resultat valide, 0 sinon (taille<=0)
	Note:
		La valeur min est stockee dans valmin qui est transmise par adresse.
	Cas particulier:
		si taille est nulle ou negative, la valeur renvoyee est 0 et valmin est fixe a 0.
*/
int minimum_tableau(double tableau[], int taille, double* minimum);

/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: maximum_tableau
	Auteur:
	Description:
		Cette fonction retourne la valeur maximale d'un tableau de reels.
	Parametres:
		taille	    nombre de points present dans le tableau
		tableau		tableau des valeurs dans lequel la recherche du maximum doit se faire
		maximum	    valeur maximale trouvee dans le tableau (recu par adresse)
	Valeur de retour:
		1 en cas de resultat valide, 0 sinon (taille<=0)
	Note:
		La valeur max est stockee dans valmax qui est transmise par adresse.
	Cas particulier:
		si taille est nulle ou negative, la valeur renvoyee est 0 et valmax est fixe a 0.
*/

int maximum_tableau(double tableau[], int taille, double* maximum);

/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: ascension
	Auteur:
	Description:
		Cette fonction calcule le total de montee le long d'une trace les information d'altitude des points de la trace
		sont fournies dans un tableau en parametre (tab_altitudes). Le calcul se fait en ajoutant les contributions de
		gain d'altitude de chacun des segments de la trace. Les segments qui sont en descente (perte d'altitude) sont
		ignores.
	Parametres:
		tab_altitudes	tableau des valeurs d'altitudes
		taille		    nombre de points present dans le tableau d'altitude
	Valeur de retour:
		L'ascension totale calculee (en metres).
	Cas particulier:
		Si la valeur de la taille est nulle ou negative, la valeur renvoyee est 0.

*/
double ascension(double tab_altitudes[], int taille) ;


/* ---------------------------------------------------------------------------------------------------------------------
	Fonction: pente_maximale
	Auteur:
	Description:
		Cette fonction calcule la pente maximale de la trace. Pour diminuer l'effet des variations locale (ex: une
		personne se met debout avec le GPS dans la main) la pente est obtenu par une moyenne glissante prenant toujours
		en compte taille_fenetre segments de chaque cote du point de calcul.

	Exemple de points utilises pour le calcul de variation d'altitude avec taille_fenetre=5:
		- la pente aux points 0-4: pas defini
		- la pente au point 5 est la pente moyenne de 5 segments avant le point 5 et de 5 segments apres le point 5
		  (points 0-10)
		- la pente au point 6 est la pente moyenne de 5 segments avant le point 6 et de 5 segments apres le point 6
		  (points 1-11)
		-...
		- la pente au point x est la pente moyenne de 5 segments avant le point x et de 5 segments apres le point x
		  (points (x-5) a (x+5))
		- la pente des 4 derniers points pas definis

	Parametres:
		tab_latitudes		tableau des valeurs de latitude
		tab_longitudes		tableau des valeurs de longitude
		tab_altitudes		tableau des valeurs d'altitude
		taille			    nombre de valeurs presentes dans les tableaux
		taille_fenetre	    nombre de segments de trace a considerer avant et apres chaque point de calcul de pente
	Valeur de retour:
		la pente maximale calculee
	Note:
		Attention la distance parcourue doit etre calculee en suivant la trace avec la fonction distance_totale.
		Si la distance entre 2 points est nulle, on suppose que la pente est nulle pour eviter une division par 0.
	Cas particuliers:
		- Si taille_fenetre est invalide (valeur nulle ou negative) la fonction renvoie 0;
		- Si taille_fenetre est trop grand et qu'il n'y a pas assez de points disponibles dans les tableaux de donnees,
		  la fonction renvoi 0.

*/
double pente_maximale(double tab_latitudes[], double tab_longitudes[], double tab_altitudes[], int taille, int taille_fenetre);

#endif
