/* 
 * Implementation of RW lock problem using std C++ 11.
 * more portable than using pthread.
 * TODO, avoid readers starving writers.
 */
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
	friend class RWSyncLockReadScope;
	friend class RWSyncLockWriteScope;
private:
	void rd_lock_sync();
	void rd_unlock();
	void wt_lock_sync();
	void wt_unlock();

	condition_variable cv;
};

class RWSyncLockReadScope {
public:
	RWSyncLockReadScope(RWLockSync* sync_lock);
        virtual ~RWSyncLockReadScope();
private:
	RWLockSync* _sync_lock;
};

class RWSyncLockWriteScope {
public:
	RWSyncLockWriteScope(RWLockSync* sync_lock);
        virtual ~RWSyncLockWriteScope();
private:
	RWLockSync* _sync_lock;
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

//////////////////////////
RWSyncLockReadScope::RWSyncLockReadScope(RWLockSync* sync_lock)
{
	_sync_lock = sync_lock;
	if (_sync_lock) {
		_sync_lock->rd_lock_sync();
	}
}

RWSyncLockReadScope::~RWSyncLockReadScope()
{
	if (_sync_lock) {
		_sync_lock->rd_unlock();
	}
}

RWSyncLockWriteScope::RWSyncLockWriteScope(RWLockSync* sync_lock)
{
	_sync_lock = sync_lock;
	if (_sync_lock) {
		_sync_lock->wt_lock_sync();
	}
}

RWSyncLockWriteScope::~RWSyncLockWriteScope()
{
	if (_sync_lock) {
		_sync_lock->wt_unlock();
	}
}

