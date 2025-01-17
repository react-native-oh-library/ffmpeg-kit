//
// Created on 2025/1/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef OHOS_THREADPOOL_H
#define OHOS_THREADPOOL_H

#include <future>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <type_traits>
#include <thread>
// 初始设定10个线程
const size_t THREAD_POOL_THREAD_NUMBER = 10;

class ThreadPool {
public:
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    static ThreadPool &getInstance()
    {
        static ThreadPool instance(THREAD_POOL_THREAD_NUMBER);
        return instance;
    }
    ~ThreadPool();

    // 模版函数的声明和实现都要放在头文件中 否则会出现未链接错误
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&...args) -> std::future<typename std::invoke_result<F, Args...>::type>
    {
        using return_type = typename std::invoke_result<F, Args...>::type;

        // 创建任务 分别输入函数名和参数
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        // rets 是一个对象其中存储了未来任务执行结束后的结果
        std::future<return_type> rets = task->get_future();
        // 将绑定好的task任务加入线程池中
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            if (m_stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            m_tasks.emplace([task]() { (*task)(); });
        }
        // 随机唤醒一个线程
        m_condition.notify_one();
        return rets;
    }

private:
    ThreadPool(size_t threads);

    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_queue_mutex;
    std::condition_variable m_condition;
    bool m_stop;
};


#endif // OHOS_THREADPOOL_H
