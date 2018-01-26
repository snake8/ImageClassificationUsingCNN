
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>

std::string Backtrace(int skip);


