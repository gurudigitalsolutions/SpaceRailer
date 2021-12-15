#include "constant.h"

char getPathSeparator() {
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}