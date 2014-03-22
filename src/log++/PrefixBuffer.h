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

#ifndef _PREFIX_BUFFER_H_
#define _PREFIX_BUFFER_H_

#include <streambuf>
#include <ios>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include <log++/PrefixString.h>

namespace std {

/**
 * Class used to change default stream buffer of standard ios
 */
class PrefixBuffer : public std::streambuf
{
public:
	PrefixBuffer(std::streambuf *sb) ;
	PrefixBuffer(std::streambuf *sb, std::shared_ptr<PrefixString> prfx) ;
	~PrefixBuffer() ;

	friend class OPrefixStream ;
protected:
	int overflow(int) ;
	int sync() ;

	std::unique_ptr<std::streambuf> buff ; 	// the actual streambuf used to read and write chars
	std::shared_ptr<PrefixString> prefix ;
	bool active ;

	std::vector<char> cache ;	//cache used for consistent console write
	bool newline ; 			//remember whether we are at a new line
	std::mutex mutex ;
	static std::mutex global_mutex ;
} ;

} // End namespace

#endif
