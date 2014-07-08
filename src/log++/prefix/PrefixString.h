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

#include <log++/prefix/Prefix.h>

#include <mutex>
#include <vector>
#include <map>

namespace std {
/**
 * Format default string
 * [%criticity%] %component% #%thread% %yyyy%/%MM%/%dd% %HH%:%mm%:%ss%
 * Possible values:
 * criticity: DEBUG, INFO, WARNING, ERROR, FATAL
 * component: name of the component that emits the message
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
class PrefixString : public Prefix
{
public:
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

	inline const std::string &get() { return prefix ; }
	virtual void refresh() ;
protected:
	//Prefix elements
	std::string prefix ;
	std::string format ;

	enum Fields { NONE, COMPONENT, CRITICITY, LEVEL, THREAD, THREAD_ID,
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
} ;

}

#endif
