#include "pch.h"
#include "CppUnitTest.h"
#include"../software/test.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int n = 6;
			int a[6] = { 0,1,2,3,4,5 };
			int True = 15;
			Assert::AreEqual(True, Max(n, a));
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int n = 6;
			int a[6] = { -1,-3,-5,39, -7,9 };
			int True = 41;
			Assert::AreEqual(True, Max(n, a));
		}

	};
	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int n = 5;
			int a[5] = { -1,-2,-3,-4,-5 };
			int True = 0;
			Assert::AreEqual(True, Max(n, a));
		}
	};
	TEST_CLASS(UnitTest4)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int n = 8;
			int a[8] = { 6,-3,-2,7,-15,1,2,2 };
			int True = 8;
			Assert::AreEqual(True, Max(n, a));
		}
	};
	TEST_CLASS(UnitTest5)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int n = 6;
			int a[6] = { -2,11 ,-4, 13, -5, -2 };
			int True = 20;
			Assert::AreEqual(True, Max(n, a));
		}
	};
}
