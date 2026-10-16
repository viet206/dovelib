#include "nekocl.h"

uint_t str_len(byte_t src,uint_t range) {
    for ( int i = 0 ; i <= (int)range ; ++i ) {
        if ( src[i] == '\0' ) return i;
    }
    return 0;
}

dyn_t str_new(byte_t dst,byte_t src,uint_t range) {
    dyn_t d = (dyn_t) dst;
    d->uiv = str_len(src,range);
    buf_copy(d->rv,src,d->uiv);

    return d;
}