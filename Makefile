all:
	gcc lib/src/*.c -o pickle -ljnxc -g 
increment:
	./lib/scripts/inc
install:
	sudo cp pickle /usr/bin
