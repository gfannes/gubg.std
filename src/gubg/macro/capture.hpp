#ifndef HEADER_gubg_macro_capture_hpp_ALREADY_INCLUDED
#define HEADER_gubg_macro_capture_hpp_ALREADY_INCLUDED

#ifdef C
#error C already defined
#endif

#define C(var) "{" #var ":" << var << "}"

#endif
