#ifndef HEADER_gubg_thread_Pool2_hpp_ALREADY_INCLUDED
#define HEADER_gubg_thread_Pool2_hpp_ALREADY_INCLUDED

#include <gubg/mss.hpp>

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <vector>

namespace gubg { namespace thread {

    template<typename Job>
    class Pool2
    {
    public:
        ~Pool2()
        {
            S("Pool");
            clear();
        }

        void clear()
        {
            S("Pool");
            state_.store(State::Uninit, std::memory_order_release);
            state_.notify_all();
            for (auto &worker : workers_)
                worker.thread.join();
            assert(thread_count_.load(std::memory_order_acquire) == 0);
        }

        bool init(std::optional<unsigned int> worker_count, std::optional<unsigned int> input_queue_size = {}, std::optional<unsigned int> output_queue_size = {})
        {
            MSS_BEGIN(bool, "Pool");

            switch (state_.load(std::memory_order_acquire))
            {
                case State::Uninit:
                    break;

                case State::Idle:
                    clear();
                    break;

                case State::Running:
                {
                    MSS(false, std::cerr << "Error: cannot init() a thread.Pool that is running" << std::endl);
                }
                break;
            }

            state_.store(State::Idle, std::memory_order_release);
            state_.notify_all();

            workers_.clear();
            workers_.resize(worker_count.value_or(std::thread::hardware_concurrency()));

            if (workers_.empty())
            {
                // We will compute everything in the calling thread
            }
            else
            {
                for (auto &worker : workers_)
                {
                    worker.thread = std::thread{[&]() {
                        S("Thread");
                        thread_count_.fetch_add(1, std::memory_order_acq_rel);
                        for (bool quit = false; !quit;)
                        {
                            switch (state_.load(std::memory_order_acquire))
                            {
                                case State::Uninit:
                                    L("Quit");
                                    quit = true;
                                    break;
                                case State::Idle:
                                    idle_count_.fetch_add(1, std::memory_order_acq_rel);
                                    idle_count_.notify_one();
                                    L("Going to sleep");
                                    state_.wait(State::Idle, std::memory_order_acquire);
                                    L("Woke");
                                    idle_count_.fetch_sub(1, std::memory_order_acq_rel);
                                    break;
                                case State::Running:
                                {
                                    L("Run");
                                    Job job;
                                    {
                                        Lock lock{input_queue_.mutex};
                                        input_queue_.cv.wait(lock, [&]() { return !input_queue_.queue.empty(); });
                                        job = input_queue_.queue.front();
                                        input_queue_.queue.pop();
                                    }
                                    if (job())
                                    {
                                        L("Computed job");
                                        {
                                            Lock lock{output_queue_.mutex};
                                            output_queue_.queue.push(job);
                                        }
                                        output_queue_.cv.notify_one();
                                    }
                                }
                                break;
                            }
                        }
                        thread_count_.fetch_sub(1, std::memory_order_acq_rel);
                    }};
                }

                // Wait for all the threads to become idle
                for (unsigned int idle_count = 0; idle_count != workers_.size(); idle_count = idle_count_.load(std::memory_order_acquire))
                {
                    L(C(idle_count));
                    idle_count_.wait(idle_count, std::memory_order_acquire);
                }
            }

            auto clear_and_set = [](auto &queue_ex, auto max_size) {
                while (!queue_ex.queue.empty())
                    queue_ex.queue.pop();
                queue_ex.max_size = max_size;
            };
            clear_and_set(input_queue_, input_queue_size);
            clear_and_set(output_queue_, output_queue_size);

            MSS_END();
        }

        bool start()
        {
            MSS_BEGIN(bool, "Pool");
            MSS(state_ == State::Idle);
            state_.store(State::Running, std::memory_order_release);
            state_.notify_all();
            MSS_END();
        }

        bool push(const Job &job)
        {
            MSS_BEGIN(bool, "Pool");
            {
                Lock lock{input_queue_.mutex};
                input_queue_.queue.push(job);
            }
            input_queue_.cv.notify_one();
            MSS_END();
        }

        template<typename Ftor>
        bool pop(bool do_continue, const Ftor &ftor)
        {
            MSS_BEGIN(bool, "Pool");
            Job job;
            {
                Lock lock{output_queue_.mutex};
                output_queue_.cv.wait(lock, [&]() { return !output_queue_.queue.empty(); });
                job = output_queue_.queue.front();
                output_queue_.queue.pop();
            }
            ftor(job);
            MSS_END();
        }

        bool stop()
        {
            MSS_BEGIN(bool, "Pool");
            MSS(state_ == State::Running);
            state_.store(State::Idle, std::memory_order_release);
            state_.notify_all();
            MSS_END();
        }

    private:
        struct Worker
        {
            std::thread thread;
        };
        std::vector<Worker> workers_;

        std::atomic<unsigned int> thread_count_;
        std::atomic<unsigned int> idle_count_;

        using Mutex = std::mutex;
        using Lock = std::unique_lock<Mutex>;

        struct QueueEx
        {
            std::queue<Job> queue;
            std::optional<unsigned int> max_size;
            std::condition_variable cv;
            Mutex mutex;
        };

        QueueEx input_queue_;
        QueueEx output_queue_;

        enum class State
        {
            Uninit,
            Idle,
            Running,
        };
        std::atomic<State> state_ = State::Uninit;
    };

}} // namespace gubg::thread

#endif
