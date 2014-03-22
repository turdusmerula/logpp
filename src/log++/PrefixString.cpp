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

#include "PrefixString.h"

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <chrono>
#include <ctime>

namespace std {

std::vector<std::string> PrefixString::CriticityString={"UNKNOWN", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"} ;
std::map<pthread_t, int> PrefixString::threads ;
std::mutex PrefixString::threads_mutex ;

PrefixString::PrefixString()
{
	criticity = INFO ;
	level = 2 ;

	setFormat("%loc%[%criticity%] #%thread% [%yyyy%/%MM%/%dd% %HH%:%mm%:%ss%] ") ;
	line = -1 ;
	col = -1 ;
}

PrefixString::PrefixString(const std::string format)
	: PrefixString()
{
	setFormat(format) ;
}

PrefixString::PrefixString(Criticity criticity)
	: PrefixString()
{
	this->criticity = criticity ;
	level = (int)criticity ;
}

PrefixString::PrefixString(int level)
	: PrefixString()
{
	this->level = level ;
	criticity = (Criticity)level ;
}

PrefixString::PrefixString(const std::string format, Criticity criticity)
	: PrefixString(criticity)
{
	setFormat(format) ;
}


PrefixString::PrefixString(const std::string format, int level)
	: PrefixString(level)
{
	setFormat(format) ;
}

PrefixString::~PrefixString()
{

}

bool PrefixString::addFormatField(const std::string &fieldname)
{
	PrefixField field ;

	if(fieldname=="criticity")
		field.field = CRITICITY ;
	else if(fieldname=="level")
		field.field = LEVEL ;
	else if(fieldname=="thread")
		field.field = THREAD ;
	else if(fieldname=="threadid")
		field.field = THREAD_ID ;
	else if(fieldname=="yy")
	{
		field.digits = 2 ;
		field.field = DATE_YEAR ;
	}
	else if(fieldname=="yyyy")
	{
		field.digits = 4 ;
		field.field = DATE_YEAR ;
	}
	else if(fieldname=="M")
	{
		field.digits = 1 ;
		field.field = DATE_MONTH ;
	}
	else if(fieldname=="MM")
	{
		field.digits = 2 ;
		field.field = DATE_MONTH ;
	}
	else if(fieldname=="d")
	{
		field.digits = 1 ;
		field.field = DATE_DAY ;
	}
	else if(fieldname=="dd")
	{
		field.digits = 2 ;
		field.field = DATE_DAY ;
	}
	else if(fieldname=="H")
	{
		field.digits = 1 ;
		field.field = DATE_HOUR ;
	}
	else if(fieldname=="HH")
	{
		field.digits = 2 ;
		field.field = DATE_HOUR ;
	}
	else if(fieldname=="m")
	{
		field.digits = 1 ;
		field.field = DATE_MINUTE ;
	}
	else if(fieldname=="mm")
	{
		field.digits = 2 ;
		field.field = DATE_MINUTE ;
	}
	else if(fieldname=="s")
	{
		field.digits = 1 ;
		field.field = DATE_SECOND ;
	}
	else if(fieldname=="ss")
	{
		field.digits = 2 ;
		field.field = DATE_SECOND ;
	}
	else if(fieldname=="loc")
		field.field = LOC ;
	else
		return false ;

	fields.push_back(field) ;
	return true ;
}

void PrefixString::setFormat(const std::string &format)
{
	std::string curr ;
	char* c=(char*)format.c_str() ;

	fields.clear() ;

	while(*c!='\0')
	{
		if(*c=='%')
		{
			std::string field ;
			c++ ;
			if(*c=='%')
				curr += '%' ;	//a %% means %
			while(*c!='%' && *c!='\0')
			{
				field += *c ;
				c++ ;
			}

			if(*c=='\0')
			{
				curr += '%' ;
				curr += field ;
				field = "" ;
			}
			else
				c++ ;

			if(curr!="")
			{
				fields.push_back(PrefixField({NONE, curr, 0})) ;
				curr = "" ;
			}

			addFormatField(field) ;
		}
		else
		{
			curr += *c ;
			c++ ;
		}
	}

	if(curr!="")
	{
		fields.push_back(PrefixField({NONE, curr, 0})) ;
		curr = "" ;
	}

	this->format = format ;
}

int PrefixString::getThreadId()
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


void PrefixString::refresh()
{
	std::ostringstream date ;
    auto now = std::chrono::system_clock::now() ;
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);


    std::ostringstream s ;

    for(auto field : fields)
    {
		boost::io::ios_all_saver guard(s) ; // Saves current flags and format

    	switch(field.field)
    	{
    	case NONE:
    		s << field.value ;
    		break ;
    	case CRITICITY:
    		s << getCriticityString() ;
    		break ;
    	case LEVEL:
    		s << getLevel() ;
    		break ;
    	case THREAD:
    		s << getThreadId() ;
    		break ;
    	case THREAD_ID:
    		s << pthread_self() ;
    		break ;
    	case DATE_YEAR:
    		if(field.digits==2)
    			s << parts->tm_year ;
    		else
    			s << std::setfill('0') << std::setw(4) << 1900 + parts->tm_year ;
    		break ;
    	case DATE_MONTH:
    		if(field.digits==2)
    			s << std::setfill('0') << std::setw(2) << 1+parts->tm_mon ;
    		else
    			s << 1+parts->tm_mon ;
    		break ;
    	case DATE_DAY:
    		if(field.digits==2)
    			s << std::setfill('0') << std::setw(2) << parts->tm_mday ;
    		else
    			s << parts->tm_mday ;
    		break ;
    	case DATE_HOUR:
    		if(field.digits==2)
    			s << std::setfill('0') << std::setw(2) << parts->tm_hour ;
    		else
    			s << parts->tm_hour ;
    		break ;
    	case DATE_MINUTE:
    		if(field.digits==2)
    			s << std::setfill('0') << std::setw(2) << parts->tm_min ;
    		else
    			s << parts->tm_min ;
    		break ;
    	case DATE_SECOND:
    		if(field.digits==2)
    			s << std::setfill('0') << std::setw(2) << parts->tm_sec ;
    		else
    			s << parts->tm_sec ;
    		break ;
    	case LOC:
    		if(file=="")
    			break ;
			s << file ;

			if(line!=-1)
				s << ":" << line ;
			else
			{
				s << " " ;
				break ;
			}

			if(col!=-1)
				s << ":" << col ;
			s << " " ;
    		break ;
    	}
    }

    prefix = s.str() ;
}

}
