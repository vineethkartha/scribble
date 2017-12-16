#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapBufferOperations
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
  gp.Insert('c');
  gp.Insert('d');
  gp.MoveGap(2);
  gp.Backspace();
  BOOST_CHECK(gp.printBuffer() == "acd");
}

BOOST_AUTO_TEST_CASE(BackSpaceEdgeTest)
{
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  BOOST_CHECK(gp.printBuffer() == "abcd");
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
  BOOST_CHECK(gp.printBuffer() == "abcd");
  gp.MoveGap(1);
  gp.Delete();
  BOOST_CHECK(gp.printBuffer() == "acd");
}
BOOST_AUTO_TEST_CASE(MoveAndInsert)
{
  GapBuffer gapB(10);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  gapB.MoveGap(3);
  gapB.MoveGap(2);
  gapB.Insert('E');
  BOOST_CHECK(gapB.printBuffer() == "abEcd");
  /*gapB.MoveGap(8);
  gapB.Insert('F');
  BOOST_CHECK(gapB.printBuffer() == "abEFcd");
  gapB.MoveGap(9);
  gapB.Insert('G');*/
  //std::cout<<gapB.printBuffer();
  //BOOST_CHECK(gapB.printBuffer() == "abEFcGd");  
}

BOOST_AUTO_TEST_CASE(ResizeAndInsert)
{
  GapBuffer gapB(2);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  gapB.MoveGap(2);
  gapB.Insert('E');
  BOOST_CHECK(gapB.printBuffer() == "abEcd");
}

BOOST_AUTO_TEST_CASE(FillDeleteAndInsert)
{
  GapBuffer gapB(2);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  gapB.MoveGap(2);
  gapB.Delete();
  BOOST_CHECK(gapB.printBuffer() == "abd");
  gapB.Insert('E');
  BOOST_CHECK(gapB.printBuffer() == "abEd");
}
