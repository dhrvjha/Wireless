build:
	gcc server/server01.c server/make_log.c -o server01

run:
	./server01

clean:
	rm server01

cleanall:
	rm server01
	ls -A | grep .out | xargs rm
	ls -A | grep .log | xargs rm

make commit:
	git add .
	git commit -m
