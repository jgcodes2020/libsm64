#include <cstdint>

#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

#include <windows.h>

#include "libsm64_utils/sm64.hpp"

using std::string, std::array, std::runtime_error;
//A function that takes nothing and returns nothing.
//Equivalent to java.lang.Runnable, hence the name.
typedef void (*runnable_fn)(void);
// These look much cleaner with hex numbers
const array<array<libsm64::sm64::mem_region, 2>, 2> save_sections {
  // US Version
  array<libsm64::sm64::mem_region, 2> {
    libsm64::sm64::mem_region {0x13E000, 0x2B4860},
    libsm64::sm64::mem_region {0xD65000, 0x4ABA80}
  },
  // JP Version
  array<libsm64::sm64::mem_region, 2> {
    libsm64::sm64::mem_region {0x13C000, 0x24B6E0},
    libsm64::sm64::mem_region {0xCF7000, 0x4ABB60}
  }
};

libsm64::sm64::sm64(string path, libsm64::sm64::version version) {
  _version = version;
  _lib = LoadLibraryA(path.c_str());
  if (_lib == NULL) {
    auto error = libsm64::shared_lib_error("Could not load SM64");
    error.error_code = GetLastError();
    throw error;
  }
  //call sm64_init
  ((runnable_fn) GetProcAddress(static_cast<HMODULE>(_lib), "sm64_init"))();
  //throws range error if we get invalid version
  array<libsm64::sm64::mem_region, 2> data = save_sections.at(static_cast<size_t>(version));
  for (int i = 0; i < 2; i++) 
    _regions[i] = data[i];
}
libsm64::sm64::~sm64() {
  FreeLibrary(static_cast<HMODULE>(_lib));
}

void* libsm64::sm64::_impl_locate(string symbol) {
  FARPROC result = GetProcAddress(static_cast<HMODULE>(_lib), symbol.c_str());
  if (result == NULL) {
    auto error = libsm64::shared_lib_error("Could not load symbol " + symbol);
    error.error_code = GetLastError();
    throw error;
  }
  else
    return reinterpret_cast<void*>(result);
}

void libsm64::sm64::advance() {
  //call sm64_update
  ((runnable_fn) GetProcAddress(static_cast<HMODULE>(_lib), "sm64_update"))();
}