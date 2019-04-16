


#include <cassert>
#include <vector>
#include <random>
#include <algorithm>
#include <memory.h>

#include "./SetsunaShiki.h"
#include "./Lapse.h"



enum eSrc {
    Rand,
    Max,
    Min,
    Nop,
    
    Num,
};

using sort_t = float;



#define ORDER   0
#define FAT     0

struct Test
{
    sort_t m;
    #if ORDER//[
    std::size_t o;
    #endif//]
    #if FAT//[
    std::size_t f[FAT];
    #endif
};

bool operator <(const Test& s, const Test& t)
{
    return s.m < t.m;
}

bool operator ==(const Test& s, const Test& t)
{
    return s.m == t.m;
}



std::size_t init(eSrc Src, std::vector<Test>& a, std::mt19937& Rand, std::uniform_int_distribution<>& Range)
{
    {   // 
        sort_t m = 0;
        std::size_t o = 0;
        for (auto& v : a){
            v.m = m++;
            #if ORDER//[
            v.o = o++;
            #endif//]
            #if FAT//[
            for (auto& f : v.f) f = 0;
            #endif//]
        }
    }
    
    {   // 
        std::size_t oChange = 0;
        switch (Src){
            case eSrc::Rand:{
                oChange = Range(Rand);
                a[oChange].m = Range(Rand);
                break;
            }
            case eSrc::Max:{
                oChange = 0;
                a[oChange].m = a.size();
                break;
            }
            case eSrc::Min:{
                oChange = a.size()-1;
                a[oChange].m = -1;
                break;
            }
            case eSrc::Nop:{
                oChange = Range(Rand);
                break;
            }
            default:{
                break;
            }
        }
        return oChange;
    }
}



void test(eSrc Src, int nTest, int nRepeat)
{
    std::random_device Seed;
    std::mt19937 Rand(Seed());
    std::uniform_int_distribution<> Range(0, nTest-1);
    auto a = std::vector<Test>(nTest);
    
    static const char* apSrc[eSrc::Num]={
        "Rand",
        "Max",
        "Min",
        "Nop",
    };
    printf("\n\n--- %s %d\n", apSrc[Src], nTest);
    
    #if 1//[
    {   // 
        double t0 = 0;
        double t1 = 0;
        double t2 = 0;
        
        for (auto n = nRepeat; n; --n){
            auto oChange = init(Src, a, Rand, Range);
            
            #if 1//[
            {   // 
                auto s = a;
                auto l = Lapse::Now();
                std::sort(s.begin(), s.end());
                t0 += Lapse::Now() - l;
            }
            #endif//]
            
            #if 1//[
            {   // 
                auto s = a;
                auto l = Lapse::Now();
                std::stable_sort(s.begin(), s.end());
                t1 += Lapse::Now() - l;
            }
            #endif//]
            
            #if 1//[
            {   // 
                auto s = a;
                auto l = Lapse::Now();
                SetsunaShiki::Sort(s.data(), s.size(), oChange);
                t2 += Lapse::Now() - l;
            }
            #endif//]
        }
        
        printf("\n== std::sort\n");          Lapse::Out(t0 / nRepeat);
        printf("\n== std::stable_sort\n");   Lapse::Out(t1 / nRepeat);
        printf("\n== SetsunaShiki::Sort\n"); Lapse::Out(t2 / nRepeat);
    }
    #else//][
    for (auto n = nLoop; n; --n){
        auto oChange = init(Src, a, Rand, Range);
        
        auto s0 = a;
        auto s1 = a;
        auto s2 = a;
        
        std::sort(s0.begin(), s0.end());
        std::stable_sort(s1.begin(), s1.end());
        SetsunaShiki::Sort(s2.data(), s2.size(), oChange);
        
        auto bEqual01 = (s0 == s1);
        auto bEqual12 = (s1 == s2);
        auto bEqual20 = (s2 == s0);
        
        printf("\n");
        printf("%d %d\n", bEqual01, (a == s0));
        printf("%d %d\n", bEqual12, (a == s1));
        printf("%d %d\n", bEqual20, (a == s2));
        assert(bEqual12);
    }
    #endif//]
}



int main(int argc, char* argv[])
{
    test(eSrc::Rand,     10000, 1000);
    test(eSrc::Rand,   1000000, 100);
    test(eSrc::Rand, 100000000, 50);
    
    test(eSrc::Max,  100000000, 10);
    test(eSrc::Min,  100000000, 10);
    test(eSrc::Nop,  100000000, 10);
    return 0;
}
