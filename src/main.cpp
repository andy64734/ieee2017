/*
 * main.cpp
 *
 *  Created on: Oct 13, 2017
 *      Author: andy
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

struct Link;
struct Node;

typedef shared_ptr<Link> LinkSP;
typedef shared_ptr<Node> NodeSP;

vector<NodeSP> nodes;
vector<LinkSP> globalLinks;

struct Link
{
public:
	NodeSP theNodes[2];
	bool active;
	Link(NodeSP first, NodeSP second)
	{
		this->active = true;
		theNodes[0] = first;
		theNodes[1] = second;
	}

	Link(Link *other)
	{
		this->active = other->active;
		this->theNodes[0] = other->theNodes[0];
		this->theNodes[1] = other->theNodes[1];
	}

	NodeSP getOtherNode(NodeSP origNode)
	{
		if (origNode == theNodes[0])
			return theNodes[1];
		if (origNode == theNodes[1])
			return theNodes[0];
		return NULL;
	}
};

struct Node
{
	int id;
	bool active;
	vector<LinkSP> links;
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
	for (vector<LinkSP>::iterator currLink = links.begin();
			currLink != links.end(); currLink++)
	{
		if((*currLink)->active)
		{
			linkCount++;
		}
	}
	return linkCount;
}

int main()
{
	stringstream ss;
	string firstLine;
	getline(cin, firstLine);
	ss << firstLine;
	int numGraphs;
	ss >> numGraphs;
	ss.str("");
	ss.clear();
	for (int graphNum = 0; graphNum < numGraphs; graphNum++)
	{
		// Read the next 2 lines in.
		string numStuffLine;
		getline(cin, numStuffLine);
		ss << numStuffLine;
		int numNodes, numLinks;
		cout << ss.str();
		ss >> numNodes;
		ss >> numLinks;

		ss.str("");
		ss.clear();
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
			nodes.push_back(NodeSP(new Node(nodeNum)));
		}
		// Now make the links, and hook them up toegether.
		ss << linkLine;
		for (int linkNum = 0; linkNum < numLinks; linkNum++)
		{
			int firstNum, secondNum;
			ss >> firstNum >> secondNum;
			NodeSP first = nodes[firstNum];
			NodeSP second = nodes[secondNum];
			LinkSP ourLink(new Link(first, second));
			globalLinks.push_back(ourLink);
			first->links.push_back(ourLink);
			second->links.push_back(ourLink);
		}

		for (int nodeNum = 0; nodeNum < numNodes; nodeNum++)
		{
			NodeSP nodePtr = nodes[nodeNum];
			if (!nodePtr->active)
			{
				continue;
			}
			while (nodePtr && nodePtr->activeLinks() <= 1)
			{
				nodePtr->active = false;
				Node *nextPtr = NULL;
				for (unsigned i = 0; i < nodePtr->links.size(); i++)
				{
					if (nodePtr->links[i]->active)
					{
						nodePtr->links[i]->active = false;
						nextPtr = nodePtr->links[i]->getOtherNode(nodePtr);
						break;
					}
				}
				nodePtr = nextPtr;
			}
		}
	}
	cout << "Hello world." << endl;
	return 0;
}

