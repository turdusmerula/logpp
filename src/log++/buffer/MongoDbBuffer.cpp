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

#include <log++/buffer/MongoDbBuffer.h>

namespace std {

std::mutex MongoDbBuffer::global_mutex ;

// The constructor of the MongoDbBuffer initializes its pointer to the streambuf
// with the argument sb: It is assumed that this streambuf is initialized
// correctly. In addition no ownership is assumed for this streambuf. It
// is not deleted in the destructor. Then the length of the prefix string
// is cached and the prefix string is copied into a private version: This
// is done to avoid problems when the user modifies or deletes the string
// passed as constructor argument. The member newline is set to indicate
// that the processing it at the beginning of a new line: in either case
// (reading or writing) it starts with a new line. When reading a file a
// prefix has to be skipped and when writing a file a prefix has to be
// added. EOF is used to indicate that the cache does not contain any
// valid character.
// In the body of the constructor the put area and the get area are
// initialized to be empty: no buffering is done by this streambuf. All
// buffering is deferred to the actually used streambuf. This makes sure
// that the function overflow() is called whenever a character is written
// to this streambuf and that the function underflow() is called whenever
// a character is read from this streambuf. The put buffer is specified
// using streambuf::setp() and the get buffer is specified using
// streambuf::setg().
MongoDbBuffer::MongoDbBuffer() :
		std::streambuf(),
		buff(std::cout.rdbuf()),
		cache(),
		newline(false),
		active(true)
//i_buf(prfx->get().size())
{
	setp(0, 0) ;
	setg(0, 0, 0) ;

	prefix = std::shared_ptr<PrefixMongoDb>(new PrefixMongoDb) ;
}

MongoDbBuffer::MongoDbBuffer(std::shared_ptr<PrefixMongoDb> prfx)
	:	MongoDbBuffer()
{
	prefix = prfx ;
}

MongoDbBuffer::MongoDbBuffer(std::shared_ptr<PrefixMongoDb> prfx, std::shared_ptr<mongo::DBClientConnection> conn, const std::string& t)
	: std::MongoDbBuffer(prfx)
{
	mgconn = conn ;
	table = t ;
}

MongoDbBuffer::MongoDbBuffer(std::shared_ptr<mongo::DBClientConnection> conn, const std::string& t)
	: std::MongoDbBuffer()
{
	mgconn = conn ;
	table = t ;
}

// The destructor of MongoDbBuffer has to release the copy of the prefix.
MongoDbBuffer::~MongoDbBuffer()
{
}

int MongoDbBuffer::overflow(int c)
{
	if(!active)
		return 0 ;

	if(c!=EOF)
	{
		//Fill the temporary buffer
		char cc=traits_type::to_char_type(c) ;

		if(cc=='\n')
			newline = true ;
		else
		{
			mutex.lock() ;
			cache += cc ;
			cache.reserve(cache.size()+1) ;
			cache[cache.size()] = '\0' ;
			mutex.unlock() ;
		}

		if(newline)
		{
			//take mutex to ensure consistent write on stream, release automatically at end of scope
			global_mutex.lock() ;
			if(active && cache!="")
			{
				try {
					prefix->refresh() ;
					mongo::BSONObjBuilder blog ;
					prefix->getBson(blog) ;
					blog.append("message", cache) ;
					mongo::BSONObj log=blog.obj() ;

					//std::cout << "table " << table << "  BSON: " << log << std::endl ;
					mgconn->insert(table, log) ;
				} catch(std::exception& e) {
					std::cerr << "Error " << e.what() << std::endl ;
				}
			}
			newline = false ;

			cache.clear() ;
			global_mutex.unlock() ;
		}

		return 1 ;
	}

	return 0 ;
}

int MongoDbBuffer::sync()
{
	if(prefix!=nullptr)
	{
		prefix->setFile("") ;
		prefix->setCol(-1) ;
		prefix->setLine(-1) ;
	}
	return buff->pubsync() ;
}

} // End namespace
