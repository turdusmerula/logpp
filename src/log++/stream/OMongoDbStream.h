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

#ifndef _MONGODBSTREAM_H_
#define _MONGODBSTREAM_H_

#include <log++/stream/OStream.h>
#include <log++/prefix/PrefixMongoDb.h>
#include <log++/buffer/MongoDbBuffer.h>

#include <memory>

namespace std {

class OMongoDbStream : public std::OStream
{
public:
	OMongoDbStream() ;
	OMongoDbStream(std::shared_ptr<PrefixMongoDb> prfx) ;
	OMongoDbStream(std::shared_ptr<PrefixMongoDb> prfx, std::shared_ptr<mongo::DBClientConnection> conn, const std::string& table) ;
	OMongoDbStream(std::shared_ptr<mongo::DBClientConnection> conn, const std::string& table) ;

	~OMongoDbStream();

	std::shared_ptr<mongo::DBClientConnection> getConn() const { return mgconn ; }
	void setConn(std::shared_ptr<mongo::DBClientConnection> value) { mgconn = value ; buff->setConn(value) ; }

	std::string getTable() const { return table ; }
	void setTable(const std::string& value) { table = value ; buff->setTable(value) ; }

	virtual PrefixMongoDb* getPrefix() const { return buff->prefix.get() ; }

protected:
	//Mongodb configuration
	std::shared_ptr<mongo::DBClientConnection> mgconn ;
	std::string table ;

	std::shared_ptr<PrefixMongoDb> prefix ;
	MongoDbBuffer* buff ; 	// the actual streambuf used to read and write chars
} ;

extern OMongoDbStream& operator<<(OMongoDbStream&, _SetFile) ;

} //End namespace
#endif /* _PRFXSTREAM_H_ */
