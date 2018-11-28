build: main.o dataReader.o lineQueue.o merge.o mergeQueue.o
	gcc -Wpedantic -g main.o dataReader.o mergeQueue.o lineQueue.o merge.o -o coolsort -pthread

main.o: main.c dataReader.h merge.h entry.h mergeQueue.h
	gcc -Wpedantic -g -c main.c -o main.o
dataReader.o: dataReader.c dataReader.h lineQueue.h entry.h
	gcc -Wpedantic -g -c dataReader.c -o dataReader.o
lineQueue.o: lineQueue.c lineQueue.h
	gcc -Wpedantic -g -c lineQueue.c -o lineQueue.o
merge.o: merge.h merge.c entry.h
	gcc -Wpedantic -g -c merge.c -o merge.o
mergeQueue.o: mergeQueue.h mergeQueue.c entry.h
	gcc -Wpedantic -g -c mergeQueue.c -o mergeQueue.o
clean:
	rm -f *.o