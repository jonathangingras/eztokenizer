#include "clean.h"

int on_each_with_cleans(char *unit, size_t len, void *clean_wrapper) {
    struct clean_wrapper *wrapper;
    int err;

    wrapper = (struct clean_wrapper *)clean_wrapper;

    if ((err = wrapper->clean(&unit, &len, wrapper->data))) {
        return err;
    }

    return wrapper->on_each(unit, len, wrapper->data);
}
