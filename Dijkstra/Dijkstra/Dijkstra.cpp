#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
	ifstream cin("minpath.in");
	ofstream cout("minpath.out");

	int numOfVertex;
	int numOfEdges;

	cin >> numOfVertex;
	cin >> numOfEdges;

	vector <pair <int, int>> edges;
	vector <int> edgesLength;

	int firstVertex;
	int secondVertex;

	cin >> firstVertex;
	cin >> secondVertex;

	for (int i = 0; i < numOfEdges; i++)
	{
		int currentVertexOne;
		int currentVertexTwo;
		int length;

		cin >> currentVertexOne;
		cin >> currentVertexTwo;
		cin >> length;

		edges.push_back(pair <int, int>(currentVertexOne, currentVertexTwo));
		edgesLength.push_back(length);
	}

	int* minPath = new int[numOfVertex];
	int* visitedVertex = new int[numOfVertex];

	for (int i = 0; i < numOfVertex; i++)
	{
		minPath[i] = 1000000;
		visitedVertex[i] = 0;
		if (i == firstVertex - 1)
			minPath[firstVertex - 1] = 0;
	}

	int minVert;
	int minWeigth;

	do
	{
		minVert = 1000001;
		minWeigth = 1000000;

		for (int i = 0; i < numOfVertex; i++)
		{
			if (visitedVertex[i] == 0 && minPath[i] < minWeigth)
			{
				minWeigth = minPath[i];
				minVert = i;
			}
		}

		if (minVert != 1000001)
		{
			for (int i = 0; i < numOfEdges; i++)
			{
				if (edges[i].first == minVert + 1)
				{
					int temp = minWeigth + edgesLength[i];

					if (temp < minPath[edges[i].second - 1])
					{
						minPath[edges[i].second - 1] = temp;
					}
				}
			}

			visitedVertex[minVert] = 1;
		}
	} while (minVert < 1000001);

	if (minPath[secondVertex - 1] == 1000000)
		cout << 0;
	else
		cout << minPath[secondVertex - 1] << "\n";

	delete[] visitedVertex;

	if (minPath[secondVertex - 1] != 1000000)
	{
		int* theShortestPath = new int[numOfVertex];

		theShortestPath[0] = secondVertex;

		secondVertex--;
		firstVertex--;

		int lastWeigth = minPath[secondVertex];

		int pos = 0;

		while (secondVertex != firstVertex)
		{
			for (int i = 0; i < numOfEdges; i++)
			{
				if (edges[i].second == secondVertex + 1)
				{
					int temp = lastWeigth - edgesLength[i];

					if (temp == minPath[edges[i].first - 1])
					{
						lastWeigth = temp;
						secondVertex = edges[i].first - 1;
						theShortestPath[pos + 1] = secondVertex + 1;
						pos++;
					}
				}
			}
		}

		for (int i = pos; i >= 0; i--)
			cout << theShortestPath[i] << " ";

		delete[] theShortestPath;
	}

	delete[] minPath;

	return 0;
}
