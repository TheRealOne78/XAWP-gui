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
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/* XAWP created headers */
#include "info.h"
#include "fancy-text.h"
#include "xawp-gui.h"
#include "dir-checker.h"
#include "history.h"

/* Where the default config exists. */
char default_config_path[PATH_MAX];

/* Where every data about history is located at */
XawpHistory_t history;

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);
  GApplication *app;
  int status;

  app = gtk_application_new("net.gui.XAWP", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
}

static void activate(GApplication *app, gpointer user_data) {
  GError *error = NULL;
  GtkBuilder *builder_main;
  GtkBuilder *builder_about_info;
  GtkBuilder *builder_popup;

  GObject *window; /* (GtkWindow) */
  GObject *window_headerbar; /* (GtkHeaderBar) */

  /* == Header Bar == */
  /* Header bar select + create buttons */
  GObject *window_headerbar_grid_always_buttonbox_button_select; /* (GtkButton) */
  GObject *window_headerbar_grid_always_buttobox_button_create; /* (GtkButton) */
  /* Header bar stack 1 aka config window */
  GObject *window_headerbar_grid_stack_1_buttonbox_cancel; /* (GtkButton) */
  GObject *window_headerbar_grid_stack_1_buttonbox_save; /* (GtkButton) */
  GObject *window_headerbar_grid_stack_1_buttonbox_set_as_default; /* (GtkButton) */

  /* == Main menu buttons == */
  GObject *mainmenu_buttonmenu_select_configuration_file; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_create_configuration_file; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_convert_to_animated_images; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_clear_history; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_about_info; /* (GtkModelButton) */

  /* == Stacks and their childs == */
  /* Body's workbench stack */
  GObject *body_workbench_stack; /* (GtkStack) */
  GObject *workbench_config_paned; /* (GtkPaned) - child of workbench stack */
  /* Workbench's home stack */
  GObject *workbench_home_stack; /* (GtkStack) - child of workbench stack */
  GObject *workbench_home_stack_empty_history; /* (GtkLabel) - child of home stack */
  GObject *workbench_home_stack_has_history; /* (GtkFixed) - child of home stack */

  /* == About info == */
  GObject *popup_about_info; /* (GtkAboutDialog) */

  /* == Popups related objects == */
  /* Config cancel */
  GObject *on_config_cancel_dialog;
  GObject *on_config_cancel_dialog_button_yes;
  GObject *on_config_cancel_dialog_button_no;
  /* Error */
  GObject *popup_error;
  GObject *popup_error_button_ok;

  /* Construct a GtkBuilder instance and load our UI description */
  builder_main = gtk_builder_new();
  builder_about_info = gtk_builder_new();
  builder_popup = gtk_builder_new();

  /* Add the UI files to builders and check if they opened correctly, else exit */
  if(gtk_builder_add_from_file(builder_main, "../ui/main.ui", &error)             == 0 ||
     gtk_builder_add_from_file(builder_about_info, "../ui/about-info.ui", &error) == 0 ||
     gtk_builder_add_from_file(builder_popup, "../ui/popup.ui", &error)           == 0
     ) {
    g_printerr(ERR_TEXT_PUTS"Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(EXIT_FAILURE);
  }

  /* Declare a pointer for each Gtk object */
  /* Windows */
  window = gtk_builder_get_object(builder_main, "window");
  window_headerbar_grid_always_buttonbox_button_select = gtk_builder_get_object(builder_main, "window_headerbar_grid_always_buttonbox_button_select");
  window_headerbar_grid_always_buttobox_button_create = gtk_builder_get_object(builder_main, "window_headerbar_grid_always_buttobox_button_create");
  window_headerbar_grid_stack_1_buttonbox_cancel = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox_cancel");
  window_headerbar_grid_stack_1_buttonbox_save = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox_save");
  window_headerbar_grid_stack_1_buttonbox_set_as_default = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox_set_as_default");
  mainmenu_buttonmenu_select_configuration_file = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_select_configuration_file");
  mainmenu_buttonmenu_create_configuration_file = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_create_configuration_file");
  mainmenu_buttonmenu_convert_to_animated_images = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_convert_to_animated_images");
  mainmenu_buttonmenu_clear_history = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_clear_history");
  mainmenu_buttonmenu_about_info = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_about_info");
  body_workbench_stack = gtk_builder_get_object(builder_main, "body_workbench_stack");
  workbench_config_paned = gtk_builder_get_object(builder_main, "workbench_config_paned");
  workbench_home_stack = gtk_builder_get_object(builder_main, "workbench_home_stack");
  workbench_home_stack_empty_history = gtk_builder_get_object(builder_main, "workbench_home_stack_empty_history");
  workbench_home_stack_has_history = gtk_builder_get_object(builder_main, "workbench_home_stack_has_history");
  popup_about_info = gtk_builder_get_object(builder_about_info, "popup_about_info");
  /* Popups */
  on_config_cancel_dialog = gtk_builder_get_object(builder_popup, "on_config_cancel_dialog");
  on_config_cancel_dialog_button_yes = gtk_builder_get_object(builder_popup, "on_config_cancel_dialog_button_yes");
  on_config_cancel_dialog_button_no = gtk_builder_get_object(builder_popup, "on_config_cancel_dialog_button_no");
  popup_error = gtk_builder_get_object(builder_popup, "popup_error");
  popup_error_button_ok = gtk_builder_get_object(builder_popup, "popup_error_button_ok");

  /* Connect signal handlers to the constructed widgets */
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window_headerbar_grid_always_buttonbox_button_select, "clicked", G_CALLBACK(on_select_configuration_file), window);
  g_signal_connect(window_headerbar_grid_always_buttobox_button_create, "clicked", G_CALLBACK(on_create_configuration_file), window);

  g_signal_connect(window_headerbar_grid_stack_1_buttonbox_cancel, "clicked", G_CALLBACK(on_config_cancel), window);
  g_signal_connect(window_headerbar_grid_stack_1_buttonbox_save, "clicked", G_CALLBACK(on_config_save), NULL);
  g_signal_connect(window_headerbar_grid_stack_1_buttonbox_set_as_default, "clicked", G_CALLBACK(on_config_set_as_default), NULL);

  g_signal_connect(mainmenu_buttonmenu_select_configuration_file, "clicked", G_CALLBACK(on_select_configuration_file), window);
  g_signal_connect(mainmenu_buttonmenu_create_configuration_file, "clicked", G_CALLBACK(on_create_configuration_file), window);
  g_signal_connect(mainmenu_buttonmenu_convert_to_animated_images, "clicked", G_CALLBACK(on_convert_images), window);
  g_signal_connect(mainmenu_buttonmenu_clear_history, "clicked", G_CALLBACK(on_clear_history), NULL);
  g_signal_connect(mainmenu_buttonmenu_about_info, "clicked", G_CALLBACK(on_about_info), popup_about_info);
  g_signal_connect(popup_about_info, "response", G_CALLBACK(close_about_dialog), NULL);

  /* Give response IDs */
  /* config cancel dialog buttons */
  gtk_dialog_add_action_widget(GTK_DIALOG(on_config_cancel_dialog), GTK_WIDGET(on_config_cancel_dialog_button_yes), GTK_RESPONSE_YES);
  gtk_dialog_add_action_widget(GTK_DIALOG(on_config_cancel_dialog), GTK_WIDGET(on_config_cancel_dialog_button_no), GTK_RESPONSE_NO);
  /* error button */
  gtk_dialog_add_action_widget(GTK_DIALOG(popup_error), GTK_WIDGET(popup_error_button_ok), GTK_RESPONSE_OK);

  /* Do all miscellaneous things for initial setup */
  gtk_header_bar_set_title(GTK_HEADER_BAR(gtk_builder_get_object(builder_main, "window_headerbar")), "XAWP-gui");
  gtk_window_set_transient_for(GTK_WINDOW(popup_about_info), GTK_WINDOW(window));
  gtk_window_set_transient_for(GTK_WINDOW(on_config_cancel_dialog), GTK_WINDOW(window));
  formatPath(DEFAULT_CONFIG_PATH, default_config_path);
  history_init(&history, HISTORY_DEFAULT_PATH);

  /* Now run the program */
  gtk_main();
}

