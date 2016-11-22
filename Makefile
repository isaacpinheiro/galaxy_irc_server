.PHONY: compile clean run

compile:
	gcc -c *.c
	gcc *.o -lpthread -o galaxy-irc-server

clean:
	rm *.o
	rm galaxy-irc-server

run:
	./galaxy-irc-server
