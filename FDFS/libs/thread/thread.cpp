#include <thread.h>

void *Thread::thread_proxy(void *args) {
	Thread *pThread = static_cast<Thread *>(args);
	pThread->run1();
	return NULL;
}

void *Thread::run1() {
	this->thread_state = THREAD_RUNNING;
	this->tid = pthread_self();
	this->run();

	this->thread_state = THREAD_EXIT;
	this->tid = 0;
	pthread_exit(NULL);
}

Thread::Thread() {
	this->tid = 0;
	this->thread_state = THREAD_NEW;
}

Thread::~Thread() {
	return;
}

bool Thread::start() {
	return pthread_create(&(this->tid), NULL, Thread::thread_proxy, this) == 0;
}

pthread_t Thread::get_thread_id() {
	return this->tid;
}

int Thread::get_thread_state() {
	return this->thread_state;
}

void Thread::join() {
	if (this->tid == 0) {
		return;
	}
	pthread_join(this->tid, NULL);
}