static GtkFileFilter *get_xawp_file_filter() {
  /* Add 'conf', 'cfg' and 'config' extensions filter and return it */
  GtkFileFilter *filter = gtk_file_filter_new();

  gtk_file_filter_add_pattern(filter, "*.conf");
  gtk_file_filter_add_pattern(filter, "*.cfg");
  gtk_file_filter_add_pattern(filter, "*.config");

  gtk_file_filter_set_name(filter, "XAWP files");

  return filter;
}

static void on_select_configuration_file(GtkWidget *widget, gpointer data) {

  GObject *window = data;
  GtkFileChooserNative *nativeChooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  nativeChooser = gtk_file_chooser_native_new("Open File", GTK_WINDOW(window), action, "_Open", "_Cancel");

  verifyDirPath(default_config_path);

  /* Set the default directory it should open by default */
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(nativeChooser), default_config_path);

  /* Add 'XAWP files' filter option by default */
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(nativeChooser), get_xawp_file_filter());

  /* Add 'All files' filter option */
  GtkFileFilter *all_files_filter = gtk_file_filter_new();
  gtk_file_filter_add_pattern(all_files_filter, "*");
  gtk_file_filter_set_name(all_files_filter, "All files");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(nativeChooser), all_files_filter);

  res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(nativeChooser));
  if(res == GTK_RESPONSE_ACCEPT) {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(nativeChooser);
    filename = gtk_file_chooser_get_filename(chooser);
    verifyDirPath(default_config_path);

    g_free(filename);
  }

  g_object_unref(nativeChooser);

