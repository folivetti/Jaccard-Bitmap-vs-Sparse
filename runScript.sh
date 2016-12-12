#!/bin/bash

echo "Few features per docs"

echo "Sparse vectors"
time ./jaccardSparse trump.txt > out.txt
echo "Bitmap 256 bits"
time ./jaccardBitmap trump.txt > out.txt
echo "Bitmap 64 bits"
time ./jaccardBitmap64 trump.txt > out.txt

echo "Many features per docs"
echo "Sparse vectors"
time ./jaccardSparse trumpJoin.txt > out.txt
echo "Bitmap 256 bits"
time ./jaccardBitmap trumpJoin.txt > out.txt
echo "Bitmap 64 bits"
time ./jaccardBitmap64 trumpJoin.txt > out.txt
