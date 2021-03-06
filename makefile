fout=server
compiler=gcc
logfile=/tmp/HTTPserver.log
input=server.c
additonal_lib=src/lib/make_log.c src/lib/readyserver.c src/lib/accept.c src/lib/parser.c src/lib/handler.c

build:
	${compiler} src/$(input) $(additonal_lib) -o ${fout}

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
	git commit
