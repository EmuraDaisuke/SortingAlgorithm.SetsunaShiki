#pragma once



#include <utility>
#include <algorithm>

#define Auto    decltype(auto)



namespace SetsunaShiki {



// 

template <class RandomAccessIterator>
inline void sort(RandomAccessIterator const first, RandomAccessIterator const last, RandomAccessIterator const change);

template <class RandomAccessIterator, class Compare>
inline void sort(RandomAccessIterator const first, RandomAccessIterator const last, RandomAccessIterator const change, Compare comp);



// 

template <class RandomAccessIterator, class Compare> class Private
{
    private:
        static void InsertLower(RandomAccessIterator b, RandomAccessIterator e)
        {
            auto v = std::move(b[0]);
            while (b-- != e) b[1] = std::move(b[0]);
            b[1] = std::move(v);
        }
        
        
        
        static void InsertUpper(RandomAccessIterator b, RandomAccessIterator e)
        {
            auto v = std::move(b[0]);
            while (++b != e) b[-1] = std::move(b[0]);
            b[-1] = std::move(v);
        }
    
    
    
    public:
        static void Sort(RandomAccessIterator const first, RandomAccessIterator const last, RandomAccessIterator const change, Compare comp)
        {
            Auto nArray = std::distance(first, last);
            if (nArray > 1){
                Auto nLower = std::distance(first, change);
                Auto nUpper = std::distance(change+1, last);
                if (nLower > 0 && comp(change[0], change[-1])){
                    Auto iInsert = std::upper_bound(first, change, *change, comp);
                    InsertLower(change, iInsert);
                } else if (nUpper > 0 && comp(change[1], change[0])){
                    Auto iInsert = std::lower_bound(change+1, last, *change, comp);
                    InsertUpper(change, iInsert);
                }
            }
        }
};



template <class RandomAccessIterator>
inline void sort(RandomAccessIterator const first, RandomAccessIterator const last, RandomAccessIterator const change)
{
    SetsunaShiki::sort(first, last, change, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}



template <class RandomAccessIterator, class Compare>
inline void sort(RandomAccessIterator const first, RandomAccessIterator const last, RandomAccessIterator const change, Compare comp)
{
    SetsunaShiki::Private<RandomAccessIterator, Compare>::Sort(first, last, change, comp);
}
}



#undef Auto
