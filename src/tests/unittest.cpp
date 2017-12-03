#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapBufferTests
#include "../GapBuffer.cpp"
#include <string>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(InsertToBuffer)
{
  GapBuffer gp(5);
  gp.addChar('a');
  gp.addChar('b');
  gp.addChar('c');
  gp.addChar('d');
  BOOST_CHECK(gp.printBuffer() == "abcd");
}

BOOST_AUTO_TEST_CASE(MoveBackWardAndInsert)
{
  GapBuffer gapB(10);
  gapB.addChar('a');
  gapB.addChar('b');
  gapB.addChar('c');
  gapB.addChar('d');
  gapB.MoveGap(1);
  gapB.addChar('E');
  //std::cout<<gp.printBuffer();
  BOOST_CHECK(gapB.printBuffer() == "aEbcd");
}
