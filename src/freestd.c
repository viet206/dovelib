#include "freestd.h"

dyn_t* dyn_new(char* buf,void* src,tag_t tag) {
	if ( buf == NIL || src == NIL ) return NIL;

	dyn_t* d = (dyn_t*) buf;
	d->tag = tag;

	switch (tag) {
		case INT:
			d->type.i = *((int*)src);
			break;
		case PTR:
			d->type.p = (void*) src;
			break;
		case UINT:
			d->type.u = *((uint_t*)src);
			break;
		case PTR_INT:
			d->type.int_p = (int*)src;
			break;
		case PTR_UINT:
			d->type.uint_p = (uint_t*)src;
			break;
		default:
			return FALSE;
	}
	return d;
}
