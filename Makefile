CC=gcc
CFLAGS=-O2
AVX=-mavx2

jaccard:
	gcc -o jaccardSparse jaccardSparse.c HashTrie.c SparseVector.c -O2
	gcc -o jaccardBitmap jaccardBitmap.c HashTrie.c bitmap.c -mavx2 -O2

clean:
	rm jaccardSparse jaccardBitmap
