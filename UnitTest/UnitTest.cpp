#include "pch.h"
#include "CppUnitTest.h"
#include "Proga3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(newNode)
		{
			ListOfSmezh test;
			test.newNode("A"); 
			test.newNode("B");
			test.newNode("C");
			test.newNode("D");
			test.newNode("E");
			test.newPath("A", "B", 7);
			test.newPath("A", "C", 8);
			test.newPath("A", "D", 6);
			test.newPath("B", "C", 5);
			test.newPath("B", "E", 11);
			test.newPath("C", "D", 2);
			test.newPath("C", "E", 12);

			Assert::AreEqual(true, test.contains("E"));
			Assert::AreEqual(false, test.contains("E324234"));
			try
			{
				test.newNode("E");
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "Error: an already existent node");
			}
		}

		TEST_METHOD(algorhytm)
		{
			ListOfSmezh test;
			test.newNode("A");
			test.newNode("B");
			test.newNode("C");
			test.newNode("D");
			test.newNode("E");
			test.newPath("A", "B", 7);
			test.newPath("A", "C", 8);
			test.newPath("A", "D", 6);
			test.newPath("B", "C", 5);
			test.newPath("B", "E", 11);
			test.newPath("C", "D", 2);
			test.newPath("C", "E", 12);

			Assert::AreEqual(18.0, test.algorhytm("A", "E"));
			test.removeEdge("C", "E", 12);
			Assert::AreEqual(18.0, test.algorhytm("A", "E"));
			test.removeEdge("B", "E", 11);
			try
			{
				test.algorhytm("A", "E");
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "Can't reach the end");
			}
		}
	};
}