#include "thread_pool.h"
#include <iostream>

void thread_work(ThreadPool* pool)
{
	while (!pool->StopRequested())
	{
		// Thread will block on pop from the queue
		int start = pool->RequestTask();

		std::thread::id this_id = std::this_thread::get_id();
		std::cout << "\tThread " << this_id << " done with task." << std::endl;
	}

}

ThreadPool::ThreadPool(int thread_count) : thread_count_(thread_count)
{
	threads_.reserve(thread_count_);

	for (int i = 0; i < thread_count_; i++)
	{
		threads_.push_back(std::thread(thread_work, this));
	}
}

void ThreadPool::AddTask()
{
	int t = 0;
	{
		std::lock_guard<std::mutex> lock(queue_access_);
		queue_.push(t);
	}
	work_available_.notify_one();
}

void ThreadPool::WaitForTasksCompletion()
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::join()
{
	int i = 0;
	for (auto &a_thread : threads_)
	{
		std::cout << "Joining thread " << i << " ... ";
		i++;
		a_thread.join();
		std::cout << " join successful." << std::endl;
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

void ThreadPool::QueueWork()
{
}

int ThreadPool::RequestTask()
{
	
	if ((queue_.size() <= 1))
	{
		// We are now finished with all work in the queue, and should
		// no longer block the thread that pushed to the queue.
		std::lock_guard<std::mutex> guard(tasks_completed_);
		queued_tasks_completeted_ = true;
		cond_.notify_one();
	}
	
	int t;
	{
		std::unique_lock<std::mutex> lock(queue_access_);
		while (!stop_requested_ && queue_.empty()) {
			//cond_.wait(lock, [&queue_ = queue_] {return !queue_.empty(); });
			work_available_.wait(lock);
		}

		t = queue_.front();
		queue_.pop();
	}

	return t;
}

int ThreadPool::QueueSize()
{
	std::lock_guard<std::mutex> queue_guard(queue_access_);
	return queue_.size();
}

