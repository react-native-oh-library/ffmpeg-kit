//
// Created on 2025/1/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "ThreadPool.h"
#include "FFmpegSession.h"

// 私有化的有参构造函数
ThreadPool::ThreadPool(size_t threads) : m_stop(false)
{
    for (size_t i = 0; i < threads; i++) {
        // 初始化 threads 个线程，将其加入 workers 队列中
        m_workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->m_queue_mutex);
                    this->m_condition.wait(lock, [this] { return this->m_stop || !this->m_tasks.empty(); });
                    // 判断是否为空唤醒 或资源发生了竞争
                    if (this->m_stop && this->m_tasks.empty()) {
                        return;
                    }

                    // 获取队列首个任务
                    task = std::move(this->m_tasks.front());
                    this->m_tasks.pop();
                }
                // 运行线程
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        m_stop = true;
    }
    // 终止条件等待
    m_condition.notify_all();
    // 回收所有线程资源
    for (std::thread &worker : m_workers) {
        worker.join();
    }
}
