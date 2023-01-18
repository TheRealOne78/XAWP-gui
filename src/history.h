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

#ifndef HISTORY_MAX
# define HISTORY_MAX 50
#endif

#ifndef HISTORY_DEFAULT_PATH
# define HISTORY_DEFAULT_PATH "~/.cache/xawp/history.txt"
#endif

typedef struct XawpHistoryLinkedList {
  /* Path data */
  char confFilePath[PATH_MAX];
  /* pointer to next node */
  struct XawpHistoryLinkedList *next;
} XawpHistoryLinkedList_t;

typedef struct XawpHistory {
  /* The cache file */
  char cacheFilePath[PATH_MAX];

  /* Number of elements in the linked list */
  uint64_t configsCount;

  XawpHistoryLinkedList_t *head;
} XawpHistory_t;

int history_init(XawpHistory_t *history, char *cacheFilePath);
int history_refresh(XawpHistory_t *history);
int history_unref(XawpHistory_t *history);

/* Getters and setters */
int history_set_list(XawpHistory_t *history, char *configPath);
int history_get_list(char dest[PATH_MAX], XawpHistory_t *history, uint8_t index);

/* Clear history functions */
int history_clear_element(XawpHistory_t *history, uint8_t index);
int history_clear_all(XawpHistory_t *history);

#endif
