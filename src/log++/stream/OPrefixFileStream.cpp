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

#include "OPrefixFileStream.h"

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

namespace std {



OPrefixFileStream::OPrefixFileStream()
	:	std::OStream()
{
	this->init(&buff) ;
}

OPrefixFileStream::OPrefixFileStream(std::shared_ptr<PrefixString> prfx)
	:	std::OStream()
{
	buff.prefix = prfx ;
	this->init(&buff) ;
}

OPrefixFileStream::OPrefixFileStream(std::shared_ptr<PrefixString> prfx, const std::string &basename, const std::string &path)
	:	std::OStream()
{
	buff.prefix = prfx ;
	buff.basename = basename ;
	buff.path = path ;
	this->init(&buff) ;
}

OPrefixFileStream::OPrefixFileStream(const std::string &basename, const std::string &path)
	:	std::OStream()
{
	buff.basename = basename ;
	buff.path = path ;
	this->init(&buff) ;
}

OPrefixFileStream::~OPrefixFileStream()
{
}

void OPrefixFileStream::setBasename(const std::string& value)
{
	buff.basename = value ;
	buff.close() ;
}

void OPrefixFileStream::setPath(const std::string& value)
{
	buff.path = value ;
	buff.close() ;
}

std::string OPrefixFileStream::getBasename() const
{
	return buff.basename ;
}

std::string OPrefixFileStream::getPath() const
{
	return buff.path ;
}

void OPrefixFileStream::setActive(bool value)
{
	buff.active = value ;
}

bool OPrefixFileStream::getActive() const
{
	return buff.active ;
}

PrefixString* OPrefixFileStream::getPrefix() const
{
	return buff.prefix.get() ;
}

OPrefixFileStream& operator<<(OPrefixFileStream& stream, _SetFile f)
{
	if(stream.getPrefix()!=nullptr)
	{
		stream.getPrefix()->setFile(f.file) ;
		stream.getPrefix()->setLine(f.line) ;
		stream.getPrefix()->setCol(f.col) ;
	}
	return stream ;

}

} //End namespace
