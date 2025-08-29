
#pragma once
/*Setup Pre-compile header file*/
// Standard Libraty
#include <memory>
#include <stdint.h>
#include <set>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>
#include <assert.h>
#include <sstream>
#include <istream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <map>
#include <stack>
#include <cstring>

template <typename T>
using Shared = std::shared_ptr<T>;
template <typename T>
using Unique = std::unique_ptr<T>;

// Build share library
#if ON_VISOL_ENGINE
#if DYNAMIC_BUILD
#ifdef _MSC_VER
#define VISOL_API __declspec(dllexport)
#else
#define VIVISOL_API __attribute__((visibility("default")))
#endif
#else
#define VIVISOL_API
#endif
#else
#if DYNAMIC_IMPORT
#ifdef _MSC_VER
#define VISOL_API __declspec(dllimport)
#else
#define VISOL_API
#endif
#else
#define VISOL_API
#endif
#endif

// Runtime assert
#define VISOL_ASSERT assert

// Static assert when compile C2607
#if defined(__clang__) || defined(__gcc__)
#define VISOL_STATIC_ASSERT _Static_assert
#else
#define VISOL_STATIC_ASSERT static_assert
#endif

// Inline function
#if defined(__clang__) || defined(_gcc__)
#define VISOL_FORCE_INLINE __attribute__((always_inline)) inline
#define VISOL_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define VISOL_FORCE_INLINE __forceinline
#define VISOL_NOINLINE __declspec(noinline)
#else
#define VISOL_FORCE_INLINE inline
#define VISOL_NOINLINE
#endif

// Free memory
#define VISOL_FREE_MEMORY(memory) \
    if (memory != nullptr)     \
    {                          \
        delete memory;         \
        memory = nullptr;      \
    }

#define BIND_EVENT_FUNCTION(function) [this](auto &...args) -> decltype(auto) \
{ return this->function(std::forward<decltype(args)>(args)...); }

#define INVALID_ID 0

namespace ViSolEngine
{
    using UUID = size_t;

    UUID VISOL_API getUUID();

    template <typename T>
    UUID VISOL_API getTypeUUID()
    {
        static UUID uuid = getUUID(); // static Func call one time
        return uuid;
    }
}
