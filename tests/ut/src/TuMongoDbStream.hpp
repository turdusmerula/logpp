#include <log++/stream/OMongoDbStream.h>

#include <log++/util.h>

extern std::shared_ptr<mongo::DBClientConnection> mgconn ;

class AddOMongoDbStreamTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(AddOMongoDbStreamTest) ;
    CPPUNIT_TEST(testInactive) ;
    CPPUNIT_TEST(testFilePos) ;
    CPPUNIT_TEST_SUITE_END();

	void testInactive()
	{
		std::OMongoDbStream tocout(mgconn, "logpp.logs") ;


		try {
			tocout << "Buffer actif" << std::endl ;
			std::cout << "isfailed " << mgconn->getLastError() << std::endl ;
			tocout.setActive(false) ;
			tocout << "Buffer inactif, rien ne doit sortir ici" << std::endl ;
		} catch(std::exception& e) {
			std::cout << e.what() << std::endl ;
		}
	}

	void testFilePos()
	{
		std::OMongoDbStream tocout(mgconn, "logpp.logs") ;

		tocout << std::endl ;
		tocout << std::setfile("file1.c") << "Test output with filename" << std::endl ;
		tocout << "Test output without filename" << std::endl ;
		tocout << std::setfile("file2.c", 4) << "Test output with filename:line" << std::endl ;
		tocout << "Test output without filename" << std::endl ;
		tocout << std::setfile("file3.c" , 8, 36) << "Test output with filename:line:col" << std::endl ;
	}

} ;

CPPUNIT_TEST_SUITE_REGISTRATION(AddOMongoDbStreamTest) ;
