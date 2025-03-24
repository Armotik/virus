//
// Created by armotik on 24/03/25.
//

#ifndef SCANNER_H
#define SCANNER_H

#define MAX_PATH_LEN 1024

// Définition de la structure de la liste
typedef struct {
    char **fichiers;
    size_t taille;
    size_t capacite;
} ListeFichiers;

// Initialisation de la liste dynamique
void init_liste(ListeFichiers *liste, size_t capacite_initiale);

// Ajout d'un fichier à la liste
void ajouter_fichier(ListeFichiers *liste, const char *chemin);

// Libération mémoire de la liste
void liberer_liste(ListeFichiers *liste);

// Teste si un fichier est régulier et exécutable
int est_executable_regulier(const char *chemin);

// Scanner un répertoire pour les fichiers exécutables réguliers
void scanner_repertoire(const char *path, ListeFichiers *resultats);

#endif // SCANNER_H
