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

#include "MultiOStream.h"
#include "OPrefixFileStream.h"
#include "OPrefixStream.h"

namespace std {


MultiOStream::MultiOStream(const std::vector<std::OStream*> &_streams)
{
	active = true ;

	for(auto& stream : _streams)
		streams.push_back(std::shared_ptr<std::OStream>(stream)) ;
}

MultiOStream::MultiOStream(const std::vector<std::shared_ptr<std::OStream>> &_streams)
{
	active = true ;

	for(auto& stream : _streams)
		streams.push_back(stream) ;
}


MultiOStream &MultiOStream::operator<<(std::ostream &(*f)(std::ostream&))
{
	if(active)
	{
		for(auto& stream : streams)
			(*stream) << f ;
	}

	return *this ;
}

MultiOStream& operator<<(MultiOStream& stream, _SetFile f)
{
	if(stream.active)
	{
		for(auto& s : stream.streams)
		{
			try {
				OPrefixFileStream* rs=dynamic_cast<OPrefixFileStream*>(s.get()) ;
				if(rs!=NULL)
					*rs << f ;
			}catch(std::bad_cast& e){ }

			try {
				OPrefixStream* rs=dynamic_cast<OPrefixStream*>(s.get()) ;
				if(rs!=NULL)
					*rs << f ;
			}catch(std::bad_cast& e){ }

		}
	}

	return stream ;

}

} //End namespace
