#ifndef CONFIG_H
#define CONFIG_H

/*
Auteur: David Marche
Date: Automne 2016

Ce module contient les constantes du projet

*/

// Constantes
// Choix du menu
#define CHARGER           1
#define AFFICHER          2
#define ANALYSER          3
#define CALCULER          4
#define QUITTER           5

// Valeurs maximales pour les tableaux statiques
#define LONGUEUR_MAX_NOM_FICHIER    100    //longueur maximale pour le nom de fichier
#define NB_MAX_POINT              10000    //nombre maximal de points dans une trace (pour creer les tableaux statiques)
#define LONGUEUR_MAX_LIGNE         1000    //longueur maximale d'une ligne dans le fichier de donnees CSV

#endif