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
	void join();

private:
	const int thread_count_;
	std::mutex stop_requested_mutex_;
	//std::mutex tasks_completed_;
	//std::condition_variable cond_;
	//bool queued_tasks_completeted_;
	bool stop_requested_;
	TaskQueue queue_;
	int stride_;
	int size_;
	std::vector<std::thread> threads_;
	//bool finished_adding_to_queue;

};

