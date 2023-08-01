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
#include <libgen.h>

/* XAWP created headers */
#include "info.h"
#include "fancy-text.h"
#include "xawp-gui.h"
#include "dir-handler.h"
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
  /* Construct GtkBuilder instances */
  GtkBuilder *builder_main = gtk_builder_new();
  GtkBuilder *builder_popup = gtk_builder_new();

  /* === builder_main === */
  GObject *window; /* (GtkWindow) */

  /* == Header Bar == */
  /* Header bar select + create buttons */
  GObject *window_headerbar; /* (GtkHeaderBar) */
  GObject *window_headerbar_grid_always_buttonbox_button_select; /* (GtkButton) */
  GObject *window_headerbar_grid_always_buttobox_button_create; /* (GtkButton) */
  /* Header bar stack 1 aka config window */
  GObject *window_headerbar_grid_stack_1_buttonbox_cancel; /* (GtkButton) */
  GObject *window_headerbar_grid_stack_1_buttonbox_save; /* (GtkButton) */
  GObject *window_headerbar_grid_stack_1_buttonbox_set_as_default; /* (GtkButton) */
  /* Header bar stack 2 aka convert window */
  GObject *window_headerbar_grid_stack_2_buttonbox_cancel; /* (GtkButton) */
  GObject *window_headerbar_grid_stack_2_buttonbox_convert; /* (GtkButton) */

  /* == Main menu buttons == */
  GObject *mainmenu_buttonmenu_select_configuration_file; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_create_configuration_file; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_convert_to_animated_images; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_clear_history; /* (GtkModelButton) */
  GObject *mainmenu_buttonmenu_about_info; /* (GtkModelButton) */

  /* == Status bar == */
  GObject *window_grid_bottom_status_bar; /* (GtkStatusBar) */

  /* == Stacks and their childs == */
  /* To add stacks, see ./xawp-gui.h at `struct stacks` */
  struct stacks stacks_w;

  /* === builder_popup === */
  /* About info */
  GObject *popup_about_info; /* (GtkAboutDialog) */
  /* Clear history */
  GObject *on_clear_history_dialog;
  GObject *on_clear_history_vbox_buttonbox;
  GObject *on_clear_history_vbox_buttonbox_button_yes;
  GObject *on_clear_history_vbox_buttonbox_button_no;
  /* Config cancel */
  GObject *popup_cancel;
  GObject *popup_cancel_button_yes;
  GObject *popup_cancel_button_no;
  /* Error */
  GObject *popup_error;
  GObject *popup_error_button_ok;

  /* config */
  config_t *cfg;

  /* Add the UI files to builders and check if they opened correctly, else exit */
  if(gtk_builder_add_from_file(builder_main, "../ui/main.ui", &error)   == 0 ||
     gtk_builder_add_from_file(builder_popup, "../ui/popup.ui", &error) == 0
     ) { /* TODO: Add test ui first and production ui */
    g_printerr(ERR_TEXT_PUTS"Error loading file: %s\n", error->message);
    g_clear_error(&error);
    exit(EXIT_FAILURE);
  }

  /* =Start declaring UI descriptions= */
  /* builder_main */
  window
    = gtk_builder_get_object(builder_main, "window");

  window_headerbar
    = gtk_builder_get_object(builder_main, "window_headerbar");

  window_headerbar_grid_always_buttonbox_button_select
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_always_buttonbox_button_select");

  window_headerbar_grid_always_buttobox_button_create
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_always_buttobox_button_create");

  window_headerbar_grid_stack_1_buttonbox_cancel
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox_cancel");

  window_headerbar_grid_stack_1_buttonbox_save
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox_save");

  window_headerbar_grid_stack_1_buttonbox_set_as_default
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox_set_as_default");

  window_headerbar_grid_stack_2_buttonbox_cancel
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_2_buttonbox_cancel");

  window_headerbar_grid_stack_2_buttonbox_convert
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_2_buttonbox_convert");

  mainmenu_buttonmenu_select_configuration_file
    = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_select_configuration_file");

  mainmenu_buttonmenu_create_configuration_file
    = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_create_configuration_file");

  mainmenu_buttonmenu_convert_to_animated_images
    = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_convert_to_animated_images");

  mainmenu_buttonmenu_clear_history
    = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_clear_history");

  mainmenu_buttonmenu_about_info
    = gtk_builder_get_object(builder_main, "mainmenu_buttonmenu_about_info");

  window_grid_bottom_status_bar
    = gtk_builder_get_object(builder_main, "window_grid_bottom_status_bar");

  stacks_w.window
    = window;

  stacks_w.window_headerbar
    = window_headerbar;

  stacks_w.window_headerbar_grid_stack
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack");

  stacks_w.window_headerbar_grid_stack_0_grid
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_0_grid");

  stacks_w.window_headerbar_grid_stack_1_buttonbox
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_1_buttonbox");

  stacks_w.window_headerbar_grid_stack_2_buttonbox
    = gtk_builder_get_object(builder_main, "window_headerbar_grid_stack_2_buttonbox");

  stacks_w.body_workbench_stack
    = gtk_builder_get_object(builder_main, "body_workbench_stack");

  stacks_w.workbench_config_paned
    = gtk_builder_get_object(builder_main, "workbench_config_paned");

  stacks_w.workbench_convert_paned
    = gtk_builder_get_object(builder_main, "workbench_convert_paned");

  stacks_w.workbench_home_stack
    = gtk_builder_get_object(builder_main, "workbench_home_stack");

  stacks_w.workbench_home_stack_empty_history
    = gtk_builder_get_object(builder_main, "workbench_home_stack_empty_history");

  stacks_w.workbench_home_stack_has_history
    = gtk_builder_get_object(builder_main, "workbench_home_stack_has_history");

  /* builder_popup */
  popup_about_info
    = gtk_builder_get_object(builder_popup, "popup_about_info");

  on_clear_history_dialog
    = gtk_builder_get_object(builder_popup, "on_clear_history_dialog");

  on_clear_history_vbox_buttonbox_button_yes
    = G_OBJECT(gtk_button_new_with_label("Yes"));

  on_clear_history_vbox_buttonbox_button_no
    = G_OBJECT(gtk_button_new_with_label("No"));

  popup_cancel
    = gtk_builder_get_object(builder_popup, "popup_cancel");

  popup_cancel_button_yes
    = G_OBJECT(gtk_button_new_with_label("Yes"));

  popup_cancel_button_no
    = G_OBJECT(gtk_button_new_with_label("No"));

  popup_error
    = gtk_builder_get_object(builder_popup, "popup_error");

  popup_error_button_ok
    = G_OBJECT(gtk_button_new_with_label("Ok"));

  /* Connect signal handlers to the constructed widgets */
  g_signal_connect(
      window,
      "destroy",
      G_CALLBACK(gtk_main_quit),
      NULL);

  g_signal_connect(
      window_headerbar_grid_always_buttonbox_button_select,
      "clicked",
      G_CALLBACK(on_select_configuration_file),
      &stacks_w);

  g_signal_connect(
      window_headerbar_grid_always_buttobox_button_create,
      "clicked",
      G_CALLBACK(on_create_configuration_file),
      &stacks_w);

  struct on_cancel_struct on_cancel_struct_w = {
    .stacks_struct = &stacks_w,
    .popup_cancel_w = popup_cancel
  };
  g_signal_connect(
      window_headerbar_grid_stack_1_buttonbox_cancel,
      "clicked",
      G_CALLBACK(on_cancel),
      &on_cancel_struct_w);

  g_signal_connect(
      window_headerbar_grid_stack_1_buttonbox_save,
      "clicked",
      G_CALLBACK(on_config_save),
      NULL);

  g_signal_connect(
      window_headerbar_grid_stack_1_buttonbox_set_as_default,
      "clicked",
      G_CALLBACK(on_config_set_as_default),
      NULL);

  g_signal_connect(
      window_headerbar_grid_stack_2_buttonbox_cancel,
      "clicked",
      G_CALLBACK(on_cancel),
      &on_cancel_struct_w);

  g_signal_connect(
      mainmenu_buttonmenu_select_configuration_file,
      "clicked",
      G_CALLBACK(on_select_configuration_file),
      &stacks_w);

  g_signal_connect(
      mainmenu_buttonmenu_create_configuration_file,
      "clicked",
      G_CALLBACK(on_create_configuration_file),
      &stacks_w);

  g_signal_connect(
      mainmenu_buttonmenu_convert_to_animated_images,
      "clicked",
      G_CALLBACK(on_convert_images),
      &stacks_w);

  struct on_about_info_struct on_about_info_struct_w = {
    .statusbar = window_grid_bottom_status_bar,
    .popup = on_clear_history_dialog
  };
  g_signal_connect(
      mainmenu_buttonmenu_clear_history,
      "clicked",
      G_CALLBACK(on_clear_history),
      &on_about_info_struct_w);

  g_signal_connect(
      mainmenu_buttonmenu_about_info,
      "clicked",
      G_CALLBACK(on_about_info),
      popup_about_info);


  /* =Give response IDs= */
  /* config cancel dialog buttons */
  gtk_dialog_add_action_widget(
      GTK_DIALOG(on_clear_history_dialog),
      GTK_WIDGET(on_clear_history_vbox_buttonbox_button_yes),
      GTK_RESPONSE_YES);

  gtk_dialog_add_action_widget(
      GTK_DIALOG(on_clear_history_dialog),
      GTK_WIDGET(on_clear_history_vbox_buttonbox_button_no),
      GTK_RESPONSE_NO);

  gtk_dialog_add_action_widget(GTK_DIALOG(popup_cancel),
      GTK_WIDGET(popup_cancel_button_yes),
      GTK_RESPONSE_YES);

  gtk_dialog_add_action_widget(GTK_DIALOG(popup_cancel),
      GTK_WIDGET(popup_cancel_button_no),
      GTK_RESPONSE_NO);

  /* error button */
  gtk_dialog_add_action_widget(GTK_DIALOG(popup_error),
      GTK_WIDGET(popup_error_button_ok),
      GTK_RESPONSE_OK);


  /* Do all miscellaneous things for initial setup */
  gtk_header_bar_set_title(
      GTK_HEADER_BAR(window_headerbar), "XAWP-gui");

  gtk_window_set_transient_for(
      GTK_WINDOW(popup_about_info), GTK_WINDOW(window));

  gtk_window_set_transient_for(
      GTK_WINDOW(on_clear_history_dialog), GTK_WINDOW(window));

  gtk_window_set_transient_for(
      GTK_WINDOW(popup_cancel), GTK_WINDOW(window));

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
  struct stacks *stacks_w = (struct stacks* )data;

  GObject *window = stacks_w->window;
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

    gtk_header_bar_set_subtitle(
        GTK_HEADER_BAR(stacks_w->window_headerbar),
        basename(filename));

    gtk_stack_set_visible_child(
        GTK_STACK(stacks_w->body_workbench_stack),
        GTK_WIDGET(stacks_w->workbench_config_paned));

    gtk_stack_set_visible_child(
        GTK_STACK(stacks_w->window_headerbar_grid_stack),
        GTK_WIDGET(stacks_w->window_headerbar_grid_stack_1_buttonbox));

    g_free(filename);
  }

  g_object_unref(nativeChooser);

