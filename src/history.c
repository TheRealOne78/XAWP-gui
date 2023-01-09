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

#include "fancy-text.h"
#include "history.h"

int history_set_list(XawpHistory_t *history, char *configPath) {

  /* This setter function sets a new path at the begining of a XawpHistory_t
   * type linked list and it's cache file. */

}

int history_get_list(char *dest, XawpHistory_t *history, uint8_t index) {

  /* This getter function gets a path at a specific index of a XawpHistory_t
   * type linked list and it's cache file. */

}

int history_clear_all(XawpHistory_t *history) {

  /* This function clears all the path values inside a XawpHistory_t type
   * linked list and the text inside it's cache file. */

}

int history_clear_element(XawpHistory_t *history, uint8_t index) {

  /* This setter function clears a specific path value at a specific index of a
   * XawpHistory_t type linked list and it's text element inside cache file. */

}
