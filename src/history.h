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

#ifndef __HISTORY_H__
# define __HISTORY_H__

/* ==DEFINE== */

#ifndef HISTORY_MAX
# define HISTORY_MAX 50
#endif

#ifndef HISTORY_DEFAULT_PATH
# define HISTORY_DEFAULT_PATH "~/.cache/xawp/history.txt"
#endif


/* ==STRUCTS== */

/*
 * XawpHistoryLinkedList_t
 * Contains the linked list of config paths
 */
typedef struct XawpHistoryLinkedList {
  /* Path data */
  char confFilePath[PATH_MAX];
  /* pointer to next node */
  struct XawpHistoryLinkedList *next;
} XawpHistoryLinkedList_t;

/*
 * XawpHistory_t
 * Contains the XawpHistoryLinkedList linked list and indexing variables
 */
typedef struct XawpHistory {
  /* The cache file */
  char cacheFilePath[PATH_MAX];

  /* Number of elements in the linked list */
  uint64_t configsCount;

  /* Head of linked list */
  XawpHistoryLinkedList_t *head;

  /* Last item pointer */
  XawpHistoryLinkedList_t *lastPtr;
} XawpHistory_t;


/* ==FUNCTIONS== */

/*
 * This init function initiates everything necessary into XawpHistory_t like
 * loading the config paths from the cache file into the linked list.
 */
int history_init(
    XawpHistory_t *history,  /* History structure to save on */
    char *cacheFilePath);    /* History file to read from */

/*
 * This function refreshes the linked list from the struct to an updated list
 * of config paths.
 */
int history_refresh(
    XawpHistory_t *history); /* History structure to refresh */

/*
 * This unreference functions makes sure every byte from the passed struct is
 * deallocated. Mostly used when cleaning up before exiting.
 */
int history_unref(
    XawpHistory_t *history); /* History structure to deallocate */


/* Getters and setters */

/*
 * This setter function sets a new path at the begining of a XawpHistory_t
 * type linked list and it's cache file.
 */
int history_set_list(
    XawpHistory_t *history,  /* History structure to set value */
    char *configPath);       /* Path value to set */

/* This getter function gets a path at a specific index of a XawpHistory_t
 * type linked list and it's cache file.
 */
int history_get_list(
    char dest[PATH_MAX],     /* Destination string array */
    XawpHistory_t *history,  /* History structure to get element from */
    uint8_t index);          /* Index to set element */


/* Clear history functions */

/*
 * This setter function clears a specific path value at a specific index of a
 * XawpHistory_t type linked list and it's text element inside cache file.
 */
int history_clear_element(
    XawpHistory_t *history,  /* History structure to clear */
    uint8_t index);          /* Index to clear element */

/* This function clears all the path values inside a XawpHistory_t type
 * linked list and the text inside it's cache file.
 */
int history_clear_all(
    XawpHistory_t *history); /* History structure to clear */


#endif
