#include "menu.h"
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "config.h"

int afficher_menu() {
	int choix;
	printf("\n");
	printf("\n--- MENU PRINCIPAL ---\n");
	printf("%d. Charger la trace d'un fichier de donnees GPS\n", CHARGER);
	printf("%d. Afficher les donnees de la trace en memoire\n", AFFICHER);
	printf("%d. Analyse de base la trace\n", ANALYSER);
	printf("%d. Calculer la pente maximale\n", CALCULER);
	printf("%d. Quitter \n", QUITTER);
	fflush(stdout);     // par securite, vider les buffers avant la lecture du choix
	fflush(stdin);
	scanf("%d", &choix); // lecture du choix au clavier
	return choix;
}
