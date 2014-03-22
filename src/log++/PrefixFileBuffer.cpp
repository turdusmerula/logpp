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

#include "PrefixFileBuffer.h"

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

namespace std {

std::mutex PrefixFileBuffer::buffer_mutex ;


// The constructor of the PrefixBuffer initializes its pointer to the streambuf
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

PrefixFileBuffer::PrefixFileBuffer()
	:	std::filebuf(),
		cache(),
		newline(false),
		active(true),
		basename("log"),
		path(".")

{
//	setp(0, 0) ;
//	setg(0, 0, 0) ;

	//Open a dummy temp file
	char *tmpname = strdup("/tmp/tmpfileXXXXXX");
	mkstemp(tmpname);
	this->open(tmpname, std::ios_base::out) ;
	//unlink(tmpname) ;

	buff = std::unique_ptr<std::filebuf>(new std::filebuf) ;
	prefix = std::shared_ptr<PrefixString>(new PrefixString) ;
}

PrefixFileBuffer::PrefixFileBuffer(std::shared_ptr<PrefixString> prfx)
	:	PrefixFileBuffer()
{
	prefix = prfx ;
}

PrefixFileBuffer::PrefixFileBuffer(std::shared_ptr<PrefixString> prfx, const std::string &basename, const std::string &path)
	:	PrefixFileBuffer(prfx)
{
	this->basename = basename ;
	this->path = path ;
}

// The destructor of PrefixBuffer has to release the copy of the prefix.
PrefixFileBuffer::~PrefixFileBuffer()
{
}

int PrefixFileBuffer::overflow(int c)
{
	if(!active)
		return 0 ;

	if(c!=EOF)
	{
		//Fill the temporary buffer
		char cc=traits_type::to_char_type(c) ;
		buffer_mutex.lock() ;
		cache.push_back(cc) ;
		buffer_mutex.unlock() ;

		if(cc=='\n')
			newline = true ;

		if(newline)
		{
			//take mutex to ensure consistent write on stream, release automatically at end of scope
			buffer_mutex.lock() ;
			prefix->refresh() ;

			if(buff->is_open()==false)
				openFile() ;
			if(buff->is_open()==false)
			{
				buffer_mutex.unlock() ;
				return EOF ;
			}

			if(buff->sputn(prefix->get().c_str(), prefix->get().size())!=prefix->get().size())
			{
				buffer_mutex.unlock() ;
				return EOF ;
			}
			if(buff->sputn(&cache[0], cache.size())!=cache.size())
			{
				cache.clear() ;
				buffer_mutex.unlock() ;
				return EOF ;
			}
			else
				newline = false ;

			newline = false ;
			cache.clear() ;
			buffer_mutex.unlock() ;
		}

		return 1 ;
	}

	return 0 ;
}


void PrefixFileBuffer::openFile()
{
	std::ostringstream date ;
    auto now = std::chrono::system_clock::now() ;
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    std::stringstream filename ;
    filename << path << "/" << setfill('0')
    		<< basename << 1900+parts->tm_year
    		<< "-" << setw(2) << 1+parts->tm_mon
    		<< "-" << setw(2) << parts->tm_mday
    		<< "T" << setw(2) << parts->tm_hour
    		<< "-" << setw(2) << parts->tm_min
    		<< "-" << setw(2) << parts->tm_sec
    		<< "Z.log" ;
    buff->open(filename.str().c_str(), std::ios::out) ;

}

int PrefixFileBuffer::sync()
{
	if(prefix!=nullptr)
	{
		prefix->setFile("") ;
		prefix->setCol(-1) ;
		prefix->setLine(-1) ;
	}
	return buff->pubsync() ;
}


} //End namespace
