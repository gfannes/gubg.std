#ifndef HEADER_gubg_Signal_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Signal_hpp_ALREADY_INCLUDED

#include <functional>
#include <list>

namespace gubg { 

    template <typename... Args>
    class Signal
    {
    public:
        //Connects functions and lambdas
        template <typename Ftor>
        void connect(Ftor &&ftor)
        {
            slots_.emplace_back(ftor);
        }

        //Connects member functions
        template <typename Receiver>
        void connect(Receiver &receiver, void (Receiver::*member_function)(Args...))
        {
            Receiver *receiver_ptr = &receiver;
            connect([=](Args... args){ (receiver_ptr->*member_function)(args...); });
        }

        void emit(Args... args)
        {
            for (const auto &slot: slots_)
                slot(args...);
        }

    private:
        using Slot = std::function<void(Args...)>;
        using Slots = std::list<Slot>;
        Slots slots_;
    };

} 

#endif
