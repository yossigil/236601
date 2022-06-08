#import  "S.h"
#define PRODUCTION
#import  "mode.h"
#import  "except.h"


#ifndef PRODUCTION 
namespace Strings {
  extern H current;  
  extern String pool;  

  String dump() {
    std::ostringstream o;
    for (int c = current; c <= 0; c += strlen(pool+c) + 1)
      o << "\n\t P" << c << "(" << strlen(pool+c) << ")=" <<  pool + c;
    return strdup(o.str().c_str());
  }
}
#endif


namespace Strings { // Atoms are never freed in mini-lisp
  define(M = 4444); // We use a total of M + sizeof("NIL") (typically 4) bytes
  static struct { // Falls in the data segment; should be just before Pairs::buffer
    char buffer[M] = "BOTTOM";
    char nil[sizeof("NIL")] = "NIL";
  } data;
  char *buffer = data.buffer;
  const char *const nil = data.nil;
  const char *const pool = nil;
  H current = 0;
  char upper(char c) { return c < 'a' || c > 'z' ? c : c - 'a' + 'A'; }
  bool eq(const char *s1, const char *s2) {
    if (s1 == s2) return true;
    for (; upper(*s1) == upper(*s2); ++s1, ++s2)
      if (*s1 == '\0')
        return true;
    return false;
  }

  /** Allocation of a input string is by moving the pool pointer down and then
   * copying the input there. A bit of optimization saves some space by
   * refraining from allocating the same string twice; moreover, there is also
   * a minimal attempt to allow one string to be realizes the suffix of a
   * previously allocated string  */ 
  H allocate(String s) {
    M("Search:", s, size(s), dump());
    for (H $ = 0; $ >= current; --$) 
      if (eq(s, pool+$))
        return (M("Found:", s, $, pool+$)), $;
    const H n = size(s);
    current -= n;
    M("Allocate:", s, pool+current,  nil-pool);
    current < 0 || die(MEMORY_ATOM);
    pool + current >= buffer || die(MEMORY_ATOM);
    for (H h = 0; h < n; ++h) // Only case in code to change the pool 
      const_cast<char&>(pool[current + h]) = upper(s[h]);
    M("Return", s, pool + current, current,dump());
    return current;
  }
}
