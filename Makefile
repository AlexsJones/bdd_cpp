all:
	gcc lib/src/*.c -o pickle -ljnxc -g 
increment:
	./lib/scripts/inc
install:
	mv pickle /usr/bin
	mkdir -p /usr/share/pickle
	cp -r lib/framework /usr/share/pickle
uninstall:
	rm  /usr/bin/pickle
	rm -rf /usr/share/pickle	
