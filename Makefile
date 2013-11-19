all:
	gcc lib/src/*.c -o pickle -ljnxc -g 
increment:
	./lib/scripts/inc
install:
	cp pickle /usr/bin
	mkdir -p /usr/share/pickle
	cp -r lib/framework /usr/share/pickle
clean:
	rm  /usr/bin/pickle
	rm -rf /usr/share/pickle	
