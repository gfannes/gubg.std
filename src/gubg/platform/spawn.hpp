#ifndef HEADER_gubg_platform_spawn_hpp_ALREADY_INCLUDED
#define HEADER_gubg_platform_spawn_hpp_ALREADY_INCLUDED

#include <string>
#include <sstream>

namespace gubg { namespace platform { 

    bool spawn(const std::string &command);

    namespace detail { 
            void add_option(std::ostringstream &oss) { }
        template <typename FirstOption, typename ...OptionsRest>
            void add_op(std::ostringstream &oss, FirstOption firstOption, OptionsRest... optionsRest)
            {
                oss << ' ' << firstOption;
                spawn(oss.str(), optionsRest...);
            }
    } 
    template <typename ...Options>
        bool spawn(const std::string &command, Options... options)
        {
            std::ostringstream oss;
            oss << command;
            detail::add_option(oss, options...);
            return spawn(oss.str());
        }

    //Basic command-line escaping
    enum class Quotes {Add};
    std::string escape_for_cli(const std::string &str, Quotes quotes);

} } 

#endif
