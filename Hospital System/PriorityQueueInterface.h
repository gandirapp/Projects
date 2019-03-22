#ifndef PRIORITYQUEUEINTERFACE_H_INCLUDED
#define PRIORITYQUEUEINTERFACE_H_INCLUDED

template<class ItemType>
class PriorityQueueInterface
{
public:
    /** Sees whether priority queue is empty.
	@return True if the priority queue is empty; otherwise false.
	**/
	virtual bool isEmpty() const = 0;

	/**  Adds  newEntry  to this priority queue.
	@param newEntry
	@post The heap contains a new node.
	@return True if the operation is successful; otherwise false.
	**/
	virtual bool add(const ItemType& newEntry) = 0;

	/**  Removes the entry with the highest priority from this priority queue.
	@return True if the operation is successful; otherwise false.
	**/
	virtual bool remove() = 0;

    /** @throw PrecondViolatedExcep if priority queue is empty. */
    virtual ItemType peek() const throw(PrecondViolatedExcep) = 0;
};
#endif // PRIORITYQUEUEINTERFACE_H_INCLUDED
