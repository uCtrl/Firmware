#pragma once

#include "CriticalSection.h"

class LinkedList;

class Node
{
	friend class LinkedList;

	void * _DataPointer;
	Node * _PreviousNode;
	Node * _NextNode;

public:
	Node();
	Node(void * pointer);
	Node(void * pointer, Node * previous, Node * next);
	Node(const Node & node);

	void * GetData() { return _DataPointer; }
	Node * GetNext() { return _NextNode; }
	Node * GetPrevious() { return _PreviousNode; }

	void Remove();
};

class LinkedList
{
private:
	Node *_pFirstNode;
	Node *_pLastNode;

	int _Count;
protected:
	CriticalSection _CriticalSection;
	virtual void DeleteData(void * data) = 0;
	virtual bool Compare(void * data0, void * data1) = 0;

public:
	LinkedList(void);
	virtual ~LinkedList(void);

	void Add(void * pointer);
	void * Find(void * pointer);

	void Remove(void * pointer);
	Node * RemoveHead();
	void RemoveAll();

	int GetSize() { return _Count; }
	Node * GetHead() { return _pFirstNode; }
	Node * GetTail() { return _pLastNode; }
};

