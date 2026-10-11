#include "nekocl.h"

dyn_t dyn_new(byte_t dst,byte_t src,dyn_tag_t tag) {

    if ( dst == NIL && src == NIL ) return NIL;

    dyn_t dyn = (dyn_t) dst;
    dyn->tag = tag;

    switch (tag) {
        case INT_T:
            dyn->i = *((int*) src);
            break;
        case CHAR_T:
            dyn->c = *src;
            break;
        case PTR_T:
            dyn->p = src;
            break;
    }

    return dyn;
}