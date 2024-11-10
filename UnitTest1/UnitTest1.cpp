#include "pch.h"
#include "CppUnitTest.h"
#include "../PDC_LAB8/source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestInitGraph)
		{
			initGraph();
			for (int i = 0; i < MAX_VERTICES; ++i) {
				Assert::IsFalse(visited[i]);
				Assert::AreEqual(0, dfsNumber[i]);
				for (int j = 0; j < MAX_VERTICES; ++j) {
					Assert::AreEqual(0, adjMatrix[i][j]);
				}
			}
		}

		TEST_METHOD(TestAddEdge)
		{
			initGraph();
			addEdge(0, 1);
			addEdge(1, 2);

			Assert::AreEqual(1, adjMatrix[0][1]);
			Assert::AreEqual(1, adjMatrix[1][0]);
			Assert::AreEqual(1, adjMatrix[1][2]);
			Assert::AreEqual(1, adjMatrix[2][1]);
			Assert::AreEqual(0, adjMatrix[0][2]);
		}

		TEST_METHOD(TestReadGraphFromFile)
		{
			initGraph();
			std::ofstream testFile("testGraph.txt");
			testFile << "0 1\n";
			testFile << "1 2\n";
			testFile << "2 0\n";
			testFile.close();

			readGraphFromFile("testGraph.txt");

			Assert::AreEqual(1, adjMatrix[0][1]);
			Assert::AreEqual(1, adjMatrix[1][0]);
			Assert::AreEqual(1, adjMatrix[1][2]);
			Assert::AreEqual(1, adjMatrix[2][1]);
			Assert::AreEqual(1, adjMatrix[2][0]);
			Assert::AreEqual(1, adjMatrix[0][2]);
		}

		TEST_METHOD(TestDepthFirstSearch)
		{
			initGraph();
			addEdge(0, 1);
			addEdge(1, 2);
			addEdge(2, 3);

			depthFirstSearch(0);

			Assert::AreEqual(1, dfsNumber[0]);
			Assert::AreEqual(2, dfsNumber[1]);
			Assert::AreEqual(3, dfsNumber[2]);
			Assert::AreEqual(4, dfsNumber[3]);

			Assert::IsTrue(visited[0]);
			Assert::IsTrue(visited[1]);
			Assert::IsTrue(visited[2]);
			Assert::IsTrue(visited[3]);
		}

		TEST_METHOD(TestDisconnectedGraphDFS)
		{
			initGraph();
			addEdge(0, 1);
			addEdge(2, 3);

			depthFirstSearch(0);

			Assert::IsTrue(visited[0]);
			Assert::IsTrue(visited[1]);
			Assert::AreEqual(1, dfsNumber[0]);
			Assert::AreEqual(2, dfsNumber[1]);

			Assert::IsFalse(visited[2]);
			Assert::IsFalse(visited[3]);
		}
	};
}
