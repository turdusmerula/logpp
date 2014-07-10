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


#include <log++/util.h>

namespace std {

mongo::Date_t ptime2date_t(const boost::posix_time::ptime& time)
{
    boost::posix_time::ptime epoch(boost::gregorian::date(1970,boost::date_time::Jan,1));
    boost::posix_time::time_duration d = time - epoch;
    return mongo::Date_t(d.total_milliseconds());
}
boost::posix_time::ptime date_t2ptime(const mongo::Date_t& time)
{
    boost::posix_time::ptime epoch(boost::gregorian::date(1970,boost::date_time::Jan,1));
    boost::posix_time::time_duration d = boost::posix_time::milliseconds(time.millis);//- epoch;
    return boost::posix_time::ptime(epoch+d);
}

time_t ptime2time_t(boost::posix_time::ptime t)
{
    using namespace boost::posix_time;
    ptime epoch(boost::gregorian::date(1970,1,1));
    time_duration::sec_type x = (t - epoch).total_seconds();
    return time_t(x);
}


}
