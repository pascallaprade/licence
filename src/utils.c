/* licence : a tool for prepending a license to files of a project.
 * Copyright (C) 2017  Pascal Laprade <laprade.p@gmail.com>
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

#include <string.h>

#include "extensions.h"
#include "utils.h"

/** Parses a string in order to find a matching license. */
License_id get_license_id_from_string(const char *string)
{
    int length_of_string = strlen(string);

    for (int lic = 0; lic < NUMBER_OF_LICENSES; lic++)
    {
        /* Including the null character in this string loop */
        for (int i = 0; i < length_of_string + 1; i++)
        {
            /* End of both strings, they are the same. */
            if (string[i] == '\0' && LICENSE_NAMES[lic][i] == '\0')
            {
                return lic;
            }

            /* The given license is longer than the tested known license. */
            if (LICENSE_NAMES[lic][i] == '\0')
            {
                break;
            }

            char capital_char = string[i];

            if (capital_char >= 'a' && capital_char <= 'z')
            {
                capital_char -= ('a' - 'A');
            }

            /* The given license isn't the tested known license. */
            if (capital_char != LICENSE_NAMES[lic][i])
            {
                break;
            }
        }
    }

    return NOT_A_LICENSE;
}

/** Finds a comment style for a given file extension. */
Comment_style get_comment_style(const char *filename)
{
    int length_of_filename = strlen(filename);

    int index_of_dot = length_of_filename;

    for (; index_of_dot >= 0; index_of_dot--)
    {
        if (filename[index_of_dot] == '.')
        {
            break;
        }
    }

    /* If there is no dot in the filename, defaulting to the pound
       comment style, it is probably a script. */
    if (index_of_dot <= 0)
    {
        return POUND;
    }

    for (int ext = 0; ext < NUMBER_OF_EXTENSIONS; ext++)
    {
        const char *extension = filename + index_of_dot;

        if (strcmp(extension, EXTENSIONS[ext]) == 0)
        {
            return get_style_for_extension(ext);
        }
    }

    /* TODO(pascal) : Returning the pound comment-style for now, but it would
       be nice to prompt the user to explicitly define the comment-style
       character(s) instead of enforcing this. */
    return POUND;
}
