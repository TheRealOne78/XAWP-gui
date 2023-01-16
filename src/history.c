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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>

#include "fancy-text.h"
#include "dir-handler.h"
#include "history.h"

int history_init(XawpHistory_t *history, char *cacheFilePath) {

  /* This init function initiates everything necessary into XawpHistory_t like
   * loading the config paths from the cache file into the linked list. */

  /* Check if the path is correct and if it's not, fix it */
  char historyDefaultPath[PATH_MAX];
  char historyDefaultDirPath[PATH_MAX];
  formatPath(cacheFilePath, historyDefaultPath);
  strcpy(historyDefaultDirPath, historyDefaultPath);
  verifyDirPath(dirname(historyDefaultDirPath));

  /* Copy the location of the cache file directly to the struct */
  strcpy(history->cacheFilePath, historyDefaultPath);

  /* Since there are no configs yet, assign value 0 */
  history->configsCount = 0;

  FILE *cacheFile = fopen(history->cacheFilePath , "r");

  /* If there is no file, create one and return */
  if(cacheFile == NULL) {
    FILE *cacheFileWrite = fopen(history->cacheFilePath , "w+");
    if(cacheFileWrite == NULL) {
      int tmperror = errno;
      fprintf(stderr, ERR_TEXT_PUTS"Error creating or opening the file %s\n", history->cacheFilePath);
      return tmperror;
    }

    if(fclose(cacheFileWrite) != 0) {
      return errno;
    }

    /* Just created a new cache file, so returning since there is no real
     * meaning to continue loading configs from an empty file */
    return 0;
  }

  /* Now load every config from the cache file into the linked list */
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  XawpHistoryLinkedList_t *temp;
  while((read = getline(&line, &len, cacheFile)) != -1) {

    temp = (XawpHistoryLinkedList_t* )malloc(sizeof(XawpHistoryLinkedList_t));
    temp->next = NULL;

    strcpy(temp->confFilePath, line);

    if(history->head != NULL)
      temp->next = history->head;

    history->head = temp;

    if(++history->configsCount >= 50) {
      // TODO: If more than 50, start removing older configs from cache
      break;
    }
  }

  if(fclose(cacheFile) != 0) {
    return errno;
  }

  return 0;
}

int history_refresh(XawpHistory_t *history) {

  /* This function refreshes the linked list from the struct to an updated list
   * of config paths. */

  /* Store the old path */
  char historyDefaultPath[PATH_MAX];
  strcpy(historyDefaultPath, history->cacheFilePath);

  /* Clear everything from history */
  history_unref(history);

  /* Reload files into history */
  history_init(history, historyDefaultPath);

  /* Copy the old path back */
  strcpy(history->cacheFilePath, historyDefaultPath);

  return 0;
}

int history_unref(XawpHistory_t *history) {

  /* This unreference functions makes sure every byte from the passed struct is
   * dealocated. Mostly used when cleaning up before exiting. */

  /* NULL every char of history->cacheFilePath string */
  memset(history->cacheFilePath, '\0', (sizeof(history->cacheFilePath) * PATH_MAX));

  /* Reset the image count */
  history->configsCount = 0;

  XawpHistoryLinkedList_t *temp;
  XawpHistoryLinkedList_t *temp2;

  temp = history->head;

  /* Free memory until it finds a NULL 'next' pointer. */
  while(temp->next != NULL) {
    temp = temp->next;
    temp2 = temp->next;
    free(temp);
    temp = temp2;
  }
  history->head = NULL;

  return 0;
}

int history_set_list(XawpHistory_t *history, char *configPath) {

  /* This setter function sets a new path at the begining of a XawpHistory_t
   * type linked list and it's cache file. */

//TODO
}

int history_get_list(char *dest, XawpHistory_t *history, uint8_t index) {

  /* This getter function gets a path at a specific index of a XawpHistory_t
   * type linked list and it's cache file. */

//TODO
}

int history_clear_element(XawpHistory_t *history, uint8_t index) {

  /* This setter function clears a specific path value at a specific index of a
   * XawpHistory_t type linked list and it's text element inside cache file. */

//TODO
}

int history_clear_all(XawpHistory_t *history) {

  /* This function clears all the path values inside a XawpHistory_t type
   * linked list and the text inside it's cache file. */

  /* Delete the cache file from the system */
  FILE *cacheFile = fopen(history->cacheFilePath , "w+");

  if(cacheFile == NULL) {
    int tmperror = errno;
    fprintf(stderr, ERR_TEXT_PUTS"Error creating or opening the file %s\n", history->cacheFilePath);
    return tmperror;
  }

  if(fclose(cacheFile) != 0) {
    return errno;
  }

  /* Free the history struct and it's linked list */
  history_unref(history);

  /* After everything went smoothly, return with 0 */
  return 0;
}
