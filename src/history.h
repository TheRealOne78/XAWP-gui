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

typedef struct XawpHistory {
  /* The cache file */
  char *historyFilePath;

  /* Number of elements in the linked list */
  uint64_t elementsCount;

  /* Path data */
  char *confFilePath;
  /* pointer to next node */
  struct XawpHistory *next;
} XawpHistory_t;

/* Getters and setters */
int history_set_list(XawpHistory_t *history, char *configPath);
int history_get_list(char *dest, XawpHistory_t *history, uint8_t index);

/* Clear history functions */
int history_clear_all(XawpHistory_t *history);
int history_clear_element(XawpHistory_t *history, uint8_t index);

#endif
