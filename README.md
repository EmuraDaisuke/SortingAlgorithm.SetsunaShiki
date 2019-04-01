# 刹那式(Setsuna-Shiki)
Setsuna-Shiki is a new method of differential sorting algorithm that applies bisection insertion sorting.  
For a sorted array, focus on the place where the value change is made and sort very fast.  

It has the following features.  
* Comparison sort
* Stable sort
* External area: None
* Average time: O (log N)
* Worst time: O (log N)
* Best time: O (2)
* Recursion: None

<br>

# Basic algorithm
* Change the value at any position in the sorted array.
* If (Changed position value < value below change position), the lower range is binary-searched and rotate from change position to search position.
* If (value above change position < Changed position value), the upper range is binary-searched and rotate from change position to search position.

## Examples
~~~
Change the value at any position in the sorted array.
0 1 2 4 5 6 7 9|Sorted array
        ↓
0 1 2 4 x 6 7 9|Change the value at any position
~~~
~~~
If (Changed position value < value below change position), the lower range is binary-searched and rotate from change position to search position.
0 1 2 4 5 3 7 9|In the case of [5]=3
0 1 2 4 5|. . .|Binary search the lower range
. . .|3 4 5|. .|Rotate from change position to search position
0 1 2 3 4 5 7 9|Sort result
~~~
~~~
If (value above change position < Changed position value), the upper range is binary-searched and rotate from change position to search position.
0 1 8 4 5 6 7 9|In the case of [2]=8
. . .|4 5 6 7 9|Binary search the upper range
. .|4 5 6 7 8|.|Rotate from change position to search position
0 1 4 5 6 7 8 9|Sort result
~~~

<br>

# Points devised
Even if binary search is performed to the area where the same value is continuous, stability is maintained.  
* The binary search in the lower range searches the end of the continuous area.
* The binary search in the upper range searches the beginning of a continuous area.

<br>

# Build & Test
The following environment has been verified.  
* Windows 10 Pro 64bit
* Core i7-8700 3.20 GHz

## **Msvc**
Microsoft(R) C/C++ Optimizing Compiler Version 19.15.26732.1 for x64  
Microsoft (R) Incremental Linker Version 14.15.26732.1  
~~~
cl Main.cpp -Ox -EHsc -Fe:TestMsvc.exe
TestMsvc.exe
~~~

## **clang++**
clang version 7.0.0 (tags/RELEASE_700/final)  
Target: x86_64-w64-windows-gnu  
~~~
clang++ Main.cpp -O3 -o TestClang++.exe
TestClang++.exe
~~~

## **g++**
gcc version 8.2.0 (Rev3, Built by MSYS2 project)  
Target: x86_64-w64-mingw32  
~~~
g++ Main.cpp -O3 -o TestG++.exe
TestG++.exe
~~~

<br>

# Average benchmark
The following is the case of changing the random position of the sorted array to a random value.  
The unit is seconds, the lower the number, the faster.  

## **Msvc**
|Array|std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|10,000|0.00007095|0.00004502|**0.00000115**|
|1,000,000|0.00975892|0.00698905|**0.00009487**|
|100,000,000|0.27018098|1.26169269|**0.01670523**|

## **clang++**
|Array|std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|10,000|0.00006162|0.00006669|**0.00000050**|
|1,000,000|0.00775640|0.00978430|**0.00006938**|
|100,000,000|0.99487866|1.46673092|**0.01248609**|

## **g++**
|Array|std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|10,000|0.00009420|0.00006123|**0.00000040**|
|1,000,000|0.01269281|0.00870394|**0.00006129**|
|100,000,000|1.32669707|1.32506381|**0.01232715**|

<br>

# Limited condition benchmark
The following is sorted by the array [100,000,000].  
The unit is seconds, the lower the number, the faster.  

## Worst case 1
When changing the first to the maximum value for a sorted array.  

||std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|Msvc|0.28328255|1.27838705|**0.03301556**|
|clang++|0.94680632|1.49072315|**0.02450915**|
|g++|1.24406811|1.35104790|**0.02465655**|

## Worst case 2
When changing the end to the minimum value for a sorted array.  

||std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|Msvc|0.29024827|1.27097092|**0.03784692**|
|clang++|6.59369224|1.44779880|**0.02844831**|
|g++|7.05050788|1.30785120|**0.02579642**|

## Best case
When the position is specified randomly without changing the value for the sorted array.  

||std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|Msvc|0.26143167|1.24644350|**0.00000026**|
|clang++|0.99570890|1.44735863|**0.00000031**|
|g++|1.33114203|1.30589223|**0.00000050**|

<br>

# Finally
How was it?  

We came up with the idea of ​​differential sorting, in terms of the fact that sorting does not always have to be done in its entirety.  
Although the comparison between std::sort and std::stable_sort, which is an overall sort, and Setsuna-Shiki, which is an diff sort, is not fair, it should be used to determine the usefulness of diff sort.  

If you operate well, you can get a rapid performance, but if you use it incorrectly it will be a two-edged sword.  

The sort algorithm is still romantic.  

<br>

---
It may be more enjoyable if you read the following together.  
* [Hayate-Shiki](https://github.com/EmuraDaisuke/SortingAlgorithm.HayateShiki)
* [Homura-Shiki](https://github.com/EmuraDaisuke/SortingAlgorithm.HomuraShiki)
