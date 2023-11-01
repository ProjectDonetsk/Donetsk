#include "addr_utils.hpp"

#include <cctype>
#include <string>
#include <windows.h>

struct Addresses {
	uintptr_t ModuleBase;
	uintptr_t jmp_rbx;
};

Addresses g_Addrs{};

void initAddrUtils() {
	g_Addrs.ModuleBase = (uintptr_t)(GetModuleHandle(0));
}

size_t _b(const size_t val) { return g_Addrs.ModuleBase + val; }

size_t operator"" _b(const size_t val) { return _b(val); }

size_t reverse_b(const size_t val) { return val - g_Addrs.ModuleBase; }

size_t reverse_b(const void* val) { return reverse_b(reinterpret_cast<size_t>(val)); }

size_t _g(const size_t val) { return g_Addrs.ModuleBase + (val - 0x140000000); }

size_t operator"" _g(const size_t val) { return _g(val); }

size_t reverse_g(const size_t val) { return (val - g_Addrs.ModuleBase) + 0x140000000; }

size_t reverse_g(const void* val) { return reverse_g(reinterpret_cast<size_t>(val)); }

namespace {
	DWORD get_module_size(uintptr_t module_base) {
		return reinterpret_cast<PIMAGE_NT_HEADERS>(
			module_base +
			reinterpret_cast<PIMAGE_DOS_HEADER>(module_base)->e_lfanew)
			->OptionalHeader.SizeOfImage;
	};
	inline byte hex_nibble_to_byte(const char* hexNibble) {
		if (not (std::isxdigit(hexNibble[0]) and std::isxdigit(hexNibble[1]))) {
			return 0;
		}
		return std::stoi(std::string(hexNibble, hexNibble + 1), nullptr, 16);
	}
}

uintptr_t findPattern(const char* pattern, const char* module_name) {
	return findPattern(pattern, (uintptr_t)GetModuleHandle(module_name));
}

uintptr_t findPattern(const char* pattern, uintptr_t module_start) {
	if (module_start == 0ULL) {
		return 0ULL;
	}

	const auto module_end = module_start + get_module_size(module_start);

	const char* pattern_current{ pattern };
	uintptr_t current_match{ 0ULL };

	MEMORY_BASIC_INFORMATION64 page_information{};
	for (auto current_page = reinterpret_cast<unsigned char*>(module_start);
		current_page < reinterpret_cast<unsigned char*>(module_end);
		current_page = reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize)) {
		if (VirtualQuery(reinterpret_cast<LPCVOID>(current_page),
			reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information),
			sizeof(MEMORY_BASIC_INFORMATION)) == 0) {
			break;
		}

		if (page_information.Protect == PAGE_NOACCESS or page_information.State != MEM_COMMIT or
			(page_information.Protect & PAGE_GUARD)) {
			continue;
		}

		for (auto current_address = reinterpret_cast<unsigned char*>(page_information.BaseAddress);
			current_address < reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize - 0x8);
			current_address++) {
			if (*pattern_current != '\?' and *current_address != hex_nibble_to_byte(pattern_current)) {
				current_match = 0ULL;
				pattern_current = pattern;
				continue;
			}

			if (not current_match)
			{
				current_match = reinterpret_cast<uintptr_t>(current_address);
			}

			pattern_current += 3;
			if (pattern_current[-1] == NULL)
			{
				return current_match;
			}
		}
	}

	return 0ULL;
}
