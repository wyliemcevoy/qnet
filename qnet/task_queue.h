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
		T t;
		{
			std::unique_lock<std::mutex> lock(mut_);
			while (! queue_.empty()) {
				//cond_.wait(lock, [&queue_ = queue_] {return !queue_.empty(); });
				cond_.wait(lock);
			}

			t = queue_.front();
			queue_.pop();
		}
		return t;

	}
	void push(const T& t)
	{
		{
			std::lock_guard<std::mutex> lock(mut_);
			queue_.push(t);
		}
		cond_.notify_one();
	}
	void push(T&& t)
	{
		{
			std::lock_guard<std::mutex> lock(mut_);
			queue_.push(t);
		}
		cond_.notify_one();
	}

private:
	std::queue<T> queue_;
	std::mutex mut_;
	std::condition_variable cond_;
};

