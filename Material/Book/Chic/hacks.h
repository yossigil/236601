#import <cstdint>
/**
 * Some hacks to make the code look like pseudo code to be included in a book
 * describing the project 
 */
#define perspective(...) struct{__VA_ARGS__;};
#define	returns(x) const {return x;}
#define representation union
#define define(...) enum{__VA_ARGS__};
#define function
#define property inline
#define procedure void
#define construct
#define destruct ~
#define by(...) :__VA_ARGS__{}
#define Var auto

#define Value const auto
#define Variable auto 

#define collaterally(x,y) ((x),(y),0)

#define assert(x) ( (x) ?  1 : 0 )

#define array(name,type,min,max) \
    static type buffer##__LINE__[(max)-(min)+1]; \
    static type *const name = buffer##__LINE__ - min;
#define let static
typedef const char *const String;

#ifdef WORK_AROUND
typedef int64_t W; // A full word of  32 bits; two half words
typedef int32_t H; // Half a word including 16 bits.
#else
typedef int32_t W;
typedef int16_t H;
#endif
typedef int8_t byte; // A byte 
typedef long long int Integer; // A byte 

static inline H size(String s) { for (H $ = 0;; ++$) if (s[$] == '\0') return $ + 1; }
template<typename T> T Return(T x, ...) { return x; }
