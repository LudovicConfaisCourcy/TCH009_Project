/*
Auteur(s):
Date:

Ce module contient les implementations des fonctions d'analyse de traces GPS

*/

#define _CRT_SECURE_NO_WARNINGS

// Librairies standard
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "matrac_lib.h"

int lire_donnees_gps(char nom_fichier[],
	                 double tab_latitudes[],
	                 double tab_longitudes[],
	                 double tab_altitudes[],
	                 int taille_max) {
	int nb_point = 0;						            // nombre de points trouves
	char ligne[LONGUEUR_MAX_LIGNE];			            // chaine de caractere contenant la balise
	FILE* fp;								            // pointeur au fichier a lire
	int no, an, mois, jour, heure, minute, seconde;		// informations lues du fichier
	double latitude, longitude, altitude;

	// ouverture du fichier et verification du succes de l'ouverture
	fp = fopen(nom_fichier, "r"); // en mode lecture seulement

	if (fp == NULL) {
		nb_point = -1;
	} else {
		// sauter l'en-tete
		if (fgets(ligne, LONGUEUR_MAX_LIGNE - 1, fp) == NULL) {
			nb_point = -1;

			// continuer la lecture si fichier n'est pas vide
		} else {

			// boucle de lecture principale de chaque point (un par ligne)
			while ((fgets(ligne, LONGUEUR_MAX_LIGNE - 1, fp) != NULL) && (nb_point < taille_max)) {
				// lecture d'un point et identification des 10 champs attendus:
				// No,Latitude,Longitude,Altitude,Date(a/m/j),Time(h:m:s)
				if (sscanf(ligne, "%d,%lf,%lf,%lf,%d/%d/%d,%d:%d:%d", &no,
				                                                      &latitude,
				                                                      &longitude,
				                                                      &altitude,
				                                                      &an,
				                                                      &mois,
				                                                      &jour,
				                                                      &heure,
				                                                      &minute,
				                                                      &seconde) == 10){

					//si decodage correct,mise en memoire de la latitude, longitude,altitude
					tab_latitudes[nb_point] = latitude;
					tab_longitudes[nb_point] = longitude;
					tab_altitudes[nb_point] = altitude;

					// incrementer le nombre de points correctement lus
					nb_point++;
				}
			}
		}
		// fermeture du fichier
		fclose(fp);
	}

	if (nb_point >= 0) {
		printf("\n...%d points lus\n", nb_point);
	}else {
		printf("\n...probleme de lecture du fichier\n");
	}
	//renvoi du nombre de points trouves
	return nb_point;

}

// implementations des fonctions de matrac_lib (c.f. prototype et doc dans matrac_lib.h)

double convertir_en_radian(double angle){
	return angle * PI / 180;
}

double distance_entre_2_points(double latitude1,
							   double longitude1,
							   double latitude2,
							   double longitude2,
							   double altidute1,
							   double altidute2){

	double delta_lat= convertir_en_radian(latitude2-latitude1)/2;
	double lat1 = convertir_en_radian(latitude1);
	double lat2 = convertir_en_radian(latitude2);
	double delta_long = convertir_en_radian((longitude2-longitude1))/2;

	double d = RAYON_TERRE * 2 * asin(sqrt(pow(sin(delta_lat),2) + (cos(lat1)) * cos(lat2) * pow(sin(delta_long), 2)));
	double d_tot = sqrt(pow(d,2) + pow((altidute2 - altidute1)/1000,2));

	return d_tot;
}

void afficher_tableau(double tableau[], int nb_valeurs) {
	for (int i = 0; i < (nb_valeurs); i++) {
		printf("%lf\n", tableau[i]);
	}
}

double distance_totale(double tab_latitudes[],
					   double tab_longitudes[],
					   double tab_altitudes[],
					   int taille,
					   int debut,
					   int fin){

	double total = 0;

	if(debut < 0 || fin > taille) {
		return 0;
	}

	for(int i = debut; i < fin-1; i++){
		total += distance_entre_2_points(tab_latitudes[i], tab_longitudes[i], tab_latitudes[i+1], tab_longitudes[i+1], tab_altitudes[i], tab_altitudes[i+1]);

}

	return total;
}

int minimum_tableau(double tableau[], int taille, double* minimum){

	if (taille <= 0) {
		*minimum = 0;
		return 0;
	}

	*minimum = tableau[0];
	for (int i = 1; i < (taille); i++) {
		if(*minimum > tableau[i]) {
			*minimum = tableau[i];
		}
	}
	return 1;
}

int maximum_tableau(double tableau[], int taille, double* maximum){

	if (taille <= 0) {
		*maximum = 0;
		return 0;
	}

	*maximum = tableau[0];
	for (int i = 1; i < (taille); i++) {
		if(*maximum < tableau[i]) {
			*maximum = tableau[i];
		}
	}
	return 1;
}

double ascension(double tab_altitudes[], int taille) {
	double tot = 0;
	for(int i = 0; i < taille; i++) {
		if(tab_altitudes[i+1] > tab_altitudes[i]) {
			tot += (tab_altitudes[i+1] - tab_altitudes[i]);
		}
	}
	return tot;
}

double pente_maximale(double tab_latitudes[], double tab_longitudes[], double tab_altitudes[], int taille, int taille_fenetre) {
 // pas fini
	int i;
	double pente = 0;

	for(i = 0; i < taille; i++) {
		pente = (tab_altitudes[i+1]-tab_altitudes[i])/distance_entre_2_points(tab_latitudes[i],tab_latitudes[i+1],tab_longitudes[i],tab_longitudes[i+1],tab_altitudes[i],tab_altitudes[i]);
	}

	return pente;
}
