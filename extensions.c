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

#include "extensions.h"

#include <stdio.h>

const char *EXTENSIONS[] =
{
    ".c",
    ".cpp",
    ".cxx",
    ".cc",
    ".h",
    ".hpp",
    ".rb",
    ".py",
    ".sh",
    ".cs",
    ".java"
};

Comment_style get_style_for_extension(Extension extension)
{
    switch (extension)
    {
        case C:
        case H:
        case JAVA:
        return SLASH_STAR;
        
        case CPP:
        case CXX:
        case CC:
        case HPP:
        case CS:
        return SLASH_SLASH;
        
        case RB:
        case PY:
        case SH:
        return POUND;
        
        default:
        return NOT_A_STYLE;
    }
}