//TODO
}

static void on_create_configuration_file(GtkWidget *widget, gpointer data) {
  struct stacks *stacks_w = (struct stacks* )data;

  GObject *window = stacks_w->window;
  GtkFileChooserNative *nativeChooser;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  nativeChooser = gtk_file_chooser_native_new(
      "Save File",
      GTK_WINDOW(window),
      action,
      "_Create",
      "_Cancel");

  chooser = GTK_FILE_CHOOSER(nativeChooser);

  verifyDirPath(default_config_path);

  /* Set the default directory it should open by default */
  gtk_file_chooser_set_current_folder(
      GTK_FILE_CHOOSER(nativeChooser),
      default_config_path);

  /* Display overwrite user confirmation when choosing an already existing file */
  gtk_file_chooser_set_do_overwrite_confirmation(
      chooser,
      TRUE);

  /* Set the default extension for the file to .conf and put the cursor at the first character */
  gtk_file_chooser_set_current_name(
      GTK_FILE_CHOOSER(chooser),
      ".conf");

  res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(nativeChooser));

  if(res == GTK_RESPONSE_ACCEPT) {
    char *filename;

    filename = gtk_file_chooser_get_filename(chooser);

    /* TODO: use this info for the next function call(s) to create a config file */
    gtk_header_bar_set_subtitle(
        GTK_HEADER_BAR(stacks_w->window_headerbar),
        basename(filename));

    gtk_stack_set_visible_child(
        GTK_STACK(stacks_w->body_workbench_stack),
        GTK_WIDGET(stacks_w->workbench_config_paned));

    gtk_stack_set_visible_child(
        GTK_STACK(stacks_w->window_headerbar_grid_stack),
        GTK_WIDGET(stacks_w->window_headerbar_grid_stack_1_buttonbox));

    g_free(filename);
  }

  g_object_unref(nativeChooser);

