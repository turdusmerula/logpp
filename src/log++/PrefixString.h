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

#ifndef _PREFIXSTRING_H_
#define _PREFIXSTRING_H_

#include <mutex>
#include <vector>
#include <map>

namespace std {
/**
 * Format default string
 * [%criticity%] #%thread% %yyyy%/%MM%/%dd% %HH%:%mm%:%ss%
 * Possible values:
 * criticity: DEBUG, INFO, WARNING, ERROR, FATAL
 * level: same as criticity but numbers, 1(DEBUG) to 5(FATAL), or more for custom
 * thread: thread number
 * threadid: system thread identifier
 * yy/yyyy: year
 * M/MM: month number
 * d/dd: day number
 * H/HH: hour
 * m/mm: month
 * s/ss: second
 * loc: prints message location file:line:col,
 * 		if file is blank then loc is ignored
 * 		if line is blank then line and col are ignored
 * 		if col is blank then it's ignored
 */
class PrefixString
{
public:
	enum Criticity { UNKNOWN=0, DEBUG, INFO, WARNING, ERROR, FATAL } ;

public:
	PrefixString() ;
	PrefixString(const std::string format) ;
	PrefixString(Criticity criticity) ;
	PrefixString(const std::string format, Criticity criticity) ;
	PrefixString(int level) ;
	PrefixString(const std::string format, int level) ;
	virtual ~PrefixString() ;

	void setFormat(const std::string &format) ;
	std::string getFormat() const ;

	void setCriticity(Criticity value) { criticity = value ; level = value ; }
	Criticity getCriticity() const { return criticity ; }
	std::string getCriticityString() const { return CriticityString[criticity] ; }

	void setLevel(int value) { level = value ; criticity=(level>0 && level<=FATAL?(Criticity)level:UNKNOWN) ; }
	Criticity getLevel() const { return criticity ; }

	void setLine(int value) { line = value ; }
	int getLine() const { return line ; }

	void setCol(int value) { col = value ; }
	int getCol() const { return col ; }

	void setFile(const std::string& value) { file = value ; }
	std::string getFile() const { return file ; }

	inline const std::string &get() { return prefix ; }
	virtual void refresh() ;
protected:
	std::string prefix ;
	std::string format ;
	static std::map<pthread_t, int> threads ;
	static std::mutex threads_mutex ;
	Criticity criticity ;
	int level ;

	int line ;
	int col ;
	std::string file ;

	static std::vector<std::string> CriticityString ;

	enum Fields { NONE, CRITICITY, LEVEL, THREAD, THREAD_ID,
		DATE_YEAR, DATE_MONTH, DATE_DAY, DATE_HOUR, DATE_MINUTE, DATE_SECOND,
		LOC } ;

	struct PrefixField
	{
		Fields field ;
		std::string value ;
		int digits ;
	} ;
	std::vector<PrefixField> fields ;
	bool addFormatField(const std::string &field) ;

	int getThreadId() ;

} ;

}

#endif
