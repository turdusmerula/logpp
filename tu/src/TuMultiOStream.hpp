#include <log++/MultiOStream.h>

class MultiOStreamTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(MultiOStreamTest) ;
    CPPUNIT_TEST(testMOSDefaultConfig) ;
    CPPUNIT_TEST(testMOSCerr) ;
    CPPUNIT_TEST(testMOSInactive) ;
    CPPUNIT_TEST(testMOSChangeFormat) ;
    CPPUNIT_TEST(testMOSFilePos) ;
    CPPUNIT_TEST_SUITE_END();

	void testMOSDefaultConfig()
	{
		std::MultiOStream log({
			new std::OPrefixStream(std::cout.rdbuf()),
			new std::OPrefixFileStream("multilog")
		}) ;

		log << "Test output to multiple logger with default config" << std::endl ;
	}

	void testMOSCerr()
	{
		std::MultiOStream log({
			new std::OPrefixStream(std::cerr.rdbuf(), std::shared_ptr<std::PrefixString>(new std::PrefixString(std::PrefixString::FATAL))),
			new std::OPrefixFileStream("multilog")
		}) ;

		log << "Test output to cerr with extended config" << std::endl ;
	}

	void testMOSInactive()
	{
		std::MultiOStream log({
			new std::OPrefixStream(std::cout.rdbuf()),
			new std::OPrefixFileStream("multilog")
		}) ;

		log << "Buffer actif" << std::endl ;
		log.setActive(false) ;
		log << "Buffer inactif, rien ne doit sortir ici" << std::endl ;
	}

	void testMOSChangeFormat()
	{
//		std::OPrefixStream tocout(std::cout.rdbuf()) ;
//
//		tocout << "Test format par défaut" << std::endl ;
//		tocout.getPrefix()->setFormat("--new format-- [%criticity%] ") ;
//		tocout << "Test avec nouveau format" << std::endl ;
	}

	void testMOSFilePos()
	{
		std::MultiOStream log({
			new std::OPrefixStream(std::cout.rdbuf()),
			new std::OPrefixFileStream("multilog")
		}) ;

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
		log << currpos << "Test réel" << std::endl ;
	}

} ;

CPPUNIT_TEST_SUITE_REGISTRATION(MultiOStreamTest) ;
