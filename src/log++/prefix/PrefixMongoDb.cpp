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

#include <log++/prefix/PrefixMongoDb.h>

namespace std {

PrefixMongoDb::PrefixMongoDb()
	: Prefix()
{
}

PrefixMongoDb::PrefixMongoDb(Criticity criticity)
	: Prefix(criticity)
{
}

PrefixMongoDb::PrefixMongoDb(int level)
	: Prefix(level)
{
}

PrefixMongoDb::~PrefixMongoDb()
{

}


void PrefixMongoDb::refresh()
{
	Prefix::refresh() ;
}

void PrefixMongoDb::getBson(mongo::BSONObjBuilder& b) const
{
	b.append("criticity", getLevel()) ;
	b.append("component", getComponent()) ;
	b.append("line", getLine()) ;
	b.append("col", getCol()) ;
	b.append("file", getFile()) ;
	b.append("thread", getThreadId()) ;
	b.append("date", ptime2date_t(getTime())) ;
}

}
