#pragma once
#include "task_queue.h"
#include <mutex>
#include <thread>


class ThreadPool
{
public:
	ThreadPool(int thread_count, int foo[], int size);
	~ThreadPool();

	void RequestStop();
	bool StopRequested();
	int GetStartIndex();
	void QueueWork();

private:
	const int thread_count_;
	std::mutex stop_requested_mutex_;
	bool stop_requested_;
	TaskQueue<int> queue_;
	int stride_;
	int size_;
	std::vector<std::thread> threads_;
};

