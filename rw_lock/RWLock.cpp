#include <iostream>
#include <unistd.h>
#include "RWLock.h"
/* 
 * Implementation of RW lock problem using std C++ 11.
 * more portable than using pthread.
 *
 * Notice, need unlock w/o lock protection. (TODO)
 */

////////////////////////////////
RWLock::RWLock():
	reader_count(0),
	writer_count(0),
	counter_lock()
{
}

RWLock::~RWLock()
{
}

////////////////////////////////
RWLockSync::RWLockSync()
	:cv()
{
}

RWLockSync::~RWLockSync()
{
}

void RWLockSync::rd_lock_sync()
{
	std::unique_lock<std::mutex> lck(counter_lock);
	while (writer_count > 0) {
		cv.wait(lck);
	}
	reader_count++;
	lck.unlock();
}

void RWLockSync::rd_unlock()
{
	bool notify = false;
	std::unique_lock<std::mutex> lck(counter_lock);
	if (reader_count > 0) {
		reader_count--;
	}
	if (reader_count == 0) {
		notify = true;
	}
	lck.unlock();
	if (notify) {
		cv.notify_all();
	}
}

void RWLockSync::wt_lock_sync()
{
        std::unique_lock<std::mutex> lck(counter_lock);
        while (writer_count > 0 ||
	       reader_count > 0) {
                cv.wait(lck);
        }
        writer_count++;
	lck.unlock();
}

void RWLockSync::wt_unlock()
{       
	bool notify = false;
	std::unique_lock<std::mutex> lck(counter_lock);
        if (writer_count > 0) {
                writer_count--;
        }
        if (writer_count == 0) {
                notify = true;
        } 
	lck.unlock();
	if (notify) {
		cv.notify_all();
	}
}

////////////////////////////////
RWLockAsync::RWLockAsync()
{
}

RWLockAsync::~RWLockAsync()
{
}

bool RWLockAsync::rd_lock_async()
{
	bool locked = false;
	counter_lock.lock();
        if (writer_count == 0) {
        	reader_count++;
		locked = true;
	}
	counter_lock.unlock();
	return locked;
}

void RWLockAsync::rd_unlock()
{
	counter_lock.lock();
        if (reader_count > 0) {
                reader_count--;
        }
	counter_lock.unlock();
}

bool RWLockAsync::wt_lock_async()
{
	bool locked = false;
	counter_lock.lock();
        if (writer_count == 0 &&
            reader_count == 0) {
        	writer_count++;
		locked = true;
	}
	counter_lock.unlock();
	return locked;
}

void RWLockAsync::wt_unlock()
{
	counter_lock.lock();
        if (writer_count > 0) {
                writer_count--;
        }
	counter_lock.unlock();
}

//////////////////////////////////////
// Test code
//////////////////////////////////////
static RWLockSync my_sync_rw_lock;
static RWLockAsync my_async_rw_lock;
static mutex cout_lock;

void sync_thread_fn (unsigned int id)
{
	int i = 0;
	bool reader = ((id % 2) > 0);
	RWLockSync* rwlock = (RWLockSync*)&my_sync_rw_lock;
	cout_lock.lock();
	cout << "sync_thread_fn id " << id << ((reader)? " Reader ": " Writer ") << "runnning" << endl;
	cout_lock.unlock();
	while (i++ < 10) {
		if (reader) {
			rwlock->rd_lock_sync();
			sleep(1);
			cout_lock.lock();
			cout << "sync rd thread " << id << " sync locked, i = " << i << endl;
			cout << "sync rd thread " << id << " do read, i = " << i << endl;
			cout << "sync rd thread " << id << " sync unlocked, i = " << i << endl;
			cout_lock.unlock();
			rwlock->rd_unlock();
			sleep(1);
		} else {
			rwlock->wt_lock_sync();
			sleep(2);
			cout_lock.lock();
			cout << "sync wt thread " << id << " sync locked, i = " << i << endl;
			cout << "sync wt thread " << id << " do write, i = " << i << endl;
			cout << "sync wt thread " << id << " sync unlocked, i = " << i << endl;
			cout_lock.unlock();
			rwlock->wt_unlock();
			sleep(2);
		}
	}
}

void async_thread_fn (unsigned int id) 
{
        int i = 0;
        bool reader = ((id % 2) > 0); 
	RWLockAsync* rwlock = (RWLockAsync*)&my_async_rw_lock;
        while (i++ < 5) {
                if (reader) {
                        if (rwlock->rd_lock_async()) {
				cout_lock.lock();
                        	cout << "async rd thread " << id << " async locked, i = " << i << endl;
                        	cout << "async rd thread " << id << " do read, i = " << i << endl;
				cout_lock.unlock();
				sleep(1);
				cout_lock.lock();
                        	cout << "async rd thread " << id << " async unlocked, i = " << i << endl;
				cout_lock.unlock();
                        	rwlock->rd_unlock();
			} else {
				cout_lock.lock();
                        	cout << "async rd thread " << id << " async lock failed, i = " << i << endl;
				cout_lock.unlock();
			}
                } else {
                        if (rwlock->wt_lock_async()) {
				cout_lock.lock();
                        	cout << "async wt thread " << id << " async locked, i = " << i << endl;
                        	cout << "async wt thread " << id << " do write, i = " << i << endl;
				cout_lock.unlock();
				sleep(1);
				cout_lock.lock();
                        	cout << "async wt thread " << id << " async unlocked, i = " << i << endl;
				cout_lock.unlock();
                        	rwlock->wt_unlock();
			} else {
				cout_lock.lock();
                        	cout << "async wt thread " << id << " async lock failed, i = " << i << endl;
				cout_lock.unlock();
			}
                }   
        }   
}


int main()
{
	std::thread s1(sync_thread_fn, 1);
	std::thread s2(sync_thread_fn, 2);
	std::thread s3(sync_thread_fn, 3);
	std::thread s4(sync_thread_fn, 4);
	s1.join();
	s2.join();
	s3.join();
	s4.join();

	std::thread a1(async_thread_fn, 1);
	std::thread a2(async_thread_fn, 2);
	a1.join();
	a2.join();
	
	return 0;
}
