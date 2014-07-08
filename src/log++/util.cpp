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
