/*
 * SafeQueue.hpp
 *
 *      Author: Iacopo Breschi
 */

#ifndef cern_vme_SafeQueue_hpp_INCLUDED
#define cern_vme_SafeQueue_hpp_INCLUDED

#include <queue>
#include <mutex>
#include <condition_variable>

// https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
template<class T>
struct SafeQueue
{
	SafeQueue() :
					queue_(),
					mut_(),
					cond_()
	{
	}
	~SafeQueue()
	{
	}

	void enqueue(T item)
	{
		std::lock_guard<std::mutex> lock(mut_);
		queue_.push(item);
		cond_.notify_one();
	}

	bool try_dequeue(T & item, std::chrono::milliseconds timeout)
	{
		std::unique_lock<std::mutex> lock(mut_);

		if (!cond_.wait_for(lock, timeout, [this]
		{	return !queue_.empty();})) return false;

		item = queue_.front();
		queue_.pop();
		return true;
	}

	T dequeue(void)
	{
		std::unique_lock<std::mutex> lock(mut_);
		while (queue_.empty())
		{
			cond_.wait(lock);
		}
		T item = queue_.front();
		queue_.pop();
		return item;
	}
	size_t size()
	{
		// TODO: needs guards?
		return queue_.size();
	}
private:
	std::queue<T> queue_;
	std::mutex mut_;
	std::condition_variable cond_;
};

#endif /* cern_vme_SafeQueue_hpp_INCLUDED */
