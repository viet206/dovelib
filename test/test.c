#include <stdio.h>
#include "freestd.h"

int main() {
	char buf[32];

	dyn_t* a = dyn_new(buf,"Hello World",PTR);

	puts(a->type.p);
}
