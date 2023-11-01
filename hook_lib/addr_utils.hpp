#include <vadefs.h>

void initAddrUtils();

size_t _b(size_t val);
size_t operator"" _b(size_t val);
size_t reverse_b(size_t val);
size_t reverse_b(const void* val);

size_t _g(size_t val);
size_t operator"" _g(size_t val);
size_t reverse_g(size_t val);
size_t reverse_g(const void* val);

uintptr_t findPattern(const char* pattern, const char* module_name);
uintptr_t findPattern(const char* pattern, uintptr_t module_start);
