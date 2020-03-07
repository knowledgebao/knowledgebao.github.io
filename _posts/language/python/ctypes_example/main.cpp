#include <iostream>

#include "example.h"

#define PRINT(v) printf("%s=%d \n", #v, v)

int main(int argc, char** argv) {
    PRINT(add_v1(1,3,5));
    PRINT(add_v2(1,3,5));
    PRINT(add_v3(1,3,5));
    PRINT(add_v4(1,3,5));
    PRINT(add_v5(1,3,5));
    PRINT(AddOp().add_v6(1,3,5));
    PRINT(AddOp().add_v7(1,3,5));
    PRINT(add_v8(1,3));
    PRINT(add_v8(1,3,5));
    PRINT(add_v8(1,3,5,7));
    return 0;
}
