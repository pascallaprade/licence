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

#include "comments.h"

const char *COMMENTS[][NUMBER_OF_TYPES] =
{
    {
        "/* ",
        " * ",
        " */"
    },
    {
        "// ",
        "// ",
        "// "
    },
    {
        "# ",
        "# ",
        "# "
    },
    {
        "; ",
        "; ",
        "; "
    },
    {
        ";; ",
        ";; ",
        ";; "
    },
    {
        ";;; ",
        ";;; ",
        ";;; "
    },
    {
        ";;;; ",
        ";;;; ",
        ";;;; "
    }
};
