#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;

};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*template<typename Key, typename Value>
void AVLNode<Key, Value>::setKey(const Key& key)
{
	mItem.first = key;
}*/

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	void zigZigRotationRight(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z);
	void zigZagRotationRight(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z);
	void zigZigRotationLeft(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z);
	void zigZagRotationLeft(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z);
	void updateHeight(AVLNode<Key, Value>* node);
	int getBalancedFactor(AVLNode<Key, Value>* node);
	AVLNode<Key,Value>* insertHelper(AVLNode<Key, Value>* node, const std::pair<Key, Value>& keyValuePair,AVLNode<Key, Value>* parent);
	AVLNode<Key, Value>* BSTremove(AVLNode<Key, Value>* node);
	void swapNodes(AVLNode<Key, Value>* node1, AVLNode<Key, Value>* node2);
	void fixBalance(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y, AVLNode<Key, Value>* Z, int bf);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(AVLNode<Key, Value>* node)
{
	int left = -1;
	int right = -1;
	if(node->getLeft() != NULL) left = node->getLeft()->getHeight();
	if(node->getRight() != NULL) right = node->getRight()->getHeight();
	node->setHeight(std::max(left,right)+1);
	// std::cerr << "Node: " << node->getValue();
	// std::cerr << "  Left: " << left;
	// std::cerr << "  Right: " << right;
	// std::cerr << "	Height: " << node->getHeight()<< std::endl;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::getBalancedFactor(AVLNode<Key, Value>* node)
{
	int left = -1;
	int right = -1;
	if(node->getLeft() != NULL) left = node->getLeft()->getHeight();
	if(node->getRight() != NULL) right = node->getRight()->getHeight();
	int diff = right - left;
	return diff;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::BSTremove(AVLNode<Key, Value>* temp)
{
	if(temp == NULL) return NULL; //Key Not Found, don't do anything

	AVLNode<Key,Value>* left = temp->getLeft();
	AVLNode<Key,Value>* right = temp->getRight();

	if((left == NULL && right == NULL))//Node has 0 children
	{
		if(temp == this->mRoot) //if only node left in tree is root
		{
			delete temp;
			this->mRoot = NULL;
			return NULL;
		}
		else
		{	
			if(temp->getParent()->getLeft() == temp) //temp is left child
			{
				temp->getParent()->setLeft(NULL);
			}
			else //temp is right child
			{
				temp->getParent()->setRight(NULL);
			}
			AVLNode<Key,Value>* temp2 = temp->getParent();
			delete temp;
			return temp2;
		}
	}
	else if(left == NULL && right != NULL)//Node has only right child
	{	
		swapNodes(temp,temp->getRight());
		return BSTremove(temp->getRight());
	}
	else if((left != NULL && right == NULL)) //Node only has left child
	{
		swapNodes(temp,temp->getLeft());
		return BSTremove(temp->getLeft());
	}
	else //Node has 2 children
	{
		AVLNode<Key,Value>* temp2 = temp->getRight();
		while(temp2->getLeft() != NULL)
		{
			temp2 = temp2->getLeft();
		} 
		swapNodes(temp, temp2);
		return BSTremove(temp2);
	}
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	// TODO
	AVLNode<Key,Value>* temp = static_cast<AVLNode<Key,Value>*>(this->findHelper(this->mRoot,key));
	if(temp == NULL) return; //NOT IN OUR MAP
	AVLNode<Key, Value>* parent = BSTremove(temp);
	int bf = 0;
	int oldHeight;
	int newHeight;
	while(parent != NULL)
	{	
			oldHeight = parent->getHeight();
			newHeight = oldHeight;
			updateHeight(parent);
			bf = getBalancedFactor(parent);
			if(bf < -1 || bf > 1) 
			{	 
				AVLNode<Key,Value>* Y = NULL;
				AVLNode<Key,Value>* X = NULL;

				if(parent->getLeft() == NULL) Y = parent->getRight();
				else if(parent->getRight() == NULL ) Y = parent->getLeft();
				else
				{
					if(parent->getRight()->getHeight() > parent->getLeft()->getHeight()) Y = parent->getRight();
					else Y = parent->getLeft();
				}

				if(Y->getLeft() == NULL) X = Y->getRight();
				else if(Y->getRight() == NULL) X = Y->getLeft();
				else
				{
					if(Y->getRight()->getHeight() > Y->getLeft()->getHeight()) X = Y->getRight();
					else X = Y->getLeft();
				}

				fixBalance(X,Y,parent,bf);

				if(parent != NULL) newHeight = parent->getParent()->getHeight();
				if(newHeight == oldHeight) break; //if height is same as old,then nothing above cares

				parent = parent->getParent()->getParent();
			}
			else parent = parent->getParent();

			
	}	
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	this->mRoot = insertHelper(static_cast<AVLNode<Key,Value>*>(this->mRoot),keyValuePair,NULL);
	AVLNode<Key,Value>* Z = static_cast<AVLNode<Key,Value>*>(this->findHelper(this->mRoot,keyValuePair.first));
	int bf = 0;
	bool imbalance = false;
	AVLNode<Key,Value>* X = NULL;
	AVLNode<Key,Value>* Y = NULL;

	while(Z != NULL) //update all the heights until you go past the root
	{
		updateHeight(Z);
		bf = getBalancedFactor(Z);
		if(bf > 1 || bf < -1) //found imbalance
		{
			imbalance = true;
			break;
		}

		X = Y;
		Y = Z;
		Z = Z->getParent();
	}

	if(imbalance) fixBalance(X,Y,Z,bf);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::fixBalance(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y, AVLNode<Key, Value>* Z, int bf)
{
	if(bf == 2)//imbalance on right side
		{
			if(Y->getRight() == X)//zigZigRight
			{
				zigZigRotationRight(X,Y,Z);
			}
			else //zigZagRight
			{
				zigZagRotationRight(X,Y,Z);
			}
		}
	else if(bf == (-2))//imbalance on left side
		{
			if(Y->getLeft() == X)//zigZigLeft
			{
				zigZigRotationLeft(X,Y,Z);
			}
			else //zigZagLeft
			{
				zigZagRotationLeft(X,Y,Z);
			}
		}
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/

template<typename Key, typename Value>
void AVLTree<Key, Value>::zigZigRotationRight(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z)
{
	bool ZisRoot = false;
	if(Z == this->mRoot )
	{
		ZisRoot = true;
	}

	AVLNode<Key,Value>* T1 = Y->getLeft(); 

	if(Z->getParent() != NULL)
	{
		if(Z->getParent()->getRight() == Z) Z->getParent()->setRight(Y);
		else Z->getParent()->setLeft(Y);
	}
	Y->setParent(Z->getParent());
	Z->setRight(T1);
	if(T1 != NULL) T1->setParent(Z);
	Y->setLeft(Z);
	Z->setParent(Y);

	if(ZisRoot) this->mRoot = Y;
	updateHeight(Z);
	updateHeight(X);
	updateHeight(Y);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::zigZagRotationRight(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z)
{

	bool ZisRoot = false;
	if(Z == this->mRoot )
	{
		ZisRoot = true;
	}

	AVLNode<Key,Value>* T1 = X->getLeft();
	AVLNode<Key,Value>* T2 = X->getRight();

	if(Z->getParent() != NULL)
	{
		if(Z->getParent()->getRight() == Z) Z->getParent()->setRight(X);
		else Z->getParent()->setLeft(X);
	}
	X->setParent(Z->getParent());
	Z->setRight(T1);
	if(T1 != NULL) T1->setParent(Z);
	Y->setLeft(T2);
	if(T2 != NULL) T2->setParent(Y);
	X->setLeft(Z);
	Z->setParent(X);
	X->setRight(Y);
	Y->setParent(X);

	if(ZisRoot) this->mRoot = X;
	updateHeight(Z);
	updateHeight(Y);
	updateHeight(X);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::zigZigRotationLeft(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z)
{
	bool ZisRoot = false;
	if(Z == this->mRoot)
	{
		ZisRoot = true;
	}

	AVLNode<Key,Value>* T2 = Y->getRight();

	if(Z->getParent() != NULL)
	{
		if(Z->getParent()->getRight() == Z) Z->getParent()->setRight(Y);
		else Z->getParent()->setLeft(Y);
	}
	Y->setParent(Z->getParent());
	Z->setLeft(T2);
	if(T2 != NULL) T2->setParent(Z);
	Y->setRight(Z);
	Z->setParent(Y);

	if(ZisRoot) this->mRoot = Y;

	updateHeight(Z);
	updateHeight(X);
	updateHeight(Y);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::zigZagRotationLeft(AVLNode<Key, Value>* X,AVLNode<Key, Value>* Y,AVLNode<Key, Value>* Z)
{

	bool ZisRoot = false;
	if(Z == this->mRoot )
	{
		ZisRoot = true;
	}

	AVLNode<Key,Value>* T1 = X->getLeft();
	AVLNode<Key,Value>* T2 = X->getRight();

	if(Z->getParent() != NULL)
	{
		if(Z->getParent()->getRight() == Z) Z->getParent()->setRight(X);
		else Z->getParent()->setLeft(X);
	}
	X->setParent(Z->getParent());
	Y->setRight(T1);
	if(T1 != NULL) T1->setParent(Y);
	Z->setLeft(T2);
	if(T2 != NULL) T2->setParent(Z);
	X->setLeft(Y);
	X->setRight(Z);
	Z->setParent(X);
	Y->setParent(X);


	if(ZisRoot) this->mRoot = X;

	updateHeight(Z);
	updateHeight(Y);
	updateHeight(X);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insertHelper(AVLNode<Key, Value>* node, const std::pair<Key, Value>& keyValuePair, AVLNode<Key, Value>* parent)
{
	if(node == NULL)
	{
		return new AVLNode<Key,Value>(keyValuePair.first,keyValuePair.second,parent);
	}
	else if(keyValuePair.first == node->getKey()) //replace old value with new one
	{
		node->setValue(keyValuePair.second);
	}
	else if(keyValuePair.first < node->getKey())
	{
		node->setLeft(insertHelper(node->getLeft(),keyValuePair,node));
	}
	else //if(keyValuePair.first > node->getKey())
	{
		node->setRight(insertHelper(node->getRight(),keyValuePair,node));
	}

	return node;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::swapNodes(AVLNode<Key, Value>* node1, AVLNode<Key, Value>* node2)
{
	// Key tempKey = node1->getKey();
	// Value tempValue = node1->getValue();
	// node1->setKey(node2->getKey());
	// node1->setValue(node2->getValue());
	// node2->setKey(tempKey);
	// node2->setValue(tempValue);

	Key& tempKey1 = node1->getKey();
	Key& tempKey2 = node2->getKey();
	Value tempValue = node1->getValue();
	tempKey1 = node2->getKey();
	tempKey2 = node1->getKey();
	node1->setValue(node2->getValue());
	node2->setValue(tempValue);
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif