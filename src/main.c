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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "prepend.h"
#include "errors.h"
#include "utils.h"

/** The possible options from the argv. */
typedef enum Option
{
    LICENSE,
    OUTPUT,
    COMMENT,
    FULL_LICENSE
} Option;

const char OPTIONS[] =
{
    'l',
    'o',
    'c',
    'f'
};

/** Prototypes. */
char get_opt(char *string);

/** The main entry point. */
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        error_not_enough_args();
        return 1;
    }

    char **output = NULL;
    int output_len = 0;
    int print_full_license = 0;
    char *license_name = NULL;

    for (int i = 1; i < argc; i++)
    {
        char opt = get_opt(argv[i]);

        if (opt == OPTIONS[LICENSE])
        {
            if (argc >= (i + 1))
            {
                license_name = argv[i + 1];
            }
        }
        else if (opt == OPTIONS[COMMENT])
        {
            /* We don't manage this option for now,
               but we need only to parse the comment-style name. */
            error_comment_option();
        }
        else if (opt == OPTIONS[FULL_LICENSE])
        {
            print_full_license = 1;
        }
        else if (output == NULL && (opt == OPTIONS[OUTPUT] || opt == ' '))
        {
            output = (argv + 1) + i;
            output_len = (argc - 1) - i;
        }
    }

    /* We should know the licence and the output file by now,
       if not, there is a problem! */

    License_id id = NOT_A_LICENSE;
    Comment_style style = NOT_A_STYLE;

    if (license_name != NULL)
    {
        id = get_license_id_from_string(license_name);

        if (id == NOT_A_LICENSE)
        {
            error_not_a_license(license_name);
            return 1;
        }
    }
    else
    {
        error_missing_license();
        return 1;
    }

    if (output == NULL)
    {
        error_missing_output();
        return 1;
    }

    const char *license = NULL;

    if (print_full_license)
    {
        license = FULL_LICENSES[id];
        style = NONE;
    }
    else
    {
        license = LICENSES[id];
    }

    /* And we can execute! */
    return prepend_to_file(output, output_len, license, style);
}

/** Finds an option in a given string.
    Always return a value, either the space char,
    the letter of the option present in the string,
    or a hyphen if it is an unknown option. */
char get_opt(char *string)
{
    char opt = ' ';

    if (strlen(string) == 2)
    {
        if (string[1] == 'l' ||
            string[1] == 'o' ||
            string[1] == 'c' ||
            string[1] == 'f')
        {
            opt = string[1];
        }
        else
        {
            /* Unknown option. */
            opt = '-';
        }
    }

    return opt;
}
