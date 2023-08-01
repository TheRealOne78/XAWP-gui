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

#ifndef __XAWP_CONF_H__
 #define __XAWP_CONF_H__


/* ==STRUCTURES== */

struct XawpConfValues {
  char version[VERSION_MAX];       /* Version of XAWP-gui */
  char path[PATH_MAX];             /* Image path */
  double time;                     /* Frame pause time */
  char debug[6];                   /* Debug: True/False (bool to string) */
  char static_wallpaper[PATH_MAX]; /* Static wallpaper path */
};


/* ==FUNCTIONS== */

/* Read configs from conf file and save the values into *xawpConfValues */
int XAWP_CONF_ReadConfig(
    struct XawpConfValues *xawpConfValues,  /* Values to save the values */
    char confPath[PATH_MAX]);               /* File to read from */

/* Write the settings into the specified conf file path */
int XAWP_CONF_WriteConfig(
    struct XawpConfValues *xawpConfValues,  /* Values to be written */
    char confPath[PATH_MAX]);               /* File to write */

/* Clear the contents of *xawpConfValues */
void XAWP_CONF_Clear(
    struct XawpConfValues *xawpConfValues); /* Values to clear */


#endif /* __XAWP_CONF_H__ */
