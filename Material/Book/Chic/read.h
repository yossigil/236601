#import "S.h"
extern char *readln();     // Only function in production mode

#ifndef PRODUCTION             // Testing adds overhead, which should not be part of production
extern char *inject(String injection); // Replace standard input with this injection 
#endif // PRODUCTION