//TODO
}

static void on_create_configuration_file(GtkWidget *widget, gpointer data) {

  GObject *window = data;
  GtkFileChooserNative *nativeChooser;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  nativeChooser = gtk_file_chooser_native_new("Save File", GTK_WINDOW(window), action, "_Create", "_Cancel");
  chooser = GTK_FILE_CHOOSER(nativeChooser);

  verifyDirPath(default_config_path);

  /* Set the default directory it should open by default */
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(nativeChooser), default_config_path);

  /* Display overwrite user confirmation when choosing an already existing file */
  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

  /* Set the default extension for the file to .conf and put the cursor at the first character */
  gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(chooser), ".conf");

  res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(nativeChooser));
  if(res == GTK_RESPONSE_ACCEPT) {
    char *filename;

    filename = gtk_file_chooser_get_filename(chooser);
    /* TODO: use this info for the next function call(s) to create a config file */
    g_free(filename);
  }

  g_object_unref(nativeChooser);

//TODO
}

static void on_config_cancel(GtkWidget *widget, gpointer data) {
  /* If the respone ID is YES, return to home, else continue to edit the config */
  gint response = gtk_dialog_run(GTK_DIALOG(widget));
  if(response == GTK_RESPONSE_YES) {
    // TODO: switch to home
  }
  gtk_widget_destroy(widget);
//TODO
}

static void on_config_save(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_config_set_as_default(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_convert_images(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_clear_history(GtkWidget *widget, gpointer data) {

//TODO
}

static void on_about_info(GtkWidget *widget, gpointer data) {
  /* Run the about info dialog */
  gtk_dialog_run(GTK_DIALOG(data));
}

static void close_about_dialog(GtkAboutDialog *popup_about_info, gint response_id, gpointer data) {
  /* Hide the about info dialog when user closes it */
  gtk_widget_hide(GTK_WIDGET(popup_about_info));
}
