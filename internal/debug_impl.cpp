#pragma once
#include "../external/prettyprint/prettyprint.h"
#define Debug(vari) std::cerr << #vari << " = " << (vari) << std::endl
#define DebugFmtln(fmt, ...) fprintf(stderr, fmt "\n", __VA_ARGS__); fflush(stderr)