build:
	gcc src/server.c src/lib/make_log.c -o server01

run:
	./startserver.sh | ./server01

localhost:
	echo 127.0.0.1 | ./server01

clean:
	rm server01

cleanall:
	rm server01
	ls -A | grep .out | xargs rm
	ls -A | grep .log | xargs rm

make commit:
	git add .
	git commit -m
