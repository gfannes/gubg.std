#include "catch.hpp"
#include "gubg/tmp/FindBaseByName.hpp"
#include "gubg/debug.hpp"
#include <string>
using namespace gubg::tmp;

namespace  { 
    const char *logns = "test";
} 

//Names that will be used to indicate the different published base classes
struct E_tag{};
struct T_tag{};
struct EC_tag{};
struct TC_tag{};
struct WTF_tag{};

//Hierarchy
struct CC
{
    typedef Null Pubs;
    CC(){S(logns);L("CC ctor");}
};
struct E: CC
{
    typedef TypeList<NameType<EC_tag, CC> > Pubs;
    E(){S(logns);L("E ctor");}
};
struct T: CC
{
    typedef TypeList<NameType<TC_tag, CC> > Pubs;
    T(){S(logns);L("T ctor");}
};
struct LL_: E, T
{
    typedef TypeList<NameType<E_tag, E>, TypeList<NameType<T_tag, T> > > Pubs;
    LL_(){S(logns);L("LL_ ctor");}
};

TEST_CASE("FindBaseByName tests", "[ut][tmp]")
{
    S(logns);
    L("We lookup recursively the type named \"E_tag\"");
    FindBaseByName<E_tag, LL_::Pubs>::Type e;

    L("We lookup recursively the type named \"EC_tag\"");
    FindBaseByName<EC_tag, LL_::Pubs>::Type et;

    L("We lookup recursively the type named \"WTF_tag\"");
    FindBaseByName<WTF_tag, LL_::Pubs>::Type wtf;
}
