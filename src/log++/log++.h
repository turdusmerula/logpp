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

#ifndef _LOGPP_H_
#define _LOGPP_H_

#include <log++/OPrefixStream.h>
#include <log++/MultiOStream.h>
#include <log++/IOManip.h>

#define currpos std::setfile(__FILE__, __LINE__)

namespace std {

//extern thread_local std::OPrefixStream debug ;
extern thread_local std::MultiOStream debug ;
extern thread_local std::MultiOStream info ;
extern thread_local std::MultiOStream warn ;
extern thread_local std::MultiOStream error ;
extern thread_local std::MultiOStream fatal ;

}

#endif // _LOGPP_H_
