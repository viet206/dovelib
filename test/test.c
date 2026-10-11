#include "nekocl.h"
#include <stdio.h>

int main() {
	char buf[64] = {0};

	str_t a = str_new(buf,"Hello World",12);

	puts(a->str);

	char* s = "Tiny World";

	dyn_t b = dyn_new(buf,s,PTR_T);

	puts(b->p);

	b = dyn_new(buf,&(int){512},INT_T);

	printf("%d\n",b->i);

}
