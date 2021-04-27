#ifndef HEADER_gubg_thread_Pool_hpp_ALREADY_INCLUDED
#define HEADER_gubg_thread_Pool_hpp_ALREADY_INCLUDED

#include <thread>
#include <list>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <functional>

namespace gubg { namespace thread { 

    template <typename Argument>
    class Pool
    {
    public:
        template <typename Ftor>
        Pool(unsigned int worker_count, Ftor &&ftor): ftor_(ftor)
        {
            for (auto ix = 0u; ix < worker_count; ++ix)
                workers_.emplace_back(*this);
        }
        ~Pool()
        {
            const auto sz = size();
            Lock lock{queue_mutex_};
            for (auto ix = 0u; ix < sz; ++ix)
                queue_.emplace(std::nullopt);
            cv_.notify_all();
        }

        unsigned int size() const {return workers_.size();}

    private:
        using MyPool = Pool<Argument>;
        using Mutex = std::mutex;
        using Lock = std::unique_lock<Mutex>;
        using Argument_opt = std::optional<Argument>;

        class Worker
        {
        public:
            Worker(MyPool &pool): pool_(pool), thread_(std::ref(*this)) {}
            ~Worker()
            {
                quit_ = true;
                thread_.join();
            }

            void operator()()
            {
                for (bool stop = false; !stop;)
                {
                    Argument_opt arg_opt;
                    {
                        Lock lock{pool_.queue_mutex_};
                        pool_.cv_.wait(lock, [&](){
                                if (pool_.queue_.empty()) return false;
                                arg_opt = pool_.queue_.front();
                                pool_.queue_.pop();
                                return true;
                                });
                    }

                    if (!arg_opt)
                        stop = true;
                    else
                    {
                    }
                }
            }

        private:
            MyPool &pool_;
            volatile bool quit_ = false;
            std::thread thread_;
        };

        using Queue = std::queue<Argument_opt>;
        Queue queue_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;

        std::function<void (Argument)> ftor_;

        std::list<Worker> workers_;
    };

} } 

#endif
