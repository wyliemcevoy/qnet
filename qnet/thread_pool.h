#pragma once
#include <mutex>
#include <thread>
#include <queue>

class ThreadPool
{
public:
	ThreadPool(int thread_count);
	~ThreadPool();

	void RequestStop();
	bool StopRequested();

	
	void QueueWork();
	int RequestTask();
	int QueueSize();

	// It is the callers responsiblity to only add tasks that can
	// be executed concurently.
	void AddTask();
	void WaitForTasksCompletion();

private:
	void join();


	const int thread_count_;

	std::mutex queue_access_;
	std::mutex stop_requested_mutex_;
	std::mutex tasks_completed_;
	std::condition_variable cond_;
	bool queued_tasks_completeted_;
	bool stop_requested_;


	std::vector<std::thread> threads_;
	std::queue<int> queue_;
	std::condition_variable work_available_;
};

