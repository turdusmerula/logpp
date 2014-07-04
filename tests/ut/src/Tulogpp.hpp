#include <log++/log++.h>

class AddlogppTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(AddlogppTest) ;
    CPPUNIT_TEST(testDefaultConfig) ;
    CPPUNIT_TEST(testChangeDebugPrefix) ;
    CPPUNIT_TEST(testAddSecondStream) ;
    CPPUNIT_TEST(testAddFileStream) ;
    CPPUNIT_TEST(testActivate) ;
    CPPUNIT_TEST_SUITE_END();

	void testDefaultConfig()
	{
		std::debug << "Debug message" << std::endl ;
		std::info << "Info message" << std::endl ;
		std::warn << "Warning message" << std::endl ;
		std::error << "Error message" << std::endl ;
		std::fatal << "Fatal message" << std::endl ;
	}

	void testChangeDebugPrefix()
	{
    	for(auto& stream : std::debug.getStreams())
    		stream->getPrefix()->setFormat("-- new prefix -- ") ;
		std::debug << "Debug message" << std::endl ;
	}

	void testAddSecondStream()
	{
		std::debug.getStreams().push_back(std::shared_ptr<std::OStream>(new std::OPrefixStream(std::cout.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(" -- second logger -- ", std::PrefixString::DEBUG))))) ;
		std::debug << "Debug message" << std::endl ;
	}

	void testAddFileStream()
	{
		std::debug.getStreams().push_back(std::shared_ptr<std::OStream>(new std::OPrefixFileStream(std::shared_ptr<std::PrefixString>(new std::PrefixString(" -- third logger -- ", std::PrefixString::DEBUG))))) ;
		std::debug << "Debug message" << std::endl ;
	}

	void testActivate()
	{
		std::debug << "Debug message should appear" << std::endl ;
		std::debug.setActive(false) ;
		std::debug << "Debug message should not appear" << std::endl ;
		std::debug.setActive(true) ;
		std::debug << "Debug message should appear again" << std::endl ;
	}
} ;

CPPUNIT_TEST_SUITE_REGISTRATION(AddlogppTest) ;
