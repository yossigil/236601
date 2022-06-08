#import "S.h"
namespace Tokenizer {
  enum { undefined = 128, $};
  const char tokens[] = "()[].\'";
  extern void initialize(String);
  // Retrieve the next token: if non-positive, this is an atom (including NIL)
  // else it is a character as per the table above
  extern H next(); 
  extern H get(); 
  extern H unget(); 
  extern H peep();
}
extern bool exists(const char, String s);
extern int getParenthesesBalanceCounter();
