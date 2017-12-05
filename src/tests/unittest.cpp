#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapBufferTests
#include "../GapBuffer.cpp"
#include <string>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(InsertTest)
{
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  BOOST_CHECK(gp.printBuffer() == "abcd");
}

BOOST_AUTO_TEST_CASE(BackSpaceTest)
{
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  gp.Backspace();
  gp.Backspace();
  BOOST_CHECK(gp.printBuffer() == "ab");
}

BOOST_AUTO_TEST_CASE(BackSpaceEdgeTest)
{
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  gp.Backspace();
  gp.Backspace();
  gp.Backspace();
  gp.Backspace();
  gp.Backspace();
  BOOST_CHECK(gp.printBuffer() == "");
}

BOOST_AUTO_TEST_CASE(DeleteTest)
{
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  gp.MoveGap(1);
  gp.Delete();
  BOOST_CHECK(gp.printBuffer() == "acd");
}
/*BOOST_AUTO_TEST_CASE(MoveBackWardAndInsert)
{
  GapBuffer gapB(10);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  gapB.MoveGap(1);
  gapB.Insert('E');
  //std::cout<<gp.printBuffer();
  BOOST_CHECK(gapB.printBuffer() == "aEbcd");
  }*/
