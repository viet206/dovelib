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
	int stat = TRUE;

	stat &= ( d1 == NIL );
	stat &= ( d2 == NIL );
	if (stat) return FALSE;

	if ( d1->tag != d2->tag ) return TAG_NEQ;

	switch (d1->tag) {
		case INT:
			stat = ( d1->type.i == d2->type.i );
			break;
		case PTR:
			stat = ( d1->type.p == d2->type.p );
			break;
		case UINT:
			stat = ( d1->type.u == d2->type.u );
			break;
		case PTR_INT:
			stat = ( d1->type.int_p == d2->type.int_p );
			break;
		case PTR_UINT:
			stat = ( d1->type.uint_p == d2->type.uint_p );
			break;
		default:
			return FALSE;
	}
	return stat;
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

dyn_t** list_new(char* mt,uint_t mt_len,char* buf,uint_t len,uint_t blk_size,uint_t idx) {
	bool stat = FALSE;

	stat &= ( mt != NIL );
	stat &= ( buf != NIL );
	if (!stat) return NIL;

	stat &= ( len > 0 );
	stat &= ( mt_len > 0 );
	stat &= ( blk_size > 0 );
	stat &= ( idx > 0 );
	if (!stat) return (void*) ZERO_SIZE;

	stat &= ( mt_len >= idx * sizeof(void*) );
	stat &= ( len >= idx * blk_size );
	if (!stat) return (void*) NOT_ENO_MEM;

	dyn_t** l = (dyn_t**) mt;

	for ( uint_t i = 0 ; i <= idx ; i++ ) {
		l[i] =  (dyn_t*)((char*)buf + i * blk_size);
	}
	l[idx] = NIL;

	return l;
}
