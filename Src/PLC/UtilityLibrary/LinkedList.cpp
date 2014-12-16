#include "LinkedList.h"

Node::Node()
{
	_DataPointer = NULL;
	_PreviousNode = NULL;
	_NextNode = NULL;
}

Node::Node(void * pointer)
{
	_DataPointer = pointer;
	_PreviousNode = NULL;
	_NextNode = NULL;
}

Node::Node(void * pointer, Node * previous, Node * next)
{
	_DataPointer = pointer;
	_PreviousNode = previous;
	if (previous != NULL)
	{
		previous->_NextNode = this;
	}
	_NextNode = next;
	if (next != NULL)
	{
		next->_PreviousNode = this;
	}
}

Node::Node(const Node & node)
{
	_DataPointer = node._DataPointer;
	_NextNode = node._NextNode;
	_PreviousNode = node._PreviousNode;
}

void Node::Remove()
{
	Node * previous = _PreviousNode;
	Node * next = _NextNode;

	if (previous != NULL)
	{
		previous->_NextNode = next;
	}
	if (next != NULL)
	{
		next->_PreviousNode = previous;
	}
}

LinkedList::LinkedList(void)
{
	_pFirstNode = NULL;
	_pLastNode = NULL;
	_Count = 0;
}


LinkedList::~LinkedList(void)
{
	RemoveAll();
}

void LinkedList::Add(void * pointer)
{
	_CriticalSection.Lock();
	_Count++;
	if (_pFirstNode == NULL)
	{
		//
		// This is the first node.
		//
		Node * node = new Node(pointer, NULL, NULL);
		_pFirstNode = node;
		_pLastNode = node;
	}
	else
	{
		Node * lastNode = (Node *) _pLastNode;
		Node * newNode = new Node(pointer, lastNode, NULL);
		_pLastNode = newNode;
	}
	_CriticalSection.UnLock();
}

Node * LinkedList::RemoveHead()
{
	Node * node = _pFirstNode;
	if (node != NULL)
	{
		_Count--;
		_pFirstNode = node->_NextNode;
		if (_pFirstNode != NULL)
		{
			_pFirstNode->_PreviousNode = NULL;
		}
	}
	else
	{
		_Count = 0;
	}

	
	return node;
}

void * LinkedList::Find(void * pointer)
{
	_CriticalSection.Lock();
	Node * node = (Node*)_pFirstNode;
	while(node != NULL)
	{
		if (this->Compare(node->_DataPointer, pointer) == true)
		{
			break;
		}
		node = node->_NextNode;
	}

	void * dataPointer = NULL;
	if (node != NULL)
	{
		dataPointer = node->_DataPointer;
	}
	
	_CriticalSection.UnLock();
	return dataPointer;
}

void LinkedList::Remove(void * pointer)
{
	if (pointer != NULL)
	{
		_CriticalSection.Lock();
		Node * node = (Node*)_pFirstNode;
		while(node != NULL)
		{
			if (this->Compare(node->_DataPointer, pointer) == true)
			{
				break;
			}
			node = node->_NextNode;
		}

		if (node != NULL)
		{
			_Count--;
			//
			// If there is no previous node then this must have been the first node
			//
			if (node->_PreviousNode == NULL)
			{
				_pFirstNode = node->_NextNode;
			}
			//
			// If there is no next node then this must have been the last node
			//
			if (node->_NextNode == NULL)
			{
				_pLastNode = node->_PreviousNode;
			}

			node->Remove();
			//
			// Call the free function of the poineter..
			//
			DeleteData(node->_DataPointer);
			node->_DataPointer = NULL;
			//
			// Free the node..
			//
			delete node;
		}
		_CriticalSection.UnLock();
	}
}

void LinkedList::RemoveAll()
{
	_CriticalSection.Lock();
	
	_Count = 0;
	Node * node = (Node*)_pFirstNode;
	while(node != NULL)
	{
		Node *next = node->_NextNode;
		DeleteData(node->_DataPointer);
		delete node;
		node = next;
	}
	_pFirstNode = NULL;
	_pLastNode = NULL;

	_CriticalSection.UnLock();
}

