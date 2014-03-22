/**
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
MA 02110-1301, USA.
*/

#ifndef LOG_IOMANIP_HPP_
#define LOG_IOMANIP_HPP_

#include <bits/c++config.h>
#include <iosfwd>
#include <bits/ios_base.h>

#if __cplusplus >= 201103L
#include <locale>
#endif

namespace std {


	struct _SetFile
	{
		std::string file ;
		int line ;
		int col ;
	} ;

	/**
	*  Sent to a log stream object, this manipulator sets the current file name
	*  @param  file  The file name.
	*  @param  line  The file line.
	*  @param  col  The file column.
	*/
	inline _SetFile setfile(std::string file, int line=-1, int col=-1)
	{
		return { file, line, col } ;
	}

}

#endif /* IOMANIP_HPP_ */
