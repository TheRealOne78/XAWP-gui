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

#include <libconfig.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>

#include "info.h"
#include "fancy-text.h"
#include "dir-handler.h"
#include "xawp-conf.h"


int XAWP_CONF_ReadConfig(struct XawpConfValues *xawpConfValues, char confPath[PATH_MAX]) {

  /*
   * Read configs from conf file and save the values into *xawpConfValues
   */

  config_t cfg;

  /* Check if can be read */
  if(config_read_file(&cfg, confPath) == CONFIG_FALSE) {
    int err = errno;
    fprintf(
        stderr,
        ERR_TEXT_PUTS"%s:%d - %s\n",
        config_error_file(&cfg),
        config_error_line(&cfg),
        config_error_text(&cfg));

    config_destroy(&cfg);
    return CONFIG_FALSE;
  }

  /* Version */
  const char *version;
  if(config_lookup_string(&cfg, "version", &version))
    strcpy(xawpConfValues->version, version);
  else
    xawpConfValues->version[0] = '\0';

  /* Path */
  const char *path;
  if(config_lookup_string(&cfg, "path", &path))
    strcpy(xawpConfValues->path, path);
  else
    xawpConfValues->path[0] = '\0';

  /* Time */
  double time;
  if(config_lookup_float(&cfg, "time", &time))
    xawpConfValues->time = time;
  else
    xawpConfValues->time = -1.d;

  /* Debug */
  int cfgDebug;
  if(config_lookup_bool(&cfg, "debug", &cfgDebug)) {
    if(cfgDebug == 1)
      strcpy(xawpConfValues->debug, "True");
    else
      strcpy(xawpConfValues->debug, "False");
  }
  else
    xawpConfValues->debug[0] = '\0';

  /* Static wallpaper */
  const char *static_wallpaper;
  if(config_lookup_string(&cfg, "static-wallpaper", &static_wallpaper))
    strcpy(xawpConfValues->static_wallpaper, static_wallpaper);
  else
    xawpConfValues->static_wallpaper[0] = '\0';

  /* Destroy the cfg */
  config_destroy(&cfg);

  return 0;
}


int XAWP_CONF_WriteConfig(struct XawpConfValues *xawpConfValues, char confPath[PATH_MAX]) {

  /*
   * Write the settings into the specified conf file path
   */

  /* Open file stream in write mode */
  FILE *fp;
  fp = fopen(confPath, "w");
  if(fp == NULL)
    return errno;

  /*** Save a XAWP configuration with all it's values ***/
  // == HEADER ==

  /* XAWP-gui version */ {
    fprintf(fp, "### %s - generated with XAWP-gui\n", basename(confPath));
    fprintf(fp, "# v%s\n", VERSION);
    fprintf(fp, "#\n");
  }

  /* XAWP ASCII logo */ {
    fprintf(fp, "#  /$$   /$$  /$$$$$$  /$$      /$$ /$$$$$$$\n");
    fprintf(fp, "# | $$  / $$ /$$__  $$| $$  /$ | $$| $$__  $$\n");
    fprintf(fp, "# |  $$/ $$/| $$  \\ $$| $$ /$$$| $$| $$  \\ $$\n");
    fprintf(fp, "#  \\  $$$$/ | $$$$$$$$| $$/$$ $$ $$| $$$$$$$/\n");
    fprintf(fp, "#   >$$  $$ | $$__  $$| $$$$_  $$$$| $$____/\n");
    fprintf(fp, "#  /$$/\\  $$| $$  | $$| $$$/ \\  $$$| $$\n");
    fprintf(fp, "# | $$  \\ $$| $$  | $$| $$/   \\  $$| $$\n");
    fprintf(fp, "# |__/  |__/|__/  |__/|__/     \\__/|__/\n");
    fprintf(fp, "#\n");
  }

  /* More info (wiki) */ {
    fprintf(fp, "# See wiki page for more info:\n");
    fprintf(fp, "# https://github.com/TheRealOne78/XAWP/wiki\n");
    fprintf(fp, "\n");
  }

  // == BODY ==

  /* Version */ {
    fprintf(fp, "### Version\n");
    fprintf(fp, "# Minimal compatible XAWP version string\n");
    fprintf(fp, "version = \"%s\"\n", xawpConfValues->version);
    fprintf(fp, "\n");
  }

  /* Path */ {
    fprintf(fp, "### Path to images directory\n");
    fprintf(fp, "# It needs to contain every frame xawp should display\n");
    fprintf(fp, "path = \"%s\"\n", xawpConfValues->path);
    fprintf(fp, "\n");
  }

  /* Time */ {
    fprintf(fp, "### Time\n");
    fprintf(fp, "# Set time to pause between 2 frames\n");
    fprintf(fp, "time = %lf\n", xawpConfValues->time);
    fprintf(fp, "\n");
  }

  /* Debug */ {
    fprintf(fp, "### Debug\n");
    fprintf(fp, "# If true, debug info will start display\n");
    fprintf(fp, "debug = %s\n", xawpConfValues->debug);
    fprintf(fp, "\n");
  }

  /* Static Image Wallpaper */ {
    fprintf(fp, "### Static Image Wallpaper\n");
    fprintf(fp, "# If uncommented, XAWP will set the wallpaper and exit\n");

    if(xawpConfValues->static_wallpaper[0] = '\0')
      fprintf(fp, "#");

    fprintf(fp, "static-wallpaper = \"%s\"\n", xawpConfValues->static_wallpaper);
  }


  /* Close file stream */
  if(fclose(fp) != 0) {
    return errno;
  }

  return 0;
}


void XAWP_CONF_Clear(struct XawpConfValues *xawpConfValues) {

  /*
   * Clear the contents of *xawpConfValues
   */

  xawpConfValues->version[0]          = '\0';
  xawpConfValues->path[0]             = '\0';
  xawpConfValues->time                = -1.d;
  xawpConfValues->debug[0]            = '\0';
  xawpConfValues->static_wallpaper[0] = '\0';
}
