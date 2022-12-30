/*
 * Copyright (C) 2022 TheRealOne78 <bajcsielias78@gmail.com>
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

/* Config */
#include <libconfig.h>

/* Basic programming */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  GObject *main_window;
  GError *error = NULL;
  GtkBuilder *builder_main;
  GtkBuilder *builder_about_info;

  gtk_init(&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder_main = gtk_builder_new();
  builder_about_info = gtk_builder_new();
  if(gtk_builder_add_from_file(builder_main, "./ui-resources/main.ui", &error) == 0 &&
     gtk_builder_add_from_file(builder_about_info, "./ui-resources/about-info.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(EXIT_FAILURE);
  }

  /* Connect signal handlers to the constructed widgets. */
  main_window = gtk_builder_get_object(builder_main, "window");
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();
}
