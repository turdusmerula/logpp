#ifndef _UTIL_H
#define _UTIL_H

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <mongo/client/dbclient.h>

namespace std {

mongo::Date_t ptime2date_t(const boost::posix_time::ptime& time) ;

boost::posix_time::ptime date_t2ptime(const mongo::Date_t& time) ;

time_t ptime2time_t(boost::posix_time::ptime t) ;

}

#endif
