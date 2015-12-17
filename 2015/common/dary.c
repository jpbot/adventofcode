#include "dary.h"

void daryFdel(dynTarray *dynary, int a){
#ifdef DEBUG
	printf("Deleting member %d\n", a);
#endif

	assert(a < dynary->len);
	
	dynary->cnt--;
	dynary->len--;
	for(; a < dynary->len; a++){
		if(dynary->fp)
			dynary->fp(dynary->ptr[a]);

		dynary->ptr[a] = dynary->ptr[a+1];
	}
}

void daryFfdel(dynTarray *dynary, int a){
#ifdef DEBUG
	printf("Deleting member %d\n", a);
#endif

	assert(a < dynary->len);

	dynary->cnt--;
	if(dynary->fp)
		dynary->fp(dynary->ptr[a]);
	dynary->ptr[a] = 0;

	if(dynary->len - dynary->cnt > dynary->len/2)
		daryFcompact(dynary);
}

void daryFcompact(dynTarray *dynary){
	int i = 0;

	if(dynary->cnt == dynary->len)
		return;

	for(dynary->cnt = 0;i < dynary->len; i++)
		if(dynary->ptr[i])
			dynary->ptr[dynary->cnt++] = dynary->ptr[i];
		
	dynary->len = dynary->cnt;
}

//void daryFprint(dynTarray *dynary){
//	int i=0;
//	for(; i < dynary->len; i++)
//		if(dynary->ptr[i])
//			printf("%d: %s\n", i, ((dynTstr *) dynary->ptr[i])->strv);
//}

dynTarray * daryFinit(dynTarray *dynary, void (*fp)(void *)){
	dynary->ptr = (void **) malloc(sizeof(void *) * DYNARY_MIN);
	dynary->len = 0;
	dynary->cnt = 0;
	dynary->sz = DYNARY_MIN;
	dynary->fp = fp;
	return dynary;
}

void daryFfree(dynTarray *dynary){
	int i = 0;

	if(dynary->fp)
		for(; i < dynary->len; i++)
			dynary->fp(dynary->ptr[i]);

	free(dynary->ptr);
	dynary->len = 0;
	dynary->cnt = 0;
	dynary->sz = 0;
}

void * daryFadd(dynTarray *dynary, void * a){
	if(dynary->len + 1 > dynary->sz){   // GROW array
		dynary->sz += DYNARY_MIN;
		dynary->ptr = (void **) realloc(dynary->ptr, sizeof(void *) * dynary->sz);
	}

	dynary->cnt++;

	return dynary->ptr[dynary->len++] = a;
}

void * daryFget(dynTarray *dynary, int a){
	if(a > dynary->len)
		return 0;

	return dynary->ptr[a];
}
