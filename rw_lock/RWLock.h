#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class RWLock {
public:
	RWLock();
	virtual ~RWLock();

	mutex counter_lock;
	unsigned int reader_count;
	unsigned int writer_count;
};

class RWLockSync:public RWLock {
public:
	RWLockSync();
	virtual ~RWLockSync();
	void rd_lock_sync();
	void rd_unlock();
	void wt_lock_sync();
	void wt_unlock();

	condition_variable cv;
};

class RWLockAsync:public RWLock {
public:
	RWLockAsync();
	virtual ~RWLockAsync();
	bool rd_lock_async();
	void rd_unlock();
	bool wt_lock_async();
	void wt_unlock();
};

