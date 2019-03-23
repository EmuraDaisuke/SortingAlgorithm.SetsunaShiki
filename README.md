# 刹那式
刹那式（せつなしき）は、「クイックソート種より高速」を目指した、比較安定ソートの補助アルゴリズムです。  

以下の特徴があります。  
* 比較ソート
* 安定ソート
* 外部領域：無し
* 平均時間：O(log N)
* 最悪時間：O(log N)
* 最良時間：O(2)
* 再帰：無し

<br>

# 基本となるアルゴリズム
* ソート済み配列に対して、任意の位置の値を変更します。
* （変更位置 ＜ 変更位置の下）であれば、下方を二分探索し、変更位置から探索位置までを回転させます。
* （変更位置の上 ＜ 変更位置）であれば、上方を二分探索し、変更位置から探索位置までを回転させます。

## 具体的な流れ
~~~
ソート済み配列に対して、任意の位置の値を変更します
0 1 2 4 5 6 7 9|ソート済み配列
        ↓
0 1 2 4 x 6 7 9|任意の位置の値を変更
~~~
~~~
（変更位置 ＜ 変更位置の下）であれば、下方を二分探索し、変更位置から探索位置までを回転させます
0 1 2 4 5 3 7 9|[5]=3の場合
0 1 2 4 5|. . .|下方を二分探索
. . .|3 4 5|. .|変更位置から探索位置までを回転
0 1 2 3 4 5 7 9|ソート結果
~~~
~~~
（変更位置の上 ＜ 変更位置）であれば、上方を二分探索し、変更位置から探索位置までを回転させます
0 1 8 4 5 6 7 9|[2]=8の場合
. . .|4 5 6 7 9|上方を二分探索
. .|4 5 6 7 8|.|変更位置から探索位置までを回転
0 1 4 5 6 7 8 9|ソート結果
~~~

<br>

# ビルド＆テスト
環境は以下のとおりです。
* Windows 10 Pro 64bit
* Core i7-8700 3.20GHz

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

# 余談
如何だったでしょうか？  

ソートは、常に全体で行う必要はないという観点から、差分ソートという考えに至ったアイデアです。  
std::sort と std::stable_sort との比較はフェアでない為、ベンチマーク結果は控えました。  

上手く運用すれば、激速なパフォーマンスが得られますが、使い方を誤ると激遅になる諸刃の剣。  

ソートアルゴリズムには、まだ浪漫が残っています。  

---
[颯式（はやてしき）](https://github.com/EmuraDaisuke/SortingAlgorithm.HayateShiki)も併せて読んでいただけると、より楽しめるかも知れません。  
