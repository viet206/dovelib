#include "nekocl.h"

dyn_t dyn_new(byte_t dst,byte_t src,dyn_tag_t tag) {

    if ( dst == NIL && src == NIL ) return NIL;

    dyn_t dyn = (dyn_t) dst;
    dyn->tag = tag;

    switch(tag) {
	case INT_T:
		dyn->_int = *((int*)src);
		break;
	case PTR_T:
		dyn->p = src;
		break;
	case UINT_T:
		dyn->_uint = *((len_t*)src);
		break;
	default:
		return FALSE;
		break;
    }

    return dyn;
}
