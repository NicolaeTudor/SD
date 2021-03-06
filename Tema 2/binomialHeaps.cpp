#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>

using namespace std;

struct BinomialHeapNode {
	int key, degree;
	BinomialHeapNode * childrens, * siblings;
};

BinomialHeapNode* newBinomialHeapNode(int key)
{
	BinomialHeapNode *temp = new BinomialHeapNode;
	temp->key = key;
	temp->degree = 0;
	temp->childrens = temp->siblings = NULL;

	return temp;
}

BinomialHeapNode * mergeBinomialTrees(BinomialHeapNode *Tree1, BinomialHeapNode *Tree2)
{
	if (Tree1->key > Tree2->key)
	{
		swap(Tree1, Tree2);
	}

	Tree2->siblings = Tree1->childrens;
	Tree1->childrens = Tree2;
	Tree1->degree++;

	return Tree1;
}

list<BinomialHeapNode *> adjustBinomialHeap(list<BinomialHeapNode *> _heap)
{
	list<BinomialHeapNode *>::iterator atTree1, atTree2, atTree3;
	atTree1 = atTree2 = atTree3 = _heap.begin();
	if (_heap.size() <= 1)
		return _heap;
	if (_heap.size() == 2)
	{
		atTree2 = atTree1;
		atTree2++;
		atTree3 = _heap.end();
	}
	else
	{
		atTree2++;
		atTree3 = atTree2;
		atTree3++;
	}
	while (atTree2 != _heap.end())
	{
		if ((*atTree1)->degree == (*atTree2)->degree && (atTree3 == _heap.end() || (*atTree2)->degree != (*atTree3)->degree))
		{
			(*atTree1) = mergeBinomialTrees((*atTree1), (*atTree2));
			atTree2 = _heap.erase(atTree2);
			if(atTree3 != _heap.end())
				atTree3++;
		}
		else
		{
			if (atTree1 != _heap.end())
			{
				atTree1++;
				if (atTree2 != _heap.end())
				{
					atTree2++;
					if (atTree3 != _heap.end())
						atTree3++;
				}
			}
		}
	}

	return _heap;
}

list<BinomialHeapNode *> unionBinomialHeaps(list<BinomialHeapNode *> source1, list<BinomialHeapNode *> source2)
{
	list<BinomialHeapNode *> target;

	list<BinomialHeapNode *>::iterator atTree1 = source1.begin();
	list<BinomialHeapNode *>::iterator atTree2 = source2.begin();

	while (atTree1 != source1.end() && atTree2 != source2.end())
	{
		if ((*atTree1)->degree <= (*atTree2)->degree)
		{
			target.push_back(*atTree1);
			atTree1++;
		}
		else
		{
			target.push_back(*atTree2);
			atTree2++;
		}
	}

	while (atTree1 != source1.end())
	{
		target.push_back(*atTree1);
		atTree1++;
	}

	while (atTree2 != source2.end())
	{
		target.push_back(*atTree2);
		atTree2++;
	}

	return adjustBinomialHeap(target);
}

list<BinomialHeapNode*> insertATreeInHeap(list<BinomialHeapNode*> _heap, BinomialHeapNode *tree)
{
	list<BinomialHeapNode*> temp;

	temp.push_back(tree);
	temp = unionBinomialHeaps(_heap, temp);

	return temp;
}

list<BinomialHeapNode*> insert(list<BinomialHeapNode*> _head, int key)
{
	BinomialHeapNode *temp = newBinomialHeapNode(key);
	return insertATreeInHeap(_head, temp);
}

BinomialHeapNode * getMin(list<BinomialHeapNode*> _heap)
{
	list<BinomialHeapNode *>::iterator atTree = _heap.begin();
	if (atTree == _heap.end())
		return 0;
	BinomialHeapNode * min = (*atTree);
	while (atTree != _heap.end())
	{
		if ((*atTree)->key < min->key)
			min = (*atTree);

		atTree++;
	}

	return min;
}

list<BinomialHeapNode*> removeTreeReturnChildrens(BinomialHeapNode* tree)
{
	list<BinomialHeapNode *> temp;
	BinomialHeapNode * child = tree->childrens;
	BinomialHeapNode * currentChild;

	while (child)
	{
		currentChild = child;
		child = child->siblings;
		currentChild->siblings = NULL;
		temp.push_front(currentChild);
	}

	tree->childrens = NULL;
	delete tree;
	return temp;
}

list<BinomialHeapNode*> extractMin(list<BinomialHeapNode*> _heap)
{
	BinomialHeapNode *temp = getMin(_heap);
	list<BinomialHeapNode*> newHeap;
	list<BinomialHeapNode*> removedTreeChildrens = removeTreeReturnChildrens(temp);

	list<BinomialHeapNode *>::iterator atTree = _heap.begin();

	while (atTree != _heap.end())
	{
		if ((*atTree) != temp)
		{
			newHeap.push_back(*atTree);
		}
		atTree++;
	}
	
	return unionBinomialHeaps(newHeap, removedTreeChildrens);
}

void freeMemory(list<BinomialHeapNode*> _head)
{
	while (_head.size() > 0)
	{
		_head = extractMin(_head);
	}
}

int main()
{
	list<BinomialHeapNode *> myHeap;

	myHeap = insert(myHeap, 100);
	myHeap = insert(myHeap, 20);
	myHeap = insert(myHeap, 30);
	myHeap = insert(myHeap, 40);
	myHeap = insert(myHeap, 10);
	myHeap = insert(myHeap, 20);
	myHeap = insert(myHeap, 30);
	myHeap = insert(myHeap, 40);
	myHeap = insert(myHeap, 10);
	myHeap = insert(myHeap, 20);
	myHeap = insert(myHeap, 30);
	myHeap = insert(myHeap, 40);
	myHeap = insert(myHeap, 10);
	myHeap = insert(myHeap, 20);
	myHeap = insert(myHeap, 30);
	myHeap = insert(myHeap, 40);
	myHeap = insert(myHeap, 2);
	myHeap = insert(myHeap, 20);
	myHeap = insert(myHeap, 30);
	myHeap = insert(myHeap, 40);
	myHeap = insert(myHeap, 10);
	myHeap = insert(myHeap, 20);
	myHeap = insert(myHeap, 1);
	myHeap = insert(myHeap, 40);
	myHeap = insert(myHeap, 10);
	myHeap = insert(myHeap, 20);

	cout << getMin(myHeap)->key;
	myHeap = extractMin(myHeap);

	freeMemory(myHeap);
    return 0;
}

