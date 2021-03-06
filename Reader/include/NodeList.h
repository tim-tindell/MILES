/*
 * Node.h
 *
 *  Created on: 2015-02-13
 *      Author: rtindell
 */
#ifndef NODELIST_H
#define NODELIST_H

#include <Node.h>
#include <string>


class NodeList{
 public:
	void NormalizeAll();
	void SortAll(bool up);
	std::string toString();
	std::string toString(int x);
	std::string toString(int begin, int end);
	Node list[10000];
	int nodeCount;
	void loadFromFile(std::string wifiFILE,std::string trajFILE);

       
};
#endif
