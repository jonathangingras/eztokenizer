#ifndef _CLEAN_H_
#define _CLEAN_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct clean_wrapper {
    int (*on_each)(char *unit, size_t len, void *data);
    int (*clean)(char **unit, size_t *len, void *data);
    void *data;
};

int on_each_with_cleans(char *unit, size_t len, void *clean_wrapper);

#ifdef __cplusplus
}
#endif

#endif
