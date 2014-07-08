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

#ifndef _OPREFIXFILESTREAM_H_
#define _OPREFIXFILESTREAM_H_

#include <log++/stream/OStream.h>
#include <log++/buffer/PrefixFileBuffer.h>

namespace std {

class OPrefixFileStream : public std::OStream
{
public:
	OPrefixFileStream() ;
	OPrefixFileStream(std::shared_ptr<PrefixString> prfx) ;
	OPrefixFileStream(std::shared_ptr<PrefixString> prfx, const std::string &basename, const std::string &path=".") ;
	OPrefixFileStream(const std::string &basename, const std::string &path=".") ;

	~OPrefixFileStream();


	std::string getBasename() const ;
	void setBasename(const std::string& value) ;

	std::string getPath() const ;
	void setPath(const std::string& value) ;

	virtual void setActive(bool value) ;
	virtual bool getActive() const ;

	virtual PrefixString* getPrefix() const ;

protected:
	PrefixFileBuffer buff ; 	// the actual streambuf used to read and write chars
} ;

extern OPrefixFileStream& operator<<(OPrefixFileStream&, _SetFile) ;

} //End namespace
#endif /* _PRFXSTREAM_H_ */
