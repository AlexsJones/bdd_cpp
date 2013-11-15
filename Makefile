increment:
	./lib/scripts/inc
all:
	gcc lib/src/*.c -o pickle -ljnxc -g
install:
	echo "Done"

