build:
	gcc -Wall -g tema1.c -o tema1

run: build
	./tema1

clean:
	rm -f tema1
