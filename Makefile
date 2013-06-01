proj4:	main.c branchsim.c branchsim.h
	gcc -Wall -g -o proj4 main.c branchsim.c

clean:	
	rm proj4 *~
