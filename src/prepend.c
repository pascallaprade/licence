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

#include <stdio.h>
#include <string.h>

#include "prepend.h"
#include "errors.h"
#include "utils.h"

#define BUFFER_LENGTH 4096

/** Prepends a string to files.
    Prepends a given string to a file, using a given comment style.
    Returns 1 if an error happened, 0 otherwise. */
int prepend_to_file(char **files, int files_len, const char *string,
    Comment_style in_style)
{
    for (int i = 0; i < files_len; i++)
    {
        const char *temp_file_path = "__temp_cat_licence.tmp";

        Comment_style style = in_style;
        if (style == NOT_A_STYLE)
        {
            style = get_comment_style(files[i]);
        }

        FILE *temp_file = NULL;
        temp_file = fopen(temp_file_path, "w+");

        if (temp_file == NULL)
        {
            error_null_file(temp_file_path);
        }

        char buffer[BUFFER_LENGTH];

        int buffer_index = 0;

        int length_of_string = strlen(string);

        fprintf(temp_file, "%s", COMMENTS[style][START]);

        for (int i = 0; i < length_of_string + 1; i++)
        {
            if (string[i] == '\n')
            {
                buffer[buffer_index] = '\0';

                fprintf(temp_file, "%s\n%s",
                    buffer, COMMENTS[style][NORMAL]);

                buffer_index = 0;
            }
            else if (i == length_of_string)
            {
                buffer[buffer_index] = '\0';

                fprintf(temp_file, "%s\n", buffer);
            }
            else
            {
                if (buffer_index == BUFFER_LENGTH - 1)
                {
                    buffer[buffer_index] = '\0';

                    fprintf(temp_file, "%s", buffer);

                    buffer_index = 0;
                }

                buffer[buffer_index++] = string[i];
            }
        }

        if (strcmp(COMMENTS[style][NORMAL], COMMENTS[style][END]) != 0)
        {
            fprintf(temp_file, "%s\n", COMMENTS[style][END]);
        }

        fprintf(temp_file, "\n");

        FILE *out_file = NULL;
        out_file = fopen(files[i], "r");

        if (out_file == NULL)
        {
            out_file = fopen(files[i], "w+");

            if (out_file == NULL)
            {
                error_null_file(files[i]);
                return 1;
            }
        }

        /* Append the out_file to the licence, then switch the files. */

        while (!feof(out_file))
        {
            if (fgets(buffer, BUFFER_LENGTH - 1, out_file) != NULL)
            {
                fprintf(temp_file, "%s", buffer);
            }
        }

        fclose(temp_file);
        fclose(out_file);
        temp_file = NULL;
        out_file = NULL;

        remove(files[i]);
        rename(temp_file_path, files[i]);
    }

    return 0;
}
