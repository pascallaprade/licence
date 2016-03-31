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

#ifndef __comments_h
#define __comments_h

typedef enum Comment_style
{
	SLASH_STAR,
	SLASH_SLASH,
	POUND,
	NUMBER_OF_STYLES,
	NOT_A_STYLE
} Comment_style;

typedef enum Comment_type
{
	START,
	NORMAL,
	END,
	NUMBER_OF_TYPES
} Comment_type;

extern const char *COMMENTS[][NUMBER_OF_TYPES];

#endif
