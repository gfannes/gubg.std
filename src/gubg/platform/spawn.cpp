#include "gubg/platform/spawn.hpp"
#include "gubg/mss.hpp"
#include <cstdlib>
#include <cstdio>
#define GUBG_API_LINUX
#ifdef GUBG_API_LINUX
#include <unistd.h>
#endif

namespace gubg { namespace platform { 

    bool spawn(const std::string &command)
    {
        MSS_BEGIN(bool);
#ifdef GUBG_API_LINUX
        switch (::fork())
        {
            case -1:
                //Something went wrong
                MSS(false);
                break;
            case 0:
                //Child process
                /* std::freopen("/dev/null", "w", stderr); */
                /* std::freopen("/dev/null", "w", stdout); */
                /* execl("/bin/sh", "sh", "-c", command.c_str(), "&>", "/dev/null", (char *)0); */
                execl("/usr/bin/gvim", (char *)0);
                break;
            default:
                //Parent process, continue without waiting
                break;
        }
#else
        MSS(std::system(command.c_str()) == 0);
#endif
        MSS_END();
    }

} } 
