#include <ncurses.h>

// We need to register a separate type for attributes, as several functions need
// to use pointers to attributes.
// In Carp, the pointer type Ptr takes an argument; if the value of this
// argument begins with a lowercase letter, it will be interpreted as a type
// parameter instead of a concrete type, so, we need to pass it a type that
// begins with a capital letter.
typedef attr_t Attribute;
// The comments above likewise apply to chtype and short, both of which are used
// throughout ncurses; for convenience we define counterparts that play well
// with Carp's compiler here.
typedef chtype Chtype;
typedef short Short;
typedef wchar_t Wchar;

#if NCURSES_WIDECHAR
typedef cchar_t Cchar;
#endif

Short NCurses_Short_from_MINUS_int(int x) {
  return (short)x;
}

// This function may seem redundant at first glance; why can't we just pass Ints
// directly? However, chtype is conditionally defined. On machines that don't
// use 64 bits for longs and pointers and 32 for int, it's defined as unsigned.
// On machines that do use 64bits, it's correctly assigned to a uint32.
//
// We provide the wrapper type and this conversion function to account for the
// rare case in which Carp's Int type doesn't correspond to the chtype.
//
// We could also just pass Carp's UInt32 type, but the cast is more resilient in
// the face of future changes or old versions which define chtype differently.
Chtype NCurses_Chtype_from_MINUS_int(int x) {
  return (chtype)x;
}

Attribute *NCurses_attr_ptr() {
  Attribute* attributes;
  return attributes;
}

int NCurses_width() {
    int row, col;
    getmaxyx(stdscr, row, col);
    return col;
}

int NCurses_height() {
    int row, col;
    getmaxyx(stdscr, row, col);
    return row;
}
