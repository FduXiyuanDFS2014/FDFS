#ifndef __THREAD_H__
#define __THREAD_H__	1

#include <pthread.h>
#include <type.h>
#include <def.h>

typedef enum Thread_State {
	THREAD_EXIT		= -1,
	THREAD_NEW		= 0,
	THREAD_RUNNING	= 1
} Thread_State;

class Thread {

private:
	pthread_t tid;
	int thread_state;

	static void *thread_proxy(void *args);

	void *run1();

public:

	Thread();
	virtual ~Thread();

	virtual void run() = 0;

	bool start();

	pthread_t get_thread_id();
	int get_thread_state();

	void join();

};

#endif
