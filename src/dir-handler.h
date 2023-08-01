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

#ifndef __DIR_CHECKER_H__
# define __DIR_CHECKER_H__


/* ==DEFINE== */

/* Get the maximum path size based of
 * different operating systems. */
#ifndef PATH_MAX
  #ifdef __linux__
    #include <linux/limits.h>
  #elif BSD
    #include <limits.h>
  #elif __APPLE__
    #include <limits.h>
  #endif /* __linux__ */
#endif /* PATH_MAX */


/* ==FUNCTIONS== */

/*
 * This function checks if the first character is a '~'.
 * If so, this function will replace the '~' with a propper
 * "/home/user/" path.
 *
 * Thanks to OpenAI's ChatGPT for all the help!
 */
void formatPath(
    char *path,                    /* Path to be formatted */
    char formattedPath[PATH_MAX]); /* Formatted path */

/*
 * This function checks and creates directories for the
 * taget directory through an iteration, like `mkdir -p`
 * does.
 *
 * Thanks to OpenAI's ChatGPT for all the help!
 */
void verifyDirPath(
    char path[PATH_MAX]);          /* Path to check and create directory */


#endif /* __DIR_CHECKER_H__ */
