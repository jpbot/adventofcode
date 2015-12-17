#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG

#define DYNARY_MIN 3 //0


typedef struct {
	void ** ptr;
	int len;
	int cnt;
	int sz;
	void (*fp)(void *);
} dynTarray;



dynTarray * daryFinit(dynTarray *dynary, void (*fp)(void *));
void daryFfree(dynTarray *dynary);
void * daryFadd(dynTarray *dynary, void * a);
void * daryFget(dynTarray *dynary, int a);
//void daryFprint(dynTarray *dynary);
void daryFdel(dynTarray *dynary, int a);
void daryFfdel(dynTarray *dynary, int a);
void daryFcompact(dynTarray *dynary);

/*
inline void * daryFget(dynTarray *dynary, int a){
	if(a > dynary->len)
		return 0;

	return dynary->ptr[a];
}
*/
