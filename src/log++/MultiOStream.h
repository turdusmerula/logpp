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

#ifndef MULTIOSTREAM_H_
#define MULTIOSTREAM_H_

#include <vector>
#include <memory>

#include <log++/OStream.h>

namespace std {

class MultiOStream {
public:
	MultiOStream(const std::vector<std::OStream*> &streams) ;
	MultiOStream(const std::vector<std::shared_ptr<std::OStream>> &streams) ;

	template<typename T>
	MultiOStream &operator<<(const T &v) ;

	MultiOStream &operator<<(std::ostream &(*f)(std::ostream&)) ;

	void setActive(bool value) { active = value ; }
	bool getActive() const { return active ; }

	std::vector<std::shared_ptr<std::OStream>>& getStreams() { return streams ; }

private:
	bool active ;
	std::vector<std::shared_ptr<std::OStream>> streams ;

	friend MultiOStream& operator<<(MultiOStream&, _SetFile) ;
} ;

template<typename T>
MultiOStream &MultiOStream::operator<<(const T &v)
{
	if(active==true)
	{
		for(auto& stream : streams)
			(*stream) << v ;
	}
	return *this ;
}

extern MultiOStream& operator<<(MultiOStream&, _SetFile) ;

} //End namespace


#endif /* MULTIOSTREAM_H_ */
