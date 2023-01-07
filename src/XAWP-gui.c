/*
 * Copyright (C) 2023 TheRealOne78 <bajcsielias78@gmail.com>
 * This file is part of the XAWP project
 *
 * XAWP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XAWP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XAWP. If not, see <http://www.gnu.org/licenses/>.
 */

/* Gtk */
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

/* Config */
#include <libconfig.h>

/* Basic programming */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XAWP created headers */
#include "info.h"
#include "XAWP-gui.h"

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);
  GtkApplication *app;
  int status;

  app = gtk_application_new("net.gui.XAWP", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
}

static void activate(GtkApplication *app, gpointer user_data) {
  GError *error = NULL;
  GtkBuilder *builder_main;
  GtkBuilder *builder_about_info;

  GObject *window; /* (GtkWindow) */
  GObject *window_headerbar; /* (GtkHeaderBar) */

  /* Header bar select + create buttons */
  GObject *window_headerbar_grid_always_buttonbox_button_select; /* (GtkButton) */
  GObject *window_headerbar_grid_always_buttobox_button_create; /* (GtkButton) */

  /* Main menu buttons */
  GObject *mainmenu_buttonmenu_select_configuration_file; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_create_configuration_file; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_convert_to_animated_images; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_clear_history; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_about_info; /* (GtkModelButton) */

  /* About info */
  GObject *popup_about_info; /* (GtkAboutDialog) */
  /* Construct a GtkBuilder instance and load our UI description */
  builder_main = gtk_builder_new();
  builder_about_info = gtk_builder_new();

  if(gtk_builder_add_from_file(builder_main, "../ui/main.ui", &error) == 0 ||
     gtk_builder_add_from_file(builder_about_info, "../ui/about-info.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(EXIT_FAILURE);
  }

  /* Declare a pointer for each Gtk object */
  window = gtk_builder_get_object(builder_main, "window");
  window_headerbar_grid_always_buttonbox_button_select = gtk_builder_get_object(builder_main, "window_headerbar_grid_always_buttonbox_button_select");
  window_headerbar_grid_always_buttobox_button_create = gtk_builder_get_object(builder_main, "window_headerbar_grid_always_buttobox_button_create");
  mainmenu_buttonmenu_select_configuration_file = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_select_configuration_file");
  mainmenu_buttonmenu_create_configuration_file = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_create_configuration_file");
  mainmenu_buttonmenu_convert_to_animated_images = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_convert_to_animated_images");
  mainmenu_buttonmenu_clear_history = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_clear_history");
  mainmenu_buttonmenu_about_info = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_about_info");
  popup_about_info = gtk_builder_get_object(builder_about_info, "popup_about_info");

  /* Connect signal handlers to the constructed widgets. */
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window_headerbar_grid_always_buttonbox_button_select, "clicked", G_CALLBACK(on_select_configuration_file), NULL);
  g_signal_connect(window_headerbar_grid_always_buttobox_button_create, "clicked", G_CALLBACK(on_create_configuration_file), NULL);
  g_signal_connect(mainmenu_buttonmenu_select_configuration_file, "clicked", G_CALLBACK(on_select_configuration_file), NULL);
  g_signal_connect(mainmenu_buttonmenu_create_configuration_file, "clicked", G_CALLBACK(on_create_configuration_file), NULL);
  g_signal_connect(mainmenu_buttonmenu_convert_to_animated_images, "clicked", G_CALLBACK(on_convert_images), NULL);
  g_signal_connect(mainmenu_buttonmenu_clear_history, "clicked", G_CALLBACK(on_clear_history), NULL);
  g_signal_connect(mainmenu_buttonmenu_about_info, "clicked", G_CALLBACK(on_about_info), popup_about_info);
  g_signal_connect(popup_about_info, "response", G_CALLBACK(close_about_dialog), NULL);

  /* Do all miscellaneous things for initial setup */
  gtk_header_bar_set_title(GTK_HEADER_BAR(gtk_builder_get_object(builder_main, "window_headerbar")), "XAWP-gui");
  gtk_window_set_transient_for(GTK_WINDOW(popup_about_info), GTK_WINDOW(window));

  gtk_main();
}

static void on_select_configuration_file(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_create_configuration_file(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_convert_images(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_clear_history(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_about_info(GtkWidget *widget, gpointer data) {
  GtkAboutDialog *popup_about_info = GTK_ABOUT_DIALOG(data);

  gtk_dialog_run(GTK_DIALOG(popup_about_info));
//TODO
}

static void close_about_dialog(GtkAboutDialog *popup_about_info, gint response_id, gpointer data) {
  gtk_widget_hide(GTK_WIDGET(popup_about_info));
}
