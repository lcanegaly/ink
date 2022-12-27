#pragma once
#include <stdio.h>

#define LOG(x) printf("info : %s\n", (x))
#define LOG_PTR(p) printf("info : pointer - %p\n", (void*)(p))
