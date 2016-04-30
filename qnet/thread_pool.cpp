#include "thread_pool.h"
#include <iostream>

void thread_work(ThreadPool* pool, int foo[], int stride)
{
	
	while (!pool->StopRequested())
	{
		// Thread will block on pop from the queue
		int start = pool->GetStartIndex();

		for (int i = start; i < start + stride; i++)
		{
			foo[i] = foo[i] + 1;
			std::cout << "sleeping" << std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(100));
		}
	}

}

ThreadPool::ThreadPool(int thread_count, int foo[], int size) : thread_count_(thread_count), stride_(100), size_(size)
{
	threads_.reserve(thread_count_);

	for (int i = 0; i < thread_count_; i++)
	{
		threads_.push_back(std::thread(thread_work, this, foo, stride_));
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::QueueWork()
{
	/*
	finished_adding_to_queue = false;
	queued_tasks_completeted_ = false;
	*/

	for (int i = 0; i < size_; i += stride_)
	{
		queue_.push(i);
	}
	/*
	finished_adding_to_queue = true;
	std::unique_lock<std::mutex> lock(tasks_completed_);
	cond_.wait(lock, [&] {return !queued_tasks_completeted_; });
	*/
}

void ThreadPool::join()
{

	for (auto &a_thread : threads_)
	{
		a_thread.join();
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
	/*
	if (finished_adding_to_queue && (queue_.size() <= 1))
	{
		// We are now finished with all work in the queue, and should
		// no longer block the thread that pushed to the queue.
	
		std::lock_guard<std::mutex> guard(tasks_completed_);
		queued_tasks_completeted_ = true;
		cond_.notify_one();
	}
	*/
	return queue_.pop();
}

