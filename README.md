# Jaccard: Bitmap vs Sparse representations

A simple test to verify the performance of using Bitmaps against Sparse array representation when calculating pairwise similarities for a set of text documents.

Compile with `make` and execute the tests with:

`time ./jaccardSparse trump.txt > out.txt`

`time ./jaccardBitmap trump.txt > out.txt`

`time ./jaccardSparse trumpJoin.txt > out.txt`

`time ./jaccardBitmap trumpJoin.txt > out.txt`

Results for *trump.txt* (number of documents >> number of features):

| | Sparse | Bitmap |
|---|---|---|
|real | 6.444s | 8.109s |
| user | 6.436s | 8.108s |

Results for *trumpJoin.txt* (number of features >> number of documents):

| | Sparse | Bitmap |
|---|---|---|
|real | 1.168s | 0.252s |
| user | 1.168s | 0.248s |
