#include "catch.hpp"
#include "gubg/pattern/SignalSlot.hpp"
#include "gubg/debug.hpp"
#include <string>
#include <sstream>

typedef const std::string & Msg;

class Model
{
    public:
        void setData(int i)
        {
            S("");
            std::ostringstream oss; oss << i;
            data_ = oss.str();
            signal.emit(data_);
        }
        gubg::pattern::Signal<Msg> signal;

    private:
        std::string data_;
};

class View
{
    public:
        View(): slot(*this) {}

        void process(Msg msg)
        {
            S("");L(C(this)C(msg));
        }
        gubg::pattern::Slot<View, Msg> slot;
};

TEST_CASE("gubg::pattern::SignalSlot", "[ut][signal]")
{
    Model model;
    View view1;
    model.signal.connect(view1.slot);
    {
        View view2;
        model.signal.connect(view2.slot);
        model.setData(42);
    }
    model.setData(42);
}
