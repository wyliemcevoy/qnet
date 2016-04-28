#include "thread_pool.h"

void thread_work(ThreadPool &pool, int foo[], int stride)
{
	while (!pool.StopRequested())
	{
		// Thread will block on pop from the queue
		int start = pool.GetStartIndex();

		for (int i = start; start < start + stride; i++)
		{
			foo[i] = foo[i] + 1;
		}

	}
}

ThreadPool::ThreadPool(int thread_count, int foo[], int size) : thread_count_(thread_count), stride_(1000), size_(size)
{
	threads_.reserve(thread_count_);

	for (int i = 0; i < thread_count_; i++)
	{
		threads_.push_back(std::thread(thread_work, foo, stride_));
	}

	// add to queue
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::QueueWork()
{
	for (int i = 0; i < size_; i += stride_)
	{
		queue_.push(i);
	}
}

void ThreadPool::RequestStop()
{
	std::lock_guard<std::mutex> lock(stop_requested_mutex_);
	stop_requested_ = true;
}

bool ThreadPool::StopRequested()
{
	std::lock_guard<std::mutex> lock(stop_requested_mutex_);
	return stop_requested_;
}

int ThreadPool::GetStartIndex()
{
	return queue_.pop();
}

