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

#ifndef __XAWP_GUI_H__
# define __XAWP_GUI_H__

#ifndef DEFAULT_CONFIG_PATH
# define DEFAULT_CONFIG_PATH "~/.config/xawp/"
#endif

struct stacks {
  /* == Stacks and their childs == */
  GObject *window;
  /* Headerbar's stack */
  GObject *window_headerbar_grid_stack; /* (GtkStack) */
  GObject *window_headerbar_grid_stack_0_grid; /* (GtkGrid) - child of headerbar stack */
  GObject *window_headerbar_grid_stack_1_buttonbox; /* (GtkButtonBox) - child of headerbar stack */
  GObject *window_headerbar_grid_stack_2_buttonbox; /* (GtkButtonBox) - child of headerbar stack */
  /* Body's workbench stack */
  GObject *body_workbench_stack; /* (GtkStack) */
  GObject *workbench_config_paned; /* (GtkPaned) - child of workbench stack */
  GObject *workbench_convert_paned; /* (GtkPaned) - child of workbench stack */
  /* Workbench's home stack */
  GObject *workbench_home_stack; /* (GtkStack) - child of workbench stack */
  GObject *workbench_home_stack_empty_history; /* (GtkLabel) - child of home stack */
  GObject *workbench_home_stack_has_history; /* (GtkFixed) - child of home stack */
};

struct on_about_info_struct {
  GObject *statusbar;
  GObject *popup;
};

/* Activate Gtk */
static void activate();

/* File chooser's file filter */
static GtkFileFilter *get_xawp_file_filter();

/* Callback functions Gtk signals will run */
static void on_select_configuration_file(GtkWidget *widget, gpointer data);
static void on_create_configuration_file(GtkWidget *widget, gpointer data);
static void on_cancel(GtkWidget *widget, gpointer data);
static void on_config_save(GtkWidget *widget, gpointer data);
static void on_config_set_as_default(GtkWidget *widget, gpointer data);
static void on_convert_images(GtkWidget *widget, gpointer data);
static void on_clear_history(GtkWidget *widget, gpointer data);
static void on_about_info(GtkWidget *widget, gpointer data);

# endif
