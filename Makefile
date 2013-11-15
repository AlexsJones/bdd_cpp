increment:
	./lib/scripts/inc lib/conf/settings.conf
all:
	gcc lib/src/*.c -o pickle -ljnxc -g
install:
	echo "Done"

