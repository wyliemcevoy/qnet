#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>



class TaskQueue
{
public:

	int pop() {
		int t;
		{
			std::unique_lock<std::mutex> lock(mut_);
			while (queue_.empty()) {
				//cond_.wait(lock, [&queue_ = queue_] {return !queue_.empty(); });
				cond_.wait(lock);
			}

			t = queue_.front();
			queue_.pop();
		}
		return t;

	}
	void push(int t)
	{
		{
			std::lock_guard<std::mutex> lock(mut_);
			queue_.push(t);
		}
		cond_.notify_one();
	}
	/*
	int size()
	{
		int result;
		{
			std::lock_guard<std::mutex> guard(mut_);
			result = queue_.size();
		}
		return result;
	}
	*/
private:
	std::queue<int> queue_;
	std::mutex mut_;
	std::condition_variable cond_;
};

