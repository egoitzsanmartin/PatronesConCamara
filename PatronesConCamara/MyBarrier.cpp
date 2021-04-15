#include "MyBarrier.h"

MyBarrier::MyBarrier(int count)
		: thread_count(count)
		, counter(0)
		, waiting(0)
{}

void MyBarrier::wait()
{
	//fence mechanism
	std::unique_lock<std::mutex> lk(m);
	++counter;
	++waiting;
	cv.wait(lk, [&] {
		return counter >= thread_count; 
	});
	cv.notify_one();
	--waiting;
	if (waiting == 0)
	{
		//reset barrier
		counter = 0;
	}
	lk.unlock();
}
