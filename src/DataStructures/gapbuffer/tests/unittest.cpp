#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapBufferOperations
#include "../GapBuffer.cpp"
#include <string>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(InsertTest) {
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  BOOST_CHECK(gp.getContentOfBuffer() == "abcd");
}


BOOST_AUTO_TEST_CASE(BackSpaceTest) {
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  gp.Backspace();
  gp.Backspace();
  BOOST_CHECK(gp.getContentOfBuffer() == "ab");
  gp.Insert('e');
  gp.Insert('f');
  gp.Backspace();
  BOOST_CHECK(gp.getContentOfBuffer() == "abe");
}

BOOST_AUTO_TEST_CASE(BackSpaceEdgeTest) {
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  BOOST_CHECK(gp.getContentOfBuffer() == "abcd");
  gp.Backspace();
  gp.Backspace();
  gp.Backspace();
  gp.Backspace();
  gp.Backspace();
  BOOST_CHECK(gp.getContentOfBuffer() == "");
}

BOOST_AUTO_TEST_CASE(DeleteTest) {
  GapBuffer gp(5);
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  BOOST_CHECK(gp.getContentOfBuffer() == "abcd");
  gp.MoveCursor(1);
  gp.Delete();
  BOOST_CHECK(gp.getContentOfBuffer() == "acd");
}

BOOST_AUTO_TEST_CASE(MoveAndInsert) {
  GapBuffer gapB(10);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  BOOST_CHECK(gapB.getContentOfBuffer() == "abcd");
  gapB.MoveCursor(3);
  BOOST_CHECK(gapB.getContentOfBuffer() == "abcd");
  gapB.MoveCursor(2);
  BOOST_CHECK(gapB.getContentOfBuffer() == "abcd");
  gapB.Insert('E');
  BOOST_CHECK(gapB.getContentOfBuffer() == "abEcd");
  gapB.MoveCursor(8);
  gapB.Insert('F');
  BOOST_CHECK(gapB.getContentOfBuffer() == "abEcFd");
  gapB.MoveCursor(9);
  gapB.Insert('G');
  BOOST_CHECK(gapB.getContentOfBuffer() == "abEcFdG");  
}

BOOST_AUTO_TEST_CASE(ResizeAndInsert) {
  GapBuffer gapB(2);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  gapB.MoveCursor(2);
  gapB.Insert('E');
  BOOST_CHECK(gapB.getContentOfBuffer() == "abEcd");
}

BOOST_AUTO_TEST_CASE(FillDeleteAndInsert) {
  GapBuffer gapB(2);
  gapB.Insert('a');
  gapB.Insert('b');
  gapB.Insert('c');
  gapB.Insert('d');
  gapB.MoveCursor(2);
  gapB.Delete();
  BOOST_CHECK(gapB.getContentOfBuffer() == "abd");
  gapB.Insert('E');
  BOOST_CHECK(gapB.getContentOfBuffer() == "abEd");
}
