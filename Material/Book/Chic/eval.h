#import "S.h"
namespace Engine {
  extern S eval(S s); 
  extern S apply(S s, S args);
}
namespace Frame { bool mark(S alist); }
