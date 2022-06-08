#import  "S.h"
#import  "except.h"

#define PRODUCTION
#import  "mode.h"

/* Global memory layout; we use no dynamic allocation of the host language.
 * TODO: deal with memory exhausting */

namespace Pairs {
#ifdef WORK_AROUND
  define(M = (1 << 25))
#else
  define(M = (1 << 15) - 1)
#endif
  // Falls in the data segment;
  static Pair buffer[M];
  Pair *const pool = buffer - 1;
  static H remaining = M;
  extern H to_go() {
    return remaining;
  }

  Pair &get(H h) {
    return pool[h];
  }

  static H init() {
    for (H h = 1; h < M; ++h)
      pool[h].next = h + 1;
    pool[M].next = 0;
    return 1;
  }

  static H &next() {
    static H inner = init();
    return inner;
  }

  H allocate() {
    (remaining > 0 &&  next() > 0) ||  die(MEMORY_CONS);
    const H $ = next();
    remaining--, next() = pool[next()].next;
    return $;
  }

  H allocate(H car, H cdr) {
    H $ = allocate();
    pool[$].car = car;
    pool[$].cdr = cdr;
    return $;
  }

  void free(H h) { D(h, remaining);
    pool[h].next = next(), remaining++, next() = h;
  }
}