//TODO
}

static void on_cancel(GtkWidget *widget, gpointer data) {

  struct on_cancel_struct *on_cancel_struct_w =
    (struct on_cancel_struct* )data;

  /*
   * If the respone ID is YES, return to home, else continue to edit the config
   *
   * TODO: pass the actual popup
   */
  gtk_widget_show_all(GTK_WIDGET(on_cancel_struct_w->popup_cancel_w));

  gint response = gtk_dialog_run(GTK_DIALOG(on_cancel_struct_w->popup_cancel_w));
  if(response == GTK_RESPONSE_YES) {
    gtk_header_bar_set_subtitle(
        GTK_HEADER_BAR(on_cancel_struct_w->stacks_struct->window_headerbar),
        "");

    gtk_stack_set_visible_child(
        GTK_STACK(on_cancel_struct_w->stacks_struct->body_workbench_stack),
        GTK_WIDGET(on_cancel_struct_w->stacks_struct->workbench_home_stack));

    gtk_stack_set_visible_child(
        GTK_STACK(on_cancel_struct_w->stacks_struct->window_headerbar_grid_stack),
        GTK_WIDGET(on_cancel_struct_w->stacks_struct->window_headerbar_grid_stack_0_grid));
  }

  gtk_widget_hide(GTK_WIDGET(on_cancel_struct_w->popup_cancel_w));
}

