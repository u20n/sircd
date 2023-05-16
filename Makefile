default: build

build:
	c99 net.c irc.c sircd.c -o sircd
	chmod +x sircd

install: build
	cp sircd.1 /usr/local/man/
	cp sircd /usr/local/bin/

clean:
	rm -f *.o sircd
