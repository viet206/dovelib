#include "nekocl.h"
#include <stdio.h>

int main() {
	char buf[64] = {0};

	str_t a = str_new(buf,"Hello World",12);

	puts(a->str);

	char* s = "Tiny World";

	dyn_t b = dyn_new(buf,s,PTR_T);

	puts(b->p);

	b = dyn_lint(buf,8324667,INT_T);

	printf("%i\n",b->i);

	b = dyn_new(buf,s,PTR_T);

	printf("%p\n",b->p);

	b = dyn_new(NULL,NULL,PTR_T);

	if ( b == NIL || b == FALSE ) {
		puts("Error Dyn_t");
		return 1;
	}

}
