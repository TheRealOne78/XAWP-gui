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
  GError *error = NULL;
  GtkBuilder *builder_main;
  GtkBuilder *builder_about_info;

  /* TODO: remove unnecessarry objects */
  GObject *window_headerbar; /* (GtkHeaderBar) */
  GObject *window_headerbar_grid_stack_1_buttonbox; /* (GtkButtonBox) */
  GObject *workbench_config_parameter_grid; /* (GtkGrid) */
  GObject *window_headerbar_grid_stack_1_buttonbox_cancel; /* (GtkButton) */
  GObject *window_headerbar_grid_stack_1_buttonbox_save; /* (GtkButton) */
  GObject *window_grid_body; /* (GtkGrid) */
  GObject *icon_apply; /* (GtkImage) */
  GObject *body_mainmenu_buttonmenu_aspectframe; /* (GtkAspectFrame) */
  GObject *window_headerbar_grid_always_buttobox_button_create; /* (GtkButton) */
  GObject *window_grid_separator_body_statusbar; /* (GtkSeparator) */
  GObject *icon_create; /* (GtkImage) */
  GObject *body_mainmenu_buttonmenu_buttonbox; /* (GtkButtonBox) */
  GObject *workbench_home_stack_empty_history; /* (GtkLabel) */
  GObject *workbench_config_description_frame_label; /* (GtkLabel) */
  GObject *mainmenu_buttonmenu_clear_history; /* (GtkModelButton) */
  GObject *window_headerbar_grid_stack_0_grid; /* (GtkGrid) */
  GObject *icon_save; /* (GtkImage) */
  GObject *window_grid; /* (GtkGrid) */
  GObject *mainmenu_buttonmenu_select_configuration_file; /* (GtkModelButton) */
  GObject *body_workbench_stack; /* (GtkStack) */
  GObject *window_headerbar_grid_workbench; /* (GtkGrid) */
  GObject *workbench_home_stack; /* (GtkStack) */
  GObject *body_mainmenu; /* (GtkGrid) */
  GObject *workbench_config_description_frame; /* (GtkFrame) */
  GObject *icon_cancel; /* (GtkImage) */
  GObject *mainmenu_buttonmenu_convert_to_animated_images; /* (GtkModelButton) */
  GObject *window_grid_bottom_status_bar; /* (GtkStatusbar) */
  GObject *window_headerbar_grid_always; /* (GtkGrid) */
  GObject *workbench_config_description_frame_alignment; /* (GtkAlignment) */
  GObject *mainmenu_buttonmenu_about_info; /* (GtkModelButton) */
  GObject *workbench_home_stack_has_history; /* (GtkFixed) */
  GObject *window_headerbar_grid_always_buttonbox; /* (GtkButtonBox) */
  GObject *workbench_config_description_label; /* (GtkLabel) */
  GObject *icon_open; /* (GtkImage) */
  GObject *menu_main_menu_logo; /* (GtkImage) */
  GObject *workbench_config_paned; /* (GtkPaned) */
  GObject *body_separator_mainmenu_workbench; /* (GtkSeparator) */
  GObject *window; /* (GtkApplicationWindow) */
  GObject *mainmenu_buttonmenu_create_configuration_file; /* (GtkModelButton) */
  GObject *window_headerbar_grid_stack; /* (GtkStack) */
  GObject *window_headerbar_grid_stack_1_buttonbox_set_as_default; /* (GtkButton) */
  GObject *window_headerbar_grid_always_buttonbox_button_select; /* (GtkButton) */

  gtk_init(&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder_main = gtk_builder_new();
  builder_about_info = gtk_builder_new();
  if(gtk_builder_add_from_file(builder_main, "../src/ui-resources/main.ui", &error) == 0) {
     // && gtk_builder_add_from_file(builder_about_info, "./ui-resources/about-info.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(EXIT_FAILURE);
  }

  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object(builder_main, "window");
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();
}
