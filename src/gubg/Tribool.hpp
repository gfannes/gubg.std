#ifndef HEADER_gubg_Tribool_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Tribool_hpp_ALREADY_INCLUDED

namespace gubg { 

    class Tribool
    {
    public:

        Tribool() {}
        Tribool(bool b): state_(b ? True : False) {}

        operator bool() const { return state_ == True; }
        Tribool operator!() const { return state_ == True ? False : (state_ == False ? True : Maybe); }

        bool is_true() const {return state_ == True;}
        bool is_false() const {return state_ == False;}
        bool is_maybe() const {return state_ == Maybe;}

        static Tribool maybe() {return Tribool{Maybe};}

    private:
        enum State {False, True, Maybe};

        Tribool(State state): state_(state) {}

        State state_ = False;
    };

} 

#endif
