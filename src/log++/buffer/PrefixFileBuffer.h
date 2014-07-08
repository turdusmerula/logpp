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

#ifndef _PRFXFILESBUFFER_H_
#define _PRFXFILESBUFFER_H_

#include <streambuf>
#include <ios>
#include <ostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include <log++/prefix/PrefixString.h>

namespace std {

/**
 * Class used to change default streaming buffer of file
 */
class PrefixFileBuffer : public std::filebuf
{
public:
	PrefixFileBuffer() ;
	PrefixFileBuffer(std::shared_ptr<PrefixString> prfx) ;
	PrefixFileBuffer(std::shared_ptr<PrefixString> prfx, const std::string &basename, const std::string &path) ;
	~PrefixFileBuffer() ;

	friend class OPrefixFileStream ;
protected:
	int overflow(int) ;
	int sync() ;

	void openFile() ;

	std::unique_ptr<std::filebuf> buff ; 	// the actual streambuf used to read and write chars
	std::shared_ptr<PrefixString> prefix ;
	std::vector<char> cache ;	//cache used for consistent console write
	bool newline ; 			//remember whether we are at a new line
	bool active ;
	static std::mutex buffer_mutex ;

	std::string basename ;
	std::string path ;
	size_t maxsize ;	//TODO log rotation
	size_t currsize ;
	bool rotatelog ;
} ;


} //End namespace
#endif /* _PRFXSTREAM_H_ */
