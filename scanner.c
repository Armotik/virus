//
// Created by armotik on 24/03/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "scanner.h"

void init_liste(ListeFichiers *liste, size_t capacite_initiale) {
    liste->fichiers = malloc(sizeof(char*) * capacite_initiale);
    liste->taille = 0;
    liste->capacite = capacite_initiale;
}

void ajouter_fichier(ListeFichiers *liste, const char *chemin) {
    if (liste->taille == liste->capacite) {
        liste->capacite *= 2;
        liste->fichiers = realloc(liste->fichiers, sizeof(char*) * liste->capacite);
    }
    liste->fichiers[liste->taille] = malloc(strlen(chemin) + 1);
    strcpy(liste->fichiers[liste->taille], chemin);
    liste->taille++;
}

void liberer_liste(ListeFichiers *liste) {
    for (size_t i = 0; i < liste->taille; ++i) {
        free(liste->fichiers[i]);
    }
    free(liste->fichiers);
}


int est_executable_regulier(const char *chemin) {
    struct stat st;

    if (stat(chemin, &st) != 0)
        return 0;

    return S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR);
}


void scanner_repertoire(const char *path, ListeFichiers *resultats) {
    DIR *dir;
    struct dirent *entry;
    char chemin_complet[MAX_PATH_LEN];

    dir = opendir(path);
    if (!dir) {
        perror("Erreur ouverture du répertoire");
        return;
    }

    printf("[*] Scan du dossier : %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(chemin_complet, sizeof(chemin_complet), "%s/%s", path, entry->d_name);

        if (est_executable_regulier(chemin_complet)) {
            printf("  [+] Exécutable trouvé : %s\n", chemin_complet);
            ajouter_fichier(resultats, chemin_complet);
        }
    }

    closedir(dir);
}