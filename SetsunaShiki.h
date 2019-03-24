#pragma once
// Copyright(c) 2019 Emura Daisuke
// MIT License



#include <cstddef>
#include <utility>

#define Auto    decltype(auto)



namespace SetsunaShiki {



// 

template <class T> void Sort(T* const aSrc, std::size_t nSrc, std::size_t oChange);

template <class T> std::size_t SearchLower(T* a, std::size_t n, T& v);
template <class T> std::size_t SearchUpper(T* a, std::size_t n, T& v);

template <class T> void CopyLower(T* p, std::size_t n);
template <class T> void CopyUpper(T* p, std::size_t n);



// 

template <class T>
void Sort(T* const aSrc, std::size_t nSrc, std::size_t oChange)
{
    if (aSrc && nSrc > 1 && oChange < nSrc){
        auto nLower = oChange;
        auto nUpper = nSrc - oChange - 1;
        if (nLower && aSrc[oChange] < aSrc[oChange-1]){
            Auto oLower = SearchLower(&aSrc[0], nLower, aSrc[oChange]);
            CopyLower(&aSrc[oChange], (oChange - oLower));
        } else if (nUpper && aSrc[oChange+1] < aSrc[oChange]){
            Auto oUpper = SearchUpper(&aSrc[oChange+1], nUpper, aSrc[oChange]);
            CopyUpper(&aSrc[oChange], oUpper);
        }
    }
}



template <class T>
std::size_t SearchLower(T* a, std::size_t n, T& v)
{
    std::size_t o0 = 0;
    std::size_t o1 = n;
    while ((o1 - o0) > 1){
        auto oh = (o1 + o0) >> 1;
        if (v < a[oh]){
            o1 = oh;
        } else {
            o0 = oh;
        }
    }
    return (v < a[o0])? o0: o1;
}



template <class T>
std::size_t SearchUpper(T* a, std::size_t n, T& v)
{
    std::size_t o0 = 0;
    std::size_t o1 = n;
    while ((o1 - o0) > 1){
        auto oh = (o1 + o0) >> 1;
        if (a[oh] < v){
            o0 = oh;
        } else {
            o1 = oh;
        }
    }
    return o1;
}



template <class T>
void CopyLower(T* p, std::size_t n)
{
    auto v = std::move(p[0]);
    for (; n--; --p) p[0] = std::move(p[-1]);
    p[0] = std::move(v);
}



template <class T>
void CopyUpper(T* p, std::size_t n)
{
    auto v = std::move(p[0]);
    for (; n--; ++p) p[0] = std::move(p[1]);
    p[0] = std::move(v);
}



}
