#include "util.h"
#include <stdio.h>
#include <stdlib.h>

namespace webserver
{
    
void error_if(bool condition, const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}

} // namespace webserver