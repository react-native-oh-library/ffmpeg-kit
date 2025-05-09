/**
 * GUN License
 *
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
