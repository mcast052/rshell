all: src/connections.h 
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o rshell
	mkdir bin
	mv rshell bin
rshell: src/connections.h
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o rshell
	mkdir bin 
	mv rshell bin
clean: 
	rm -r bin	
