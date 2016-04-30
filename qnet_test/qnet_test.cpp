// qnet_test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "neural_net.h"
#include "thread_pool.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <ctime>

std::mutex mut;
std::condition_variable cond_var;
std::string data;
bool ready = false;
bool processed = false;


void worker_thread()
{
	std::unique_lock<std::mutex> lock(mut);
	cond_var.wait(lock, [] { return ready; });

	std::cout << "worker thread is processing data\n";
	data += " after processing";

	processed = true;
	std::cout << "Worker thread signals data processing completed\n";

	lock.unlock();
	cond_var.notify_one();
}


int m()
{
	std::thread worker(worker_thread);

	data = "example data";

	{
		std::lock_guard<std::mutex> guard(mut);
		ready = true;
		std::cout << "main() signals data ready for processing\n";
	}

	cond_var.notify_one();

	{
		std::unique_lock<std::mutex> lock(mut);
		cond_var.wait(lock, [] {return processed;});
	}
	worker.join();
	std::cout << "back in main(), data = " << data << std::endl;

	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();
    return 0;
}


std::mutex mute;
std::condition_variable work_available;

const int foo_size = 10000;
int foo[foo_size];
int num_executions = 1;


void fill_foo()
{
	for (int i = 0; i < foo_size; i++)
	{
		foo[i] = i;
	}
}

void single_thread_work()
{
	for (int i = 0; i < foo_size; i++)
	{
		foo[i] = foo[i] + 1;
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}

void thread_work(int start_index, int end_index)
{
	for (int i = start_index; i <= end_index; i++)
	{
		foo[i] = foo[i] + 1;
	}
}


void multi_thread_work()
{
	std::thread one(thread_work, 0, 199999);
	std::thread two(thread_work, 200000, 399999);
	std::thread three(thread_work, 400000, 599999);
	std::thread four(thread_work, 600000, 799999);	
	std::thread five(thread_work, 800000, 999999);

	one.join();
	two.join();
	three.join();
	four.join();
	five.join();
}

int main()
{

	// Build foo array
	fill_foo();

	//start clock
	clock_t begin = clock();

	for (int i = 0; i < num_executions; i++)
	{
		single_thread_work();
	}

	clock_t end = clock();

	double single_elapsed_secs = double(end - begin) * 1000 / CLOCKS_PER_SEC;

	std::cout << "Single thread elapsed miliseconds : " << single_elapsed_secs << std::endl;


	fill_foo();

	ThreadPool pool(7,foo, foo_size);

	//start clock
	begin = clock();

	for (int i = 0; i < num_executions; i++)
	{
		pool.QueueWork();
	}

	

	end = clock();

	double multi_elapsed_secs = double(end - begin) * 1000 / CLOCKS_PER_SEC;

	std::cout << "5 thread elapsed miliseconds : " << multi_elapsed_secs << std::endl;

	double ratio = single_elapsed_secs / multi_elapsed_secs;
	std::cout << "\t" << ratio << " times as fast." << std::endl;

	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();
	
	pool.join();
	return 0;
}
