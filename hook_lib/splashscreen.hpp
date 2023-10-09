#pragma once
#include "Main.hpp"
typedef unsigned char byte;

size_t operator"" _b(size_t val);
size_t reverse_b(size_t val);
size_t reverse_b(const void* val);

size_t operator"" _g(size_t val);
size_t reverse_g(size_t val);
size_t reverse_g(const void* val);

extern byte data_buf[1];

void set_splashscreen();
