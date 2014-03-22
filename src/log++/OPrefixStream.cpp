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

#include "OPrefixStream.h"
#include "PrefixBuffer.h"

namespace std {


OPrefixStream::OPrefixStream(std::streambuf *sb)
	:	std::OStream(buff=new PrefixBuffer(sb))
{
}

OPrefixStream::OPrefixStream(std::streambuf *sb, std::shared_ptr<PrefixString> prfx)
	:	std::OStream(buff=new PrefixBuffer(sb, prfx))
{
}

OPrefixStream::~OPrefixStream()
{
}

void OPrefixStream::setActive(bool value)
{
	buff->active = value ;
}

bool OPrefixStream::getActive() const
{
	return buff->active ;
}

PrefixString* OPrefixStream::getPrefix() const
{
	return buff->prefix.get() ;
}

OPrefixStream& operator<<(OPrefixStream& stream, _SetFile f)
{
	stream.getPrefix()->setFile(f.file) ;
	stream.getPrefix()->setLine(f.line) ;
	stream.getPrefix()->setCol(f.col) ;
	return stream ;

}


} //End namespace
