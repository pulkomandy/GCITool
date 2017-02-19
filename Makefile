#
# Makefile
# pulkomandy, 2017-02-17 20:32
#

main: main.cpp Application.cpp Window.cpp
	$(CC) -o main main.cpp -lbe -lshared

# vim:ft=make
#
