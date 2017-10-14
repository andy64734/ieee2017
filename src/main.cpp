/*
 * main.cpp
 *
 *  Created on: Oct 13, 2017
 *      Author: andy
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Link;
struct Node;

vector<Node> nodes;
vector<Link> globalLinks;

struct Link
{
public:
	Node *theNodes[2];
	bool active;
	Link(Node &first, Node &second)
	{
		this->active = true;
		theNodes[0] = &first;
		theNodes[1] = &second;
	}
	Link(const Link &other)
	{
		this->active = other.active;
		this->theNodes[0] = other.theNodes[0];
		this->theNodes[1] = other.theNodes[1];
	}
};

struct Node
{
	int id;
	bool active;
	vector<Link> links;
	Node(int);
	~Node();
	int activeLinks();
};

Node :: Node(int id)
{
	this->active = true;
	this->id = id;
}

Node :: ~Node()
{

}

int Node :: activeLinks()
{
	int linkCount = 0;
	vector<int> myint;
	for (vector::iterator<Link> currLink = links.begin();
			currLink != links.end(); currLink++)
	{
		if(currLink->active)
		{
			linkCount++;
		}
	}
	return linkCount;
}

int main()
{
	int numGraphs;
	cin >> numGraphs;
	for (int graphNum = 0; graphNum < numGraphs; graphNum++)
	{
		// Read the next 2 lines in.
		string numStuffLine;
		getline(cin, numStuffLine);
		stringstream ss;
		ss << numStuffLine;
		int numNodes, numLinks;
		ss >> numNodes >> numLinks;

		ss.flush();
		string linkLine;
		getline(cin, linkLine);

		// Check if the number of links >= numNodes
		// If so, junk the next line and move on.
		if (numLinks >= numNodes)
		{
			cout << 1 << endl;
			string junk;
			getline(cin, junk);
			continue;
		}
		for (int nodeNum = 0; nodeNum < numNodes; nodeNum++)
		{
			nodes.push_back(Node(nodeNum));
		}
		// Now make the links, and hook them up toegether.
		ss << linkLine;
		for (int linkNum = 0; linkNum < numLinks; linkNum++)
		{
			int firstNum, secondNum;
			ss >> firstNum >> secondNum;
			Node &first = nodes[firstNum];
			Node &second = nodes[secondNum];
			globalLinks.push_back(Link(first, second));
			Link ourLink = globalLinks.back();
			first.links.push_back(ourLink);
			second.links.push_back(ourLink);
		}

		for (int nodeNum = 0; nodeNum < numNodes; nodeNum++)
		{
			Node *nodePtr;
			nodePtr = &nodes[nodeNum];
			while (nodePtr->links.size() <= 1)
			{
				nodePtr->active = false;
				nodePtr = nodePtr->links[0];
			}
		}
	}
	cout << "Hello world." << endl;
	return 0;
}

