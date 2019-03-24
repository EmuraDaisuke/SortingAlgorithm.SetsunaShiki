


#include <vector>
#include <random>
#include <algorithm>
#include <memory.h>

#include "./SetsunaShiki.h"
#include "./Lapse.h"



enum class eSrc {
    Rand,
    Max,
    Min,
    Nop,
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



void test(eSrc Src, int nTest, int nLoop, int nRepeat)
{
    std::random_device Seed;
    std::mt19937 Rand(Seed());
    std::uniform_int_distribution<> Range(0, nTest-1);
    
    auto a = std::vector<Test>(nTest);
    for (auto n = nLoop; n; --n){
        printf("\n\n--- %d\n", nTest);
        std::size_t oChange = 0;
        
        {   // 
            sort_t m = 0;
            for (auto& v : a) v.m = m++;
        }
        
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
        }
        
        {   // 
            std::size_t o = 0;
            for (auto& v : a){
                #if ORDER//[
                v.o = ++o;
                #endif//]
                #if FAT//[
                for (auto& f : v.f) f = 0;
                #endif//]
            }
        }
        
        #if 1//[
        printf("\n== std::sort\n");
        for (auto n = nRepeat; n; --n){
            auto s = a;
            Lapse l;
            std::sort(s.begin(), s.end());
        }
        #endif//]
        
        #if 1//[
        printf("\n== std::stable_sort\n");
        for (auto n = nRepeat; n; --n){
            auto s = a;
            Lapse l;
            std::stable_sort(s.begin(), s.end());
        }
        #endif//]
        
        #if 1//[
        printf("\n== SetsunaShiki::Sort\n");
        for (auto n = nRepeat; n; --n){
            auto s = a;
            Lapse l;
            SetsunaShiki::Sort(s.data(), s.size(), oChange);
        }
        #endif//]
        
        #if 0//[
        {   // 
            auto s0 = a;
            auto s1 = a;
            auto s2 = a;
            
            std::sort(s0.begin(), s0.end());
            std::stable_sort(s1.begin(), s1.end());
            SetsunaShiki::Sort(s2.data(), s2.size(), oChange);
            
            auto bStrict01 = (memcmp(s0.data(), s1.data(), s1.size() * sizeof(Test)) == 0);
            auto bStrict12 = (memcmp(s1.data(), s2.data(), s2.size() * sizeof(Test)) == 0);
            auto bStrict20 = (memcmp(s2.data(), s0.data(), s0.size() * sizeof(Test)) == 0);
            
            printf("\n");
            printf("%d %d %d\n", (s1 == s0), bStrict01, (a == s0));
            printf("%d %d %d\n", (s2 == s1), bStrict12, (a == s1));
            printf("%d %d %d\n", (s0 == s2), bStrict20, (a == s2));
        }
        #endif//]
    }
}



int main(int argc, char* argv[])
{
    eSrc Src = eSrc::Rand;
    test(Src,     10000, 1, 4);
    test(Src,   1000000, 1, 4);
    test(Src, 100000000, 1, 4);
    return 0;
}
