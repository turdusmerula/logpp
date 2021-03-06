log++
======

log++ is a library for fast and simple logging purpose, it is able to log into console, file or mongodb database. 

Log++ is able to log inside simultaneous streams at the same time and automatically prepend informations to the data logged.

Note: When I created this library I wasn't aware of the existence of Boost.log so it's pretty similar but not compatible. 
Note: Once you do not need the special abilities of log++ such as adding file name to the logged data or logging to mongodb I strongly recommend you to use the Boost.log data logger that may be more stable. 

Building log++
=====

Simply use the build script:

    ./build.sh
    
Installing log++
=====

The installer is only provided for debian systems but may work on other systems:

    ./install.sh

Using log++
=====

Dependencies
====
Log++ uses boost and mongodb and will need the following libraries:
 *  mongoclient
 *  pthread
 *  crypto
 *  ssl
 *  boost_filesystem 
 *  boost_regex 
 *  boost_system 
 *  boost_thread 

Boost minimum version required is 1.49 

Linking log++ on cmake
====
Simply add the following line in CMakeLists.txt:

  find_package(log++ REQUIRED HINTS "${CMAKE_INSTALL_PREFIX}/lib/log++")

The following variables are defined by find script:

| variable                | description
| ----------------------- | ---------------------------------------------
| LIBLOGPP_FOUND          | True if liblog++ is found.
| LIBLOGPP_INCLUDE_DIRS   | Directory where liblog++ headers are located.
| LIBLOGPP_LIBRARIES      | log++ libraries to link against.
| LIBLOGPP_VERSION_MAJOR  | The major version of log++
| LIBLOGPP_VERSION_MINOR  | The minor version of log++
| LIBLOGPP_VERSION_PATCH  | The patch version of log++
| LIBLOGPP_VERSION_STRING | version number as a string (ex: "2.0.0")


The most simple case
====

log++ comes preconfigured to log on stdout and stderr with five predefined messages level:

| criticity     | level         | output
| ------------- | ------------- | -------------
| debug         | 1             | stdout
| info          | 2             | stdout
| warning       | 3             | stdout
| error         | 4             | stderr
| fatal         | 5             | stderr

There is nothing to configure in the most simple case.

Code example:

    #include <log/log++.>
    
    void main(int argc, char** argv)
    {
    	std::debug << "This is a debug message" << std::endl ;
    	std::fatal << "This is a fatal error message" << std::endl ;
    }
    
It will produce the following output on the console:

    [DEBUG] #1 [2014/03/21 02:27:34] This is a debug message
    [FATAL] #1 [2014/03/21 02:27:34] This is a fatal error message

Appending a new logger
====
Appending a new logger is made simply, look at the following sample that adds a file logger to a multi stream:


    #include <log/log++.>
    
    void main(int argc, char** argv)
    {
		std::debug.getStreams().push_back(
			std::shared_ptr<std::OStream>(
				new std::OPrefixFileStream(
					std::shared_ptr<std::PrefixString>(new std::PrefixString(" -- third logger -- ", std::PrefixString::DEBUG))
				)
			)
		) ;

    	std::debug << "This is a debug message that will log on console and file" << std::endl ;
    	std::fatal << "This is a fatal error message" << std::endl ;
    }
  

Changing prefix format
====
The format of the prefix can be changed for each stream inside a multi stream object with few lines of code:

    #include <log/log++.>
    
    void main(int argc, char** argv)
    {
    	//Change the prefix for each stream 
    	for(auto& stream : std::debug.getStreams())
    		stream->getPrefix()->setFormat("-- new prefix -- ") ;
    	
    	std::debug << "This is a debug message" << std::endl ;
    	std::fatal << "This is a fatal error message" << std::endl ;
    }
    
If not changed new streams are given the following default prefix value:

    %loc%[%criticity%] #%thread% [%yyyy%/%MM%/%dd% %HH%:%mm%:%ss%] 

Predefined variables should be surounded by %, a double %% gives a % in the prefix. The possible variables names are the following:

| Variable      | Values 
| ------------- | ------------------------------------------------------------------------ 
| criticity     | DEBUG, INFO, WARNING, ERROR, FATAL 
| component     | Component name, empty by default
| level         | Same as criticity but numbers, 1(DEBUG) to 5(FATAL), or more for custom 
| thread        | Thread creation number 
| threadid      | System thread identifier 
| yy or yyyy    | Year 
| M or MM       | Month number 
| d or dd       | Day number 
| H or HH       | Hour 
| m or mm       | Month 
| s or ss       | Seconds   
| loc           | Prints message location file:line:col 

Note: 
 * 		if file is blank then loc is ignored
 * 		if line is blank then line and col are ignored
 * 		if col is blank then it's ignored

Enabling/disabling loggers
====

It is possible to enable or disable a whole multi stream object or only some streams contained by the multi stream object:

    #include <log/log++.>
    
    void main(int argc, char** argv)
    {
		//Disable whole multi stream object
		std::debug.setActive(false) ;

    	std::debug << "This is a debug message" << std::endl ;
		
		//Enable whole multi stream object
		std::debug.setActive(true) ;

		//Disable first stream object only
		std::debug.getStreams()[0]->setActive(false) ;
		
    	std::debug << "This is a debug message" << std::endl ;
    }


Sourcecode log localisation
====

log++ helps tracking position of logged messages inside source code, it's made really simply. Inside prefix format the %loc% is used to put the source code position inside the code. 
If there's no position to track then it's left blank.

There is two ways of putting the position:

 * use the std::setfile stream modifier, it will take at max three parameters, source file, line and column:
 
    std::cout << std::setfile("myfile.c", 10, 20) << "My message" << std::endl ;
    
 * use the macro currpos, it will automatically fill the file name and line from the point where it is called:

    std::cout << currpos << "My message" << std::endl ;
 

Customizing prefix keywords
====

