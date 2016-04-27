#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class TaskQueue
{
public:


	T pop() {
		{
			std::lock_guard<mutex> lock(mut_);
			cond_.wait(lock, [&] {return !queue_.empty()});
			auto t = queue.front();
			queue_.pop();
		}

		return t;
	}
	void push(const T& t)
	{
		{
			std::lock_guard<mutex> lock(mut_);
			queue_.push(t);
		}
		cond_.notify_one();
	}
	void push(T&& t)
	{
		{
			std::lock_guard<mutex> lock(mut_);
			queue_.push(t);
		}
		cond_.notify_one();
	}

private:
	std::queue<T> queue_;
	std::mutex mut_;
	std::condition_variable cond_;
};

