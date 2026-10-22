#include "dove.h"

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
			return (void*) TAG_NOT_FOUND;
	}
	return d;
}

/*
 *
 *
 *
 *
 *
*/

bool_t dyn_cmp(dyn_t* d1,dyn_t* d2) {
	if ( d1 == NIL || d2 == NIL ) return FALSE;
	if ( d1->tag != d2->tag ) return FALSE;

	switch (d1->tag) {
		case INT:
			return ( d1->type.i == d2->type.i );
		case PTR:
			return ( d1->type.p == d2->type.p );
		case UINT:
			return ( d1->type.u == d2->type.u );
		case PTR_INT:
			return ( d1->type.int_p == d2->type.int_p );
		case PTR_UINT:
			return ( d1->type.uint_p == d2->type.uint_p );
		default:
			return FALSE;
	}
	return FALSE;
}

/*
 *
 *
 *
 *
 *
*/

dyn_t* dyn_str(char* buf,char* s,uint_t range) {
	if ( buf == NIL || s == NIL || range == 0 ) return NIL;

	dyn_t* d = (dyn_t*) buf;
	uint_t a;

	d->tag = STR;
	a = compat_str_len(s,range);

	if ( a == 0 ) return NIL;

	d->type.str.len = a;
	d->type.str.p = (char*)buf + DYN_SIZE;

	fn_copy(d->type.str.p,s,a);

	return d;
}

list_t* list_new(char* mt,uint_t mt_len,uint_t idx) {

	bool_t stat = FALSE;

	stat &= ( mt == NIL );

	if (!stat) return NIL;

	stat &= ( 
