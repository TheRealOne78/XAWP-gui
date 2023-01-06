/*
 * Copyright (C) 2023 TheRealOne78 <bajcsielias78@gmail.com>
 *
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

  app = gtk_application_new("net.gui.XAWP", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
}

static void activate(GtkApplication *app, gpointer user_data) {
  GError *error = NULL;
  GtkBuilder *builder_main;
  GtkBuilder *builder_about_info;

  /* TODO: remove unnecessarry objects */
  GObject *window; /* (GtkWindow) */
  GObject *window_headerbar; /* (GtkHeaderBar) */


  /* Construct a GtkBuilder instance and load our UI description */
  builder_main = gtk_builder_new();
  builder_about_info = gtk_builder_new();

  if(gtk_builder_add_from_file(builder_main, "../src/ui-resources/main.ui", &error) == 0 &&
     gtk_builder_add_from_file(builder_about_info, "./ui-resources/about-info.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(EXIT_FAILURE);
  }

  /* Declare a pointer for each Gtk object */
  window = gtk_builder_get_object(builder_main, "window");

  /* Connect signal handlers to the constructed widgets. */
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  /* Do all miscellaneous things for initial setup */
  gtk_header_bar_set_title(GTK_HEADER_BAR(gtk_builder_get_object(builder_main, "window_headerbar")), "XAWP-gui");

  gtk_main();
}
