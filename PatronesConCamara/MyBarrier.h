#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

#ifndef MY_BARRIER_H
#define MY_BARRIER_H

class MyBarrier
{
	public:
		MyBarrier(int count);
		void wait();

	private:
		std::mutex m;
		std::condition_variable cv;
		int counter;
		int waiting;
		int thread_count;
};

#endif
