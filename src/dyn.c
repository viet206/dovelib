#include "freestd.h"

dyn_t* dyn_new(char* buf,char* src,dyn_tag_t tag) {
	if ( buf == NIL || src == NIL ) return NIL;

	dyn_t* d = (dyn_t*) buf;
	d->tag = tag;

	switch (tag) {
		case INT:
			d->type.i = *((int*)src);
			break;
		case PTR:
			d->type.p = src;
			break;
		case UINT:
			d->type.u = *((unsigned int*)src);
			break;
	}
	return d;
}
