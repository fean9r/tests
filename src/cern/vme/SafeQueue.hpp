/*
 * SafeQueue.hpp
 *
 *      Author: Iacopo Breschi
 */

#ifndef cern_vme_SafeQueue_hpp_INCLUDED
#define cern_vme_SafeQueue_hpp_INCLUDED

#include <queue>

// https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
template<class T>
struct SafeQueue
{
	SafeQueue() :
			queue_()
	{
		//empty constructor
	}
	~SafeQueue()
	{
	}

	void enqueue(T item)
	{
		// handle here the lock
		queue_.push(item);
	}

	T dequeue(void)
	{
		// handle here the lock
		T item = queue_.front();
		queue_.pop();
		return item;
	}
private:
	std::queue<T> queue_;
};

#endif /* cern_vme_SafeQueue_hpp_INCLUDED */
