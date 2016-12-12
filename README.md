# Jaccard: Bitmap vs Sparse representations

A simple test to verify the performance of using Bitmaps against Sparse array representation when calculating pairwise similarities for a set of text documents.

Compile with `make` and execute the tests with:

`sh runScript.sh`

Results for *trump.txt* (few features per documents):

| | Sparse | Bitmap 256 bits | Bitmap 64 bits |
|---|---|---|---|
|real | 6.444s | 8.109s | 10.432s |
| user | 6.436s | 8.108s | 10.200s |

Results for *trumpJoin.txt* (many features per documents):

| | Sparse | Bitmap 256 bits | Bitmap 64 bits
|---|---|---|---|
|real | 1.168s | 0.252s |  0.322s
| user | 1.168s | 0.248s | 0.248s
