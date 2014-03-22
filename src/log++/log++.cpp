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

#include "log++.h"

#include <iostream>
#include <vector>

namespace std {

//TODO: use a MultiOStream by defening output to log file and console simultaneously
//TODO: add an udp/tcp logger
//TODO: intercept all stdout and stderr outputs, possible?

//Declared static local to thread to avoid line collision when writing simultaneously
//thread_local std::OPrefixStream debug(std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::DEBUG))) ;
/*thread_local std::OPrefixStream info(std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::INFO))) ;
thread_local std::OPrefixStream warn(std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::WARNING))) ;
thread_local std::OPrefixStream error(std::cerr.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::ERROR))) ;
thread_local std::OPrefixStream fatal(std::cerr.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::FATAL))) ;*/

thread_local std::MultiOStream debug({
		new std::OPrefixStream (std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::DEBUG)))
	}) ;
thread_local std::MultiOStream info({
		new std::OPrefixStream (std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::INFO)))
	}) ;
thread_local std::MultiOStream warn({
		new std::OPrefixStream (std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::WARNING)))
	}) ;
thread_local std::MultiOStream error({
		new std::OPrefixStream (std::cerr.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::ERROR)))
	}) ;
thread_local std::MultiOStream fatal({
		new std::OPrefixStream (std::cerr.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::FATAL)))
	}) ;

} //End namespace
