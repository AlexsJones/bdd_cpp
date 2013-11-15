increment:
	./lib/scripts/increment
all:
	gcc lib/src/*.c -o pickle -ljnxc -g
install:
	echo "Done"

