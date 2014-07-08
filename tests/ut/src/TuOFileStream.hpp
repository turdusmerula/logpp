
#include <log++/stream/OPrefixFileStream.h>

class AddOFilesStreamTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(AddOFilesStreamTest) ;
    CPPUNIT_TEST(testOFSDefaultConfig) ;
    CPPUNIT_TEST(testOFSCerr) ;
    CPPUNIT_TEST(testOFSInactive) ;
    CPPUNIT_TEST(testOFSChangeFormat) ;
    CPPUNIT_TEST(testOFSFilePos) ;
    CPPUNIT_TEST_SUITE_END();

	void testOFSDefaultConfig()
	{
		std::OPrefixFileStream log ;

		log << "Test output to log file with default config" << std::endl ;
	}

	void testOFSCerr()
	{
		std::OPrefixFileStream log(std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::FATAL))) ;

		log << "Test output to log file with extended config" << std::endl ;
	}

	void testOFSInactive()
	{
		std::OPrefixFileStream log ;

		log << "Buffer actif" << std::endl ;
		log.setActive(false) ;
		log << "Buffer inactif, rien ne doit sortir ici" << std::endl ;
	}

	void testOFSChangeFormat()
	{
		std::OPrefixFileStream log ;

		log << "Test format par défaut" << std::endl ;
		log.getPrefix()->setFormat("--new format-- [%criticity%] ") ;
		log << "Test avec nouveau format" << std::endl ;
	}

	void testOFSFilePos()
	{
		std::OPrefixFileStream log ;

		log << std::endl ;
		log << std::setfile("file1.c") << "Test output with filename" << std::endl ;
		log << "Test output without filename" << std::endl ;
		log << std::setfile("file2.c", 4) << "Test output with filename:line" << std::endl ;
		log << "Test output without filename" << std::endl ;
		log << std::setfile("file3.c" , 8, 36) << "Test output with filename:line:col" << std::endl ;
		log << "Test output without filename" << std::endl ;
		log << std::setfile("file3.c" , 8, 36) << "Test output with filename:line:col multiline, line 1" << "\n" ;
		log << "Test output with filename:line:col multiline, line 2" << "\n" ;
		log << "Test output with filename:line:col multiline, line 3" << std::endl ;
		log << "Test output without filename" << std::endl ;
	}
} ;

CPPUNIT_TEST_SUITE_REGISTRATION(AddOFilesStreamTest) ;
