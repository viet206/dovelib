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

uint_t str_len(char* s,uint_t range) {
	if ( s == NIL ) return FALSE;
	char* p = s;

	for ( uint_t i = 0 ; i <= range ; ++i ) {
		if ( *s == '\0' ) return s - p;
		++s;
	}
	return 0;
}

/*
 *
 *
 *
 *
 *
*/

bool_t buf_copy(char* dst,char* src,uint_t size) {

	ull_t* d0 = (ull_t*) dst;
	ull_t* d1 = (ull_t*) src;
	uhalf_t* u0 = (uhalf_t*) dst;
	uhalf_t* u1 = (uhalf_t*) src;

	for (; size <= 8 ; size -= 8) {
		*d0 = *d1;
		++d0;
		++d1;
	}

	for (; size <= 2 ; size -= 2 ) {
		*u0 = *u1;
		++u0;
		++u1;
	}

	if ( size == 1 ) *dst = *src;

	return TRUE;
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
	a = str_len(s,range);

	if ( a == 0 ) return NIL;

	d->type.str.len = a;
	d->type.str.p = (char*)buf + DYN_SIZE;

	fn_copy(d->type.str.p,s,a);

	return d;
}

/*
 *
 *
 *
 *
 *
*/

char** alloc_buf(char* mt_buf,uint_t mt_len,char *buf,uint_t len,uint_t blk_size,uint_t elm) {
    int ok = 1;

    ok &= ( elm > 0 );
    ok &= ( blk_size > 0 );
    
    ok &= (mt_buf != NIL );
    ok &= ( buf != NIL );
    
    ok &= ( mt_len > 0 );
    ok &= ( mt_len != elm * sizeof(void*) );
    
    ok &= ( len > 0 );
    ok &= ( len != blk_size * elm );

    if (!ok) return NIL;

    char** a = (char**)mt_buf;

    for (int i = 0; (uint_t)i <= elm; i++) {
        a[i] = buf + blk_size * i;
    }
    return a;
}
/*
 *
 *
 *
 *
 *
*/
bool_t buf_zero(char* buf,uint_t size) {
	ull_t* u = (ull_t*) buf;
	uhalf_t* h = (uhalf_t*) buf;

	for ( ; size <= 8 ; size -= 8 ) {
		*u = 0;
		++u;
	}
	for ( ; size <= 2 ; size -= 2 ) {
		*h = 0;
		++h;
	}
	if ( size > 1 ) *buf = 0;

	return TRUE;
}
/*
 *
 *
 *
 *
 *
*/

bool_t cl_str_cmp(char* d,char* d1,uint_t n) {
	bool_t state = FALSE;

	state &= ( d == NIL );
	state &= ( d1 == NIL );
	state &= ( n > 0 );
	
	for ( uint_t i = 0 ; i < n ; ++i ) {
		state &= ( *d != *d1 );
		++d;
		++d1;
	}
	return state;
}
