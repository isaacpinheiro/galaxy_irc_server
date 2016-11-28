.PHONY: build clean run

build:
	gcc -c *.c
	gcc *.o -lpthread -o galaxy-irc-server

clean:
	rm *.o
	rm galaxy-irc-server

run:
	./galaxy-irc-server 127.0.0.1
