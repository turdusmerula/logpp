#include <log++/stream/OPrefixStream.h>

class AddOStreamTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(AddOStreamTest) ;
    CPPUNIT_TEST(testDefaultConfig) ;
    CPPUNIT_TEST(testCerr) ;
    CPPUNIT_TEST(testInactive) ;
    CPPUNIT_TEST(testChangeFormat) ;
    CPPUNIT_TEST(testFilePos) ;
    CPPUNIT_TEST_SUITE_END();

	void testDefaultConfig()
	{
		std::OPrefixStream tocout(std::cout.rdbuf()) ;

		tocout << "Test output to cout with default config" << std::endl ;
	}

	void testCerr()
	{
		std::OPrefixStream tocout(std::cerr.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::FATAL))) ;

		tocout << "Test output to cerr with extended config" << std::endl ;
	}

	void testInactive()
	{
		std::OPrefixStream tocout(std::cout.rdbuf()) ;

		tocout << "Buffer actif" << std::endl ;
		tocout.setActive(false) ;
		tocout << "Buffer inactif, rien ne doit sortir ici" << std::endl ;
	}

	void testChangeFormat()
	{
		std::OPrefixStream tocout(std::cout.rdbuf()) ;

		tocout << "Test format par défaut" << std::endl ;
		tocout.getPrefix()->setFormat("--new format-- [%criticity%] ") ;
		tocout << "Test avec nouveau format" << std::endl ;
	}

	void testFilePos()
	{
		std::OPrefixStream tocout(std::cout.rdbuf()) ;

		tocout << std::endl ;
		tocout << std::setfile("file1.c") << "Test output with filename" << std::endl ;
		tocout << "Test output without filename" << std::endl ;
		tocout << std::setfile("file2.c", 4) << "Test output with filename:line" << std::endl ;
		tocout << "Test output without filename" << std::endl ;
		tocout << std::setfile("file3.c" , 8, 36) << "Test output with filename:line:col" << std::endl ;
	}

} ;

CPPUNIT_TEST_SUITE_REGISTRATION(AddOStreamTest) ;
