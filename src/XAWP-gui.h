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

/* Activate Gtk */
static void activate(GtkApplication *app, gpointer user_data);

/* Callback functions Gtk signals will run */
static void on_select_configuration_file(GtkWidget *widget, gpointer data);
static void on_create_configuration_file(GtkWidget *widget, gpointer data);
static void on_convert_images(GtkWidget *widget, gpointer data);
static void on_clear_history(GtkWidget *widget, gpointer data);
static void on_about_info(GtkWidget *widget, gpointer data);

# endif
