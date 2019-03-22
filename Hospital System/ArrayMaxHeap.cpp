//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */

#include "ArrayMaxHeap.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const{
    return (2 * nodeIndex) + 2;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(int nodeIndex) const{
    return (nodeIndex - 1) / 2;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const{
    if ((nodeIndex >= (itemCount / 2)) && (nodeIndex <= itemCount))
        return true;
    else
        return false;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int subTreeRootIndex){
	if (!isLeaf(subTreeRootIndex)){
        int largerChildIndex = 2 * subTreeRootIndex + 1;

        if ((itemCount % 2) != 0){
            int rightChildIndex = largerChildIndex + 1;
            if (items[rightChildIndex] >= items[largerChildIndex])
                largerChildIndex = rightChildIndex;
        }

        if (items[subTreeRootIndex] < items[largerChildIndex]){
            ItemType tempVariable = items[largerChildIndex];
            items[largerChildIndex] = items[subTreeRootIndex];
            items[subTreeRootIndex] = tempVariable;
            heapRebuild(largerChildIndex);
        }
	}
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);
   }  // end for
}  // end heapCreate

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY){
    items = new ItemType[maxItems];
    heapCreate();
}

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize)
{
   // Allocate the array
   items = new ItemType[2 * arraySize];

   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];

   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap(){
    clear();
	delete[]items;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const{
    if (itemCount == 0)
        return true;
    else
        return false;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const{
	return itemCount;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const{
	return static_cast<int>(log2(itemCount) + 1);
}

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("Attempted peek into an empty heap.");

   return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData){
	if (itemCount == maxItems)
		return false;

    items[itemCount] = newData;
    int newDataIndex = itemCount;
    bool inPlace = false;

    while ((newDataIndex >= 0) && !inPlace){
        int parentIndex = getParentIndex(newDataIndex);

        if (items[newDataIndex] <= items[parentIndex])
            inPlace = true;
        else{
            ItemType tempVariable = items[newDataIndex];
            items[newDataIndex] = items[parentIndex];
            items[parentIndex] = tempVariable;
            newDataIndex = parentIndex;
        }
    }
    itemCount++;
	return true;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove(){
	if (isEmpty())
		return false;

	items[0] = items[itemCount - 1];
	itemCount--;
	heapRebuild(0);
	return true;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear(){
	int tempCount = itemCount;
	for (int i = 0; i < tempCount; i++){
		remove();
	}
}
