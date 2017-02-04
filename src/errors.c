/* licence : a tool for prepending a license to files of a project.
 * Copyright (C) 2016  Pascal Laprade <laprade.p@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "errors.h"

#include <stdio.h>
#include <string.h>

/** Displays an error message in case of missing args. */
void error_not_enough_args()
{
    fprintf(stderr, "Usage: licence -l <LICENCE> [-o] <FILE>...\n");
}

/** Displays an error message in case of a missing licence arg. */
void error_missing_license()
{
    fprintf(stderr, "No license provided.\n");
}

/** Displays an error message in case of a missing output arg. */
void error_missing_output()
{
    fprintf(stderr, "No output file.\n");
    error_not_enough_args();
}

/** Displays an error message if the licence given is not managed. */
void error_not_a_license(const char *string)
{
    fprintf(stderr,
        "%s is not included in the present version.\n"
        "Please write to <laprade.p@gmail.com> if you wish to include it.\n",
        string
    );
}

/** Displays an error message if a file could not be opened. */
void error_null_file(const char *string)
{
    fprintf(stderr,
        "%s could not be opened or created.\n",
        string
    );
}

/** Displays a warning if the user attempts uses the unimplemented -c option. */
void error_comment_option()
{
    fprintf(stderr,
        "The -c option is not yet implemented.\n"
        "Defaulting to automatic detection.\n");
}
