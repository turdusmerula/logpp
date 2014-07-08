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

#include <log++/prefix/Prefix.h>

#include <boost/lexical_cast.hpp>
#include <ctime>

namespace std {

std::vector<std::string> Prefix::CriticityString={"UNKNOWN", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"} ;
std::map<pthread_t, int> Prefix::threads ;
std::mutex Prefix::threads_mutex ;

Prefix::Prefix()
{
	criticity = INFO ;
	level = 2 ;

	line = -1 ;
	col = -1 ;
}

Prefix::Prefix(Criticity criticity)
	: Prefix()
{
	this->criticity = criticity ;
	level = (int)criticity ;
}

Prefix::Prefix(int level)
	: Prefix()
{
	this->level = level ;
	criticity = (Criticity)level ;
}


Prefix::~Prefix()
{

}

int Prefix::getThreadId() const
{
	static int id=1 ;
	int ret ;
	threads_mutex.lock() ;
	auto ith=threads.find(pthread_self()) ;
	if(ith==threads.end())
	{
		//TODO protect here with mutex
		threads[pthread_self()] = id ;
		threads_mutex.unlock() ;
		ret = id ;
		id++ ;
	}
	else
	{
		threads_mutex.unlock() ;
		return (*ith).second ;
	}
	return ret ;
}


void Prefix::refresh()
{
    msgtime = boost::posix_time::second_clock::local_time() ;
}

}
