#ifndef HEADER_gubg_thread_Semaphore_hpp_ALREADY_INCLUDED
#define HEADER_gubg_thread_Semaphore_hpp_ALREADY_INCLUDED

#include "gubg/debug.hpp"
#include <mutex>
#include <condition_variable>
#include <cassert>

namespace gubg { namespace thread { 

    class Semaphore
    {
        private:
            static constexpr const char *logns = "Semaphore";

        public:
            Semaphore(unsigned int max): max_(max) {}

            void take()
            {
                S(logns);
                std::unique_lock<Mutex> lock(mutex_);
                L(count_);
                assert(count_ <= max_);
                cv_.wait(lock, [&](){return count_ < max_;});
                ++count_;
            }

            void give()
            {
                S(logns);
                std::lock_guard<Mutex> lock(mutex_);
                assert(count_ <= max_);
                --count_;
                cv_.notify_one();
            }

        private:
            using Mutex = std::mutex;

            const unsigned int max_;
            unsigned int count_ = 0;
            Mutex mutex_;
            std::condition_variable cv_;
    };

} } 

#endif
