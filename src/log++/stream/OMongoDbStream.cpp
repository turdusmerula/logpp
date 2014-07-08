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

#include <log++/stream/OMongoDbStream.h>

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

namespace std {



OMongoDbStream::OMongoDbStream()
	: 	OStream()
{
	prefix = std::shared_ptr<PrefixMongoDb>(new PrefixMongoDb) ;
	buff = new MongoDbBuffer(prefix) ;
	init(buff) ;
}

OMongoDbStream::OMongoDbStream(std::shared_ptr<PrefixMongoDb> prfx)
	:	OStream(buff=new MongoDbBuffer(prfx))
{
	prefix = prfx ;
}

OMongoDbStream::OMongoDbStream(std::shared_ptr<PrefixMongoDb> prfx, std::shared_ptr<mongo::DBClientConnection> conn, const std::string& t)
	: std::OMongoDbStream(prfx)
{
	mgconn = conn ;
	table = t ;
	buff->setConn(conn) ;
	buff->setTable(table) ;
}

OMongoDbStream::OMongoDbStream(std::shared_ptr<mongo::DBClientConnection> conn, const std::string& t)
	: std::OMongoDbStream()
{
	mgconn = conn ;
	table = t ;
	buff->setConn(conn) ;
	buff->setTable(table) ;
}

OMongoDbStream::~OMongoDbStream()
{
}

OMongoDbStream& operator<<(OMongoDbStream& stream, _SetFile f)
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
