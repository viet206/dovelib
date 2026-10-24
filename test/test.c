/* Test All Case API */
#include <stdio.h>
#include "dove.h"

int counter = -1;

void new_heading(char* s) {
	printf("##############################\n"
	       "# %s			      \n"
	       "##############################\n\n",
	       s);
}

void log_print(char* s,int rt) {
	++counter;
	printf("#%d - %s %d \n",counter,s,rt);
}

void log_bool(char* s,int rt) {
	++counter;
	if (rt == COMPAT_FALSE ) {
		printf("#%d - %s : False\n",counter,s);
	}else if ( rt == COMPAT_TRUE ) {
		printf("#%d - %s : True\n",counter,s);
	}
}





void test_bool() {
	new_heading("Test Boolean");

	log_bool("is_num('1')",is_num('1'));
	log_bool("is_alpha('A')",is_alpha('A'));
	log_bool("is_lower('a')",is_lower('a'));
	log_bool("is_upper('A')",is_upper('A'));

	log_bool("compat_str_cmp(NULL,NULL,0)",compat_str_cmp(NULL,NULL,0));
	log_bool("compat_str_cmp(\"Hello C\",\"Hello C\",7)",compat_str_cmp("Hello C","Hello C",7));
	log_bool("compat_str_cmp(NULL,\"Hello C\",7)",compat_str_cmp(NULL,"Hello C",7));
	log_bool("compat_str_cmp(\"Hello C\",\"Hello C\",0)",compat_str_cmp("Hello C","Hello C",0));

	log_print("compat_str_len(\"Hello World\",20)",compat_str_len("Hello World",20));
	log_print("compat_str_len(\"Hello World C\",99999)",compat_str_len("Hello World C",99999));

	log_bool("compat_str_len(\"Hello World\",0)",compat_str_len("Hello World",0));
	log_bool("compat_str_len(NULL,0)",compat_str_len(NULL,0));
	log_bool("compat_str_len(NULL,99999)",compat_str_len(NULL,99999));
	log_bool("compat_str_len(\"Hello World C\",99999)",compat_str_len("Hello World C",99999));
}

int main() {
	test_bool();
}
