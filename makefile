COMPILE = clang++ -Wall -Wextra -Werror -ferror-limit=5 -lpthread main.cpp src/utils.cpp -o container

all:
	$(COMPILE)

clear:
	@ clear

list: clear
	@ $(COMPILE) && ./container list
map: clear
	@ $(COMPILE) && ./container map
queue: clear
	@ $(COMPILE) && ./container queue
stack: clear
	@ $(COMPILE) && ./container stack
vector: clear
	@ $(COMPILE) && ./container vector


const:
	@ printf "\n\x1B[0;31mYOU SHOULD HAVE 11 COMPILATION ERRORS NOT MORE OR LESS. THEY SHOULD ALL BE COMMENTED WITH OK.\x1B[0m\n\n"
	@ clang++ -Wall -Wextra -Werror const_main.cpp -o const_container && ./const_container
#Compile const program to test for const containers

clean:
	rm -f output/tmp_my output/tmp_real

fclean: clean
		rm -f container const_container a.out

re: fclean all
