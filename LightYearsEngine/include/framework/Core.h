#pragma once

#include <stdio.h>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace ly
{
template<typename T>
using unique = std::unique_ptr<T>;

template<typename T>
using shared = std::shared_ptr<T>;

template<typename T>
using weak = std::weak_ptr<T>;

template<typename T>
using List = std::vector<T>;

// Sort from least to greatest
template<typename keyType, typename valType, typename Pr = std::less_equal<keyType>>
using Map = std::map<keyType, valType, Pr>;

template<typename keyType, typename valType, typename hasher = std::hash<keyType>>
using Dictionary = std::unordered_map<keyType, valType, hasher>;

template<typename T>
using Set = std::unordered_set<T>;

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

}