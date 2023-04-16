#ifndef HEADER_gubg_thread_Pool_hpp_ALREADY_INCLUDED
#define HEADER_gubg_thread_Pool_hpp_ALREADY_INCLUDED

#include <gubg/debug.hpp>

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

namespace gubg { namespace thread {

    template<typename Argument>
    class Pool
    {
    public:
        template<typename Ftor>
        Pool(unsigned int worker_count, Ftor &&ftor)
            : ftor_(ftor)
        {
            S("");
            for (auto ix = 0u; ix < worker_count; ++ix)
                workers_.emplace_back(*this);
        }
        ~Pool()
        {
            {
                Lock lock{queue_mutex_};
                const auto sz = size();
                for (auto ix = 0u; ix < sz; ++ix)
                    queue_.emplace_back(std::nullopt);
            }
            cv_.notify_all();
        }

        unsigned int size() const { return workers_.size(); }

        void push_one(Argument arg)
        {
            S("");
            {
                Lock lock{queue_mutex_};
                queue_.emplace_back(arg);
            }
            cv_.notify_one();
        }

        template<typename Arguments>
        void push_many(const Arguments &args)
        {
            S("");
            {
                Lock lock{queue_mutex_};
                for (const auto &arg: args)
                    queue_.emplace_back(arg);
            }
            cv_.notify_all();
        }

    private:
        using MyPool = Pool<Argument>;
        using Mutex = std::mutex;
        using Lock = std::unique_lock<Mutex>;
        using Argument_opt = std::optional<Argument>;

        class Worker
        {
        public:
            Worker(MyPool &pool)
                : pool_(pool), thread_(std::ref(*this)) {}
            ~Worker()
            {
                quit_ = true;
                thread_.join();
            }

            void operator()()
            {
                S("");
                for (bool stop = false; !stop;)
                {
                    Argument_opt arg_opt;
                    {
                        L("Waiting for data");
                        Lock lock{pool_.queue_mutex_};
                        pool_.cv_.wait(lock, [&]() {
                            if (pool_.queue_.empty()) return false;
                            arg_opt = pool_.queue_.back();
                            pool_.queue_.pop_back();
                            return true;
                        });
                    }

                    if (!arg_opt)
                        stop = true;
                    else
                    {
                        L("Processing ...");
                        pool_.ftor_(*arg_opt);
                        L("done");
                    }
                }
            }

        private:
            MyPool &pool_;
            std::atomic<bool> quit_ = false;
            std::thread thread_;
        };

        using Queue = std::vector<Argument_opt>;
        Queue queue_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;

        std::function<void(Argument)> ftor_;

        std::list<Worker> workers_;
    };

}} // namespace gubg::thread

#endif
