#pragma once

#include <string>
#include <limits>
#include "List.h"

struct ListOfSmezh
{
	void newNode(string name)
	{
		for (unsigned int i = 0; i < allNodes.GetSize(); i++)
			if (allNodes[i]->name == name)
				throw exception("Error: an already existent node");
		allNodes.push_back(new Node(name));
	}

	void newPath(string sourceS, string stockS, float value)
	{
		unsigned int source = nameToIndex(sourceS);
		unsigned int stock = nameToIndex(stockS);
		if (source > allNodes.GetSize() - 1)
			throw exception("Index is too high");
		if (stock > allNodes.GetSize() - 1)
			throw exception("Index is too high");
		allNodes[source]->paths.push_back(new Path(stock, value));
	}

	void removeDot(unsigned int removal)
	{
		if (removal >= allNodes.GetSize())
			throw exception("Index is too high");
		for (unsigned int i = 0; i < allNodes.GetSize(); i++)
			for (unsigned int j = 0; j < allNodes[i]->paths.GetSize(); j++)
			{
				if (allNodes[i]->paths[j]->stock == removal)
				{
					allNodes[i]->paths.removeAt(j);
					j--;
				}
			}

		allNodes[removal]->paths.clear();
		allNodes.removeAt(removal);

		for (unsigned int i = 0; i < allNodes.GetSize(); i++) 
			for (unsigned int j = 0; j < allNodes[i]->paths.GetSize(); j++)
			{
				if (allNodes[i]->paths[j]->stock >= removal)
				{
					allNodes[i]->paths[j]->stock--;
				}
			}
	}

	void removeEdge(string sourceS, string stockS, float value)
	{
		unsigned int source = nameToIndex(sourceS);
		unsigned int stock = nameToIndex(stockS);
		for (unsigned int i = 0; i < allNodes[source]->paths.GetSize(); i++)
		{
			if ((allNodes[source]->paths[i]->stock == stock) && (allNodes[source]->paths[i]->value == value))
			{
				allNodes[source]->paths.removeAt(i);
				return;
			}
		}
		throw exception("Error: path doesn't exist");
	}

	void print()
	{
		for (unsigned int i = 0; i < allNodes.GetSize(); i++)
		{
			cout << allNodes[i]->name << " - ";
			for (unsigned int j = 0; j < allNodes[i]->paths.GetSize(); j++)
			{
				cout << allNodes[allNodes[i]->paths[j]->stock]->name;
				cout << " value: " << allNodes[i]->paths[j]->value << " ";
				if (j < allNodes[i]->paths.GetSize() - 1)
					cout << ", ";
				else
					cout << endl;
			}
			cout << endl;
		}
	}

	double algorhytm(string fromS, string toS)
	{
		struct box
		{
			unsigned int source;
			double summ;
			bool ended;

			box()
			{
				summ = numeric_limits<double>::infinity();
				source = numeric_limits<unsigned int>::infinity();
				ended = false;
			};
		};

		unsigned int from, to;
		from = nameToIndex(fromS);
		to = nameToIndex(toS);
		if (from > allNodes.GetSize() - 1 || to > allNodes.GetSize() - 1)
			throw exception("Index is too high");

		box* cycle = new box[allNodes.GetSize()];
		cycle[from].ended = true;
		cycle[from].summ = 0;
		bool progress = true;
		unsigned int last = from;
		while (progress == true)
		{
			progress = false;
			for (unsigned int i = 0; i < allNodes[last]->paths.GetSize(); i++)
			{
				float newPath = cycle[last].summ + allNodes[last]->paths[i]->value;
				float oldPath = cycle[allNodes[last]->paths[i]->stock].summ;
				unsigned int outOf = cycle[allNodes[last]->paths[i]->stock].source;
				if ((oldPath == -1) || (oldPath > newPath))
				{
					cycle[allNodes[last]->paths[i]->stock].summ = newPath;
					cycle[allNodes[last]->paths[i]->stock].source = last;
				}
			}

			double min = numeric_limits<double>::infinity();

			for (unsigned int i = 0; i < allNodes.GetSize(); i++)
			{
				if ((cycle[i].summ != -1) && (cycle[i].summ < min) && (cycle[i].ended == false))
				{
					last = i;
					min = cycle[i].summ;
					progress = true;
				}
			}
			if (progress == true)
				cycle[last].ended = true;
			else
				throw exception("Can't reach the end");
			if (cycle[to].ended == true)
			{
				string path;
				unsigned int reverseEnd = last;
				unsigned int reverseStart = 0 - 1;
				path.insert(0, allNodes[reverseEnd]->name);
				while (reverseStart != from)
				{
					path.insert(0, " | ");
					reverseStart = cycle[reverseEnd].source;
					path.insert(0, allNodes[reverseStart]->name);
					reverseEnd = reverseStart;
				}
				path += "  = ";
				cout << path;
				return cycle[to].summ;
			}
		}
	}

	bool contains(string name)
	{
		for (unsigned int i = 0; i < allNodes.GetSize(); ++i)
			if (allNodes[i]->name == name)
				return true;
		return false;
	}


private:

	unsigned int nameToIndex(string input)
	{
		unsigned int answer;
		bool success = false;
		for (unsigned int i = 0; i < allNodes.GetSize(); i++)
		{
			if (allNodes[i]->name == input)
			{
				answer = i;
				success = true;
				break;
			}
		}

		if (success == false)
			throw exception("Couldn't find such dot");
		return answer;
	}

	struct Path
	{
		unsigned int stock;
		double value;

		Path(unsigned int stock = NULL, unsigned int value = NULL)
		{
			this->stock = stock;
			this->value = value;
		}
	};
	
	struct Node
	{
		string name;
		List<Path*> paths;

		Node(string name = "")
		{
			this->name = name;
		}
	};

	List<Node*> allNodes;
};