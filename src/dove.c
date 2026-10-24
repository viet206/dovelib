#include "dove.h"

buf_t* new_buf(char* b,uint_t size) {
	if ( b == NIL ) return NIL;
	if ( size < 0 && size == 0 ) return ZERO_SIZE;

	buf_t* a = (buf_t*) b;
	a->size = size;

	return a;
}

dyn_t* dyn_new(buf_t* buf, void* src, dyn_tag tag) {
	if ( buf == NIL ) return NIL;
	if ( src == NIL ) return NIL;

        dyn_t* d = (dyn_t*) buf->d;
        d->tag = tag;
        switch (tag) {
                case INT:
                        d->i = *((int*)src);
                        break;
                case PTR:
                        d->_v = (void*) src;
                        break;
                case UINT:
                        d->u = *((uint_t*)src);
                        break;
                case PTR_INT:
                        d->_i = (int*)src;
                        break;
                case PTR_UINT:
                        d->_u = (uint_t*)src;
                        break;
                case STR:
                        break;
        }
        return d;
}

int dyn_cmp(dyn_t* d1,dyn_t* d2) {
        int stat = COMPAT_TRUE;

        stat &= ( d1 == NIL );
        stat &= ( d2 == NIL );
        if (stat) return PTR_NIL;

        if ( d1->tag != d2->tag ) return TAG_NEQ;

        switch (d1->tag) {
                case INT:
                        stat = ( d1->i == d2->i );
                        break;
                case PTR:
                        stat = ( d1->_v == d2->_v );
                        break;
                case UINT:
                        stat = ( d1->u == d2->u );
                        break;
                case PTR_INT:
                        stat = ( d1->_i == d2->_i );
                        break;
                case PTR_UINT:
                        stat = ( d1->_u == d2->_u );
                        break;
                case STR:
                        break;
        }
        return stat;
}

dyn_t* dyn_str(buf_t* buf, char* str, uint_t range) {
        if ( buf == NIL || str == NIL || range == 0 ) return NIL;

        dyn_t* d = (dyn_t*) buf->d;
        uint_t a;

        d->tag = STR;
        a = compat_str_len(str, range);

        if ( a == 0 ) return NIL;

        d->s.len = a;
        d->s.p = (char*)buf + DYN_SIZE;

        fn_copy(d->s.p, str, a);

        return d;
}

dyn_t** list_new(char* mt, uint_t mt_len, char* buf, uint_t len, uint_t blk_size, uint_t idx) {
        int stat = COMPAT_TRUE;

        stat &= ( mt != NIL );
        stat &= ( buf != NIL );
        if (!stat) return NIL;

        stat &= ( len > 0 );
        stat &= ( mt_len > 0 );
        stat &= ( blk_size > 0 );
        stat &= ( idx > 0 );
        if (!stat) return (void*) ENO_SIZE;

        stat &= ( mt_len >= idx * sizeof(void*) );
        stat &= ( len >= idx * blk_size );
        if (!stat) return (void*) ENO_MEM;

        dyn_t** l = (dyn_t**) mt;

        for ( uint_t i = 0 ; i <= idx ; i++ ) {
                l[i] = (dyn_t*)((char*)buf + i * blk_size);
        }
        l[idx] = NIL;

        return l;
}
