#include "dstr.h"

#define inline __inline

dynTstr* dstrFinit(dynTstr *str){
	str->strv = (char *) malloc(DYNSTR_MIN);
	if(str->strv == 0)
		return 0;

	*str->strv = 0;
	str->len = 0;
	str->sz = DYNSTR_MIN;
	return str;
}

inline void dstrFfree(dynTstr *str){
	free(str->strv);
	str->strv = 0;
	str->len = 0;
	str->sz = 0;
}

inline char* dstrFappends(dynTstr *str, char *s){
	return dstrFappend(str, s, strlen(s));
}

char* dstrFappend(dynTstr *str, char *s, int len){
#ifdef DYN_GROWMETHOD_TWO
	if(str->len + len + 1 > str->sz){
		if(!(len < DYNSTR_MIN))
			str->sz += len;
		
		str->sz += DYNSTR_MIN;
		str->strv = (char *) realloc(str->strv, str->sz);
	}
#else
	if(str->len + len + 1 > str->sz){
		if(!(len < DYNSTR_MIN))
			str->sz += len;
		
		str->sz += DYNSTR_MIN;
		str->strv = (char *) realloc(str->strv, str->sz);
	}
#endif

	memcpy(str->strv + str->len, s, len + 1);
	str->len += len;

	return str->strv;
}
