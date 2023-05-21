default: build

build:
	c99 net.c hashk.c hasht.c irc.c sircd.c -o sircd
	chmod +x sircd

install: build
	cp sircd.1 /usr/local/man/
	cp sircd /usr/local/bin/

clean:
	rm -f *.out sircd

test:
	# hasht
	c99 hashk.c hasht.c test/hasht.test.c -o test/hasht.out
	chmod +x test/hasht.out
	./test/hasht.out
