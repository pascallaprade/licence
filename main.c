/* licence : a tool for prepending a licence to files of a project.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comments.h"
#include "errors.h"
#include "extensions.h"
#include "licences.h"

#ifdef __win32
#define NEW_LINE "\r\n"
#else
#define NEW_LINE "\n"
#endif

/** The possible options from the argv. */
typedef enum Option
{
    LICENCE,
    OUTPUT,
    COMMENT
} Option;

const char OPTIONS[] =
{
    'l',
    'o',
    'c'
};

/** Prototypes. */
char get_opt(char *string);
Licence_id get_licence_id_from_string(const char *string);
Comment_style get_comment_style(const char *filename);

int prepend_to_file(const char *filename, const char *string,
    Comment_style style);

/** The main entry point. */
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        error_not_enough_args();
        
        return 1;
    }
    
    char *output = NULL;
    
    Licence_id id = NOT_A_LICENCE;
    
    Comment_style style = NOT_A_STYLE;
    
    for (int i = 1; i < argc; i++)
    {
        char opt = get_opt(argv[i]);
        
        if (opt == OPTIONS[LICENCE])
        {
            if (argc >= (i + 1))
            {
                const char *licence = argv[i + 1];
                
                if (licence != NULL)
                {
                    id = get_licence_id_from_string(licence);
                    
                    if (id == NOT_A_LICENCE)
                    {
                        error_not_a_licence(licence);
                        
                        return 1;
                    }
                }
                else
                {
                    // TODO(pascal): Write error message.
                    
                    return 1;
                }
            }
        }
        else if (opt == OPTIONS[COMMENT])
        {
            /* We don't manage this option for now,
               but we need only to parse the comment-style name. */
            error_comment_option();
        }
        else if (opt == OPTIONS[OUTPUT] || opt == ' ')
        {
            output = argv[i];
        }
    }
    
    /* We should know the licence and the output file by now,
       if not, there is a problem! */
    
    if (id == NOT_A_LICENCE)
    {
        error_missing_licence();
        
        return 1;
    }
    
    if (output == NULL)
    {
        error_missing_output();
        
        return 1;
    }
    
    if (style == NOT_A_STYLE)
    {
        style = get_comment_style(output);
    }
    
    /* And we can execute! */
    return prepend_to_file(output, LICENCES[id], style);
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
            string[1] == 'c')
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

/** Parses a string in order to find a matching licence */
Licence_id get_licence_id_from_string(const char *string)
{
    for (int i = 0; i < NUMBER_OF_LICENCES; i++)
    {
        if (strcmp(LICENCES_NAMES[i], string) == 0)
        {
            return i;
        }
    }
    
    return NOT_A_LICENCE;
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
       comment style. */
    if (index_of_dot <= 0)
    {
        return POUND;
    }
    
    // TODO(pascal): Use an array instead of malloc. Wastes a few bytes,
    // but reduces risks of failure.
    char *extension =
        malloc(((length_of_filename - index_of_dot) * sizeof(*extension)) + 1);
    
    if (extension == NULL)
    {
        error_malloc();
        
        return NOT_A_STYLE;
    }
    
    for (int i = index_of_dot; i < length_of_filename; i++)
    {
        extension[i - index_of_dot] = filename[i];
    }
    
    Comment_style style = NOT_A_STYLE;
    
    for (int i = 0; i < NUMBER_OF_EXTENSIONS; i++)
    {
        if (strcmp(EXTENSIONS[i], extension) == 0)
        {
            style = get_style_for_extension(i);
            
            break;
        }
    }
    
    free(extension);
    extension = NULL;
    
    /* Defaulting to pound style if the file extension is unknown. */
    if (style == NOT_A_STYLE)
    {
        return POUND;
    }
    
    return style;
}

/** Prepends a string to a file.
   Prepends a given string to a file, using a given comment style.
   Returns 1 if an error happened, 0 otherwise. */
int prepend_to_file(const char *filename, const char *string,
    Comment_style style)
{
    const char *temp_file_path = "__temp_cat_licence.tmp";
    
    FILE *temp_file = NULL;
    temp_file = fopen(temp_file_path, "w+");
    
    if (temp_file == NULL)
    {
        error_null_file(temp_file_path);
    }
    
    const int BUFFER_LENGTH = 80;
    
    char buffer[BUFFER_LENGTH];
    
    int buffer_index = 0;
    
    int length_of_string = strlen(string);
    
    fprintf(temp_file, "%s", COMMENTS[style][START]);
    
    for (int i = 0; i < length_of_string; i++)
    {
        if (string[i] == '\n')
        {
            buffer[buffer_index] = '\0';
            
            fprintf(temp_file, "%s%s%s",
                buffer, NEW_LINE, COMMENTS[style][NORMAL]);
            
            buffer_index = 0;
        }
        else if (i == length_of_string - 1)
        {
            buffer[buffer_index] = '\0';
            
            fprintf(temp_file, "%s%s", buffer, NEW_LINE);
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
        fprintf(temp_file, "%s%s", COMMENTS[style][END], NEW_LINE);
    }
    
    fprintf(temp_file, "%s", NEW_LINE);
    
    FILE *out_file = NULL;
    out_file = fopen(filename, "r");
    
    if (out_file == NULL)
    {
        error_null_file(filename);
        
        return 1;
    }
    
    /* Append the out_file to the licence, then switch the files. */
    
    const int TAILLE_BUFFER_LECTURE = 4096;
    char buffer_lecture[TAILLE_BUFFER_LECTURE];
    
    while (!feof(out_file))
    {
        if (fgets(buffer_lecture, TAILLE_BUFFER_LECTURE - 1, out_file) != NULL)
        {
            fprintf(temp_file, "%s", buffer_lecture);
        }
    }
    
    fclose(temp_file);
    fclose(out_file);
    
    remove(filename);
    rename(temp_file_path, filename);
    
    return 0;
}
