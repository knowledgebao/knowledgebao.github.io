#include "example.h"

#include <stdio.h>

int add_v1(int a, int b, int c) { return a + b + c; }
int add_v2(int a, int b, int c) { return a + b + c; }
int WINAPI add_v3(int a, int b, int c) { return a + b + c; }
int FASTCALL add_v4(int a, int b, int c) { return a + b + c; }
int add_v5(int a, int b, int c) { return a + b + c; } 
int AddOp::add_v6(int a, int b, int c) { return a + b + c; }
int AddOp::add_v7(int a, int b, int c) { return a + b + c; }

int add_v8(int a, int b) { return a + b; }
int add_v8(int a, int b, int c) { return a + b + c; }
int add_v8(int a, int b, int c, int d){ return a + b + c + d; }

int add_v9(int a, int b, int* OUT){ return *OUT = a + b; }
int sprint(char *buffer, char a, int b, const char* c) {
    return sprintf(buffer, "[%c, %d, %s]", a,  b, c);
}
