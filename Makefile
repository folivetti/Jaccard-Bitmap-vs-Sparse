CC=gcc
CFLAGS=-O2

jaccard:
	$(CC) -o jaccardSparse jaccardSparse.c HashTrie.c SparseVector.c $(CFLAGS) 
	$(CC) -o jaccardBitmap jaccardBitmap.c HashTrie.c bitmap.c -mavx2  $(CFLAGS)
	$(CC) -o jaccardBitmap64 jaccardBitmap64.c HashTrie.c -mavx2  $(CFLAGS)

clean:
	rm jaccardSparse jaccardBitmap jaccardBitmap64
