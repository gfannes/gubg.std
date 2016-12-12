#ifndef HEADER_gubg_debug_hpp_ALREADY_INCLUDED
#define HEADER_gubg_debug_hpp_ALREADY_INCLUDED

#include "gubg/macro/stream.hpp"
#include "gubg/macro/capture.hpp"
#include <iostream>

namespace gubg { namespace debug { 

    namespace details { 
        template <typename T>
            struct Level { static unsigned int value; };
        template <typename T>
            unsigned int Level<T>::value = 0;
    } 

    class Scope
    {
        public:
            Scope(std::ostream &os, const char *debug_ns, const char *func): os_(os), debug_ns_(debug_ns), func_(func)
            {
                if (do_log())
                {
                    stream() << ">> " << debug_ns_ << " => " << function_name() << std::endl;
                    ++details::Level<Scope>::value;
                }
            }
            ~Scope()
            {
                if (do_log())
                {
                    --details::Level<Scope>::value;
                    stream() << "<< " << debug_ns_ << " => " << function_name() << std::endl;
                }
            }

            bool do_log() const {return !!debug_ns_;}
            std::ostream &stream() {return os_ << std::string(2*details::Level<Scope>::value, ' ');}
            const char *function_name() const {return !!func_ ? func_ : "<no function name given>";}

        private:
            std::ostream &os_;
            const char *debug_ns_;
            const char *func_;
    };
} } 

#ifndef GUBG_DEBUG_LOG
#ifdef NDEBUG
#define GUBG_DEBUG_LOG 0
#else
#define GUBG_DEBUG_LOG 1
#endif
#endif

#if GUBG_DEBUG_LOG
#define S(debug_ns) gubg::debug::Scope l_gubg_debug_Scope(std::cout, debug_ns, __func__)
#define L(msg) do { \
    if (l_gubg_debug_Scope.do_log()) \
        l_gubg_debug_Scope.stream() << "   " << msg << std::endl; \
    } while (false)
#else
#define S(debug_ns)
#define L(msg)
#endif

#endif
