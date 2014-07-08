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

#ifndef _MONGODBBUFFER_H_
#define _MONGODBBUFFER_H_

#include <streambuf>
#include <ios>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>

#include <log++/prefix/PrefixMongoDb.h>
#include <log++/util.h>

namespace std {

/**
 * Class used to change default stream buffer of standard ios
 */
class MongoDbBuffer: public std::streambuf
{
public:
	MongoDbBuffer() ;
	MongoDbBuffer(std::shared_ptr<PrefixMongoDb> prfx) ;
	MongoDbBuffer(std::shared_ptr<PrefixMongoDb> prfx, std::shared_ptr<mongo::DBClientConnection> conn, const std::string& table) ;
	MongoDbBuffer(std::shared_ptr<mongo::DBClientConnection> conn, const std::string& table) ;
	~MongoDbBuffer() ;

	std::shared_ptr<mongo::DBClientConnection> getConn() const { return mgconn ; }
	void setConn(std::shared_ptr<mongo::DBClientConnection> value) { mgconn = value ; }

	std::string getTable() const { return table ; }
	void setTable(const std::string& value) { table = value ; }

	friend class OMongoDbStream ;
protected:
	int overflow(int) ;
	int sync() ;

	std::unique_ptr<std::streambuf> buff ; 	// the actual streambuf used to read and write chars
	std::shared_ptr<PrefixMongoDb> prefix ;
	bool active ;

	//Mongodb configuration
	std::shared_ptr<mongo::DBClientConnection> mgconn ;
	std::string table ;

	std::string cache ;	//cache used for consistent console write
	bool newline ; 			//remember whether we are at a new line
	std::mutex mutex ;
	static std::mutex global_mutex ;
} ;


} //End namespace
#endif /* _PRFXSTREAM_H_ */
