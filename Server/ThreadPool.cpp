#include "ThreadPool.h"

std::atomic<size_t> ThreadPool::next_thread_name(0);

// the constructor just launches some amount of workers
ThreadPool::ThreadPool(size_t threads)
    :   stop(false), thread_name(next_thread_name.fetch_add(1))
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(
                    [this]
        {
            for(;;)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock,
                                         [this]{ return this->stop || !this->tasks.empty(); });
                    if(this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                task();
            }
        }
        );
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}

size_t ThreadPool::getThreadName() const
{
    return thread_name;
}
