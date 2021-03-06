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

#ifndef _OPRFXSTREAM_H_
#define _OPRFXSTREAM_H_

#include <memory>

#include <log++/stream/OStream.h>
#include <log++/prefix/PrefixString.h>

namespace std {

class PrefixBuffer ;


class OPrefixStream : public std::OStream
{
public:
	OPrefixStream(std::streambuf *sb) ;
	OPrefixStream(std::streambuf *sb, std::shared_ptr<PrefixString> prfx) ;

	~OPrefixStream();

	virtual void setActive(bool value) ;
	virtual bool getActive() const ;

	virtual PrefixString* getPrefix() const ;

protected:
	PrefixBuffer *buff ;
} ;

extern OPrefixStream& operator<<(OPrefixStream&, _SetFile) ;


} //End namespace
#endif /* _OPRFXSTREAM_H_ */
