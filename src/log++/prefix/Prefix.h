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

#ifndef _PREFIX_H_
#define _PREFIX_H_

#include <mutex>
#include <vector>
#include <map>

#include <log++/util.h>

namespace std {

class Prefix
{
public:
	typedef enum { UNKNOWN=0, DEBUG, INFO, WARNING, ERROR, FATAL } Criticity ;

public:
	Prefix() ;
	Prefix(Criticity criticity) ;
	Prefix(int level) ;
	virtual ~Prefix() ;

	void setCriticity(Criticity value) { criticity = value ; level = value ; }
	Criticity getCriticity() const { return criticity ; }
	std::string getCriticityString() const { return CriticityString[criticity] ; }

	void setLevel(int value) { level = value ; criticity=(level>0 && level<=FATAL?(Criticity)level:UNKNOWN) ; }
	Criticity getLevel() const { return criticity ; }

	void setComponent(const std::string& value) { component = value ; }
	std::string getComponent() const { return component ; }

	void setLine(int value) { line = value ; }
	int getLine() const { return line ; }

	void setCol(int value) { col = value ; }
	int getCol() const { return col ; }

	void setFile(const std::string& value) { file = value ; }
	std::string getFile() const { return file ; }

	void setTime(const boost::posix_time::ptime& value) { msgtime=value ; }
	boost::posix_time::ptime getTime() const { return msgtime ; }

	int getThreadId() const ;

	virtual void refresh() ;
protected:
	//Prefix elements
	Criticity criticity ;
	int level ;
	std::string component ;

	//Date
	boost::posix_time::ptime msgtime ;

	//Filename
	int line ;
	int col ;
	std::string file ;

	static std::map<pthread_t, int> threads ;
	static std::mutex threads_mutex ;

	//Enum for criticity
	static std::vector<std::string> CriticityString ;


} ;

}

#endif
