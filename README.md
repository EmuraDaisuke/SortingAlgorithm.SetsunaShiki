# 刹那式(Setsuna-Shiki)
Setsuna-Shiki is a new method of comparison stable sorting algorithm.  
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
|10,000|0.00006410|0.00004770|**0.00000190**|
|1,000,000|0.00916610|0.00753640|**0.00029180**|
|100,000,000|0.23774790|1.30206660|**0.01747180**|

## **clang++**
|Array|std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|10,000|0.00005290|0.00006160|**0.00000020**|
|1,000,000|0.00754440|0.01009760|**0.00003920**|
|100,000,000|1.02647040|1.43888810|**0.01039800**|

## **g++**
|Array|std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|10,000|0.00008570|0.00008380|**0.00000020**|
|1,000,000|0.01185260|0.00942110|**0.00003780**|
|100,000,000|1.36576920|1.38283890|**0.01030640**|

<br>

# Limited condition benchmark
The following is sorted by the array [100,000,000].  
The unit is seconds, the lower the number, the faster.  

## Worst case 1
When the top is changed to the maximum value for a sorted array.  

||std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|Msvc|0.24552310|1.31975820|**0.03363140**|
|clang++|0.98457310|1.59001550|**0.02440560**|
|g++|1.30654070|1.41271570|**0.02451180**|

## Worst case 2
When the end is changed to the minimum value for a sorted array.  

||std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|Msvc|0.25440420|1.30800500|**0.03833860**|
|clang++|6.58926600|1.55079530|**0.02815680**|
|g++|6.81361270|1.38467000|**0.02570930**|

## Best case
For a sorted array, where the position is random without changing the value.  

||std::sort|std::stable_sort|Setsuna-Shiki|
|---:|---:|---:|---:|
|Msvc|0.22714320|1.28550500|**0.00000020**|
|clang++|1.03461340|1.54787000|**0.00000030**|
|g++|1.36841120|1.37394720|**0.00000050**|


<br>

# Finally
How was it?  

We came up with the idea of ​​differential sorting, in terms of the fact that sorting does not always have to be done in its entirety.  
Although the comparison between std::sort and std::stable_sort, which is an overall sort, and Setsuna-Shiki, which is an diff sort, is not fair, it should be used to determine the usefulness of diff sort.  

If you operate well, you can get a rapid performance, but if you use it incorrectly it will be a two-edged sword.  

The sort algorithm is still romantic.  

<br>

---
It may be fun to read [Hayate-Shiki](https://github.com/EmuraDaisuke/SortingAlgorithm.HayateShiki).