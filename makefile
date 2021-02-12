fout=server
compiler=gcc
logfile=/tmp/HTTPserver.log
input=server.c

build:
	${compiler} src/$(input) src/lib/make_log.c -o ${fout}

run:
	./getIP.sh | ./${fout}

localhost:
	echo 127.0.0.1 | ./${fout}

log:
	cat ${logfile}
clean:
	rm ${fout}

cleanall:
	rm ${fout}
	rm ${logfile}

make commit:
	git add .
	git commit -m
