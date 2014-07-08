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

#ifndef LOG_OSTREAM_H_
#define LOG_OSTREAM_H_

#include <ostream>
#include <log++/IOManip.h>
#include <log++/prefix/Prefix.h>

namespace std {

class OStream : public std::ostream
{
public:
	OStream() ;
	OStream(std::streambuf *sb) ;

	virtual ~OStream()=0 ;

	virtual void setActive(bool value) { active = value ; }
	virtual bool getActive() const { return active ; }

	virtual Prefix* getPrefix() const { return nullptr ; }

protected:
	bool active ;
} ;

extern OStream& operator<<(OStream&, _SetFile) ;
extern basic_ostream<char>& operator<<(basic_ostream<char>&, _SetFile) ;

} //End namespace
#endif /* LOG_OSTREAM_H_ */