static void on_config_save(GtkWidget *widget, gpointer data) {
  struct stacks *stacks_w = (struct stacks* )data;


//TODO
}

static void on_config_set_as_default(GtkWidget *widget, gpointer data) {
  struct stacks *stacks_w = (struct stacks* )data;

//TODO
}

static void on_convert_images(GtkWidget *widget, gpointer data) {
  struct stacks *stacks_w = (struct stacks* )data;

  gtk_stack_set_visible_child(GTK_STACK(stacks_w->body_workbench_stack), GTK_WIDGET(stacks_w->workbench_convert_paned));
  gtk_stack_set_visible_child(GTK_STACK(stacks_w->window_headerbar_grid_stack), GTK_WIDGET(stacks_w->window_headerbar_grid_stack_2_buttonbox));
//TODO
}

static void on_clear_history(GtkWidget *widget, gpointer data) {
  struct on_about_info_struct *widgets = (struct on_about_info_struct* )data;

  gtk_widget_show_all(GTK_WIDGET(widgets->popup));
  gint result = gtk_dialog_run(GTK_DIALOG(widgets->popup));
  if(result == GTK_RESPONSE_YES) {
    guint context_id;
    history_clear_all(&history);
    gtk_statusbar_push(GTK_STATUSBAR(widgets->statusbar), context_id, "History cleared");
  }
  else if(result == GTK_RESPONSE_NO) { }
  gtk_widget_hide(GTK_WIDGET(widgets->popup));
}

static void on_about_info(GtkWidget *widget, gpointer data) {
  /* Run the about info dialog */
  gtk_widget_show_all(GTK_WIDGET(data));
  gint respone = gtk_dialog_run(GTK_DIALOG(data));
  gtk_widget_hide(GTK_WIDGET(data));
}
