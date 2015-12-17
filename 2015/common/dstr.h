#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG

#define DYNSTR_MIN 30
#define DYNSTR_GROW_METHOD_TWO

typedef struct {
	char * strv;
	int len;
	int sz;
} dynTstr;


dynTstr* dstrFinit(dynTstr *string);
void dstrFfree(dynTstr *str);
char* dstrFappends(dynTstr *str, char *s);
char* dstrFappend(dynTstr *str, char *s, int len);
