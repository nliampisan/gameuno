COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++


gameuno: game.o player.o deck.o card.o 
	$(LINKER) game.o player.o deck.o card.o -o gameuno

test: test.o player.o deck.o card.o 
	$(LINKER) test.o player.o deck.o card.o -o test

game.o : game.cpp player.h deck.h card.h 
	$(COMPILER) $(COMPILER_FLAGS) game.cpp

test.o : test.cpp player.h deck.h card.h
	$(COMPILER) $(COMPILER_FLAGS) test.cpp

player.o : player.cpp player.h card.h 
	$(COMPILER) $(COMPILER_FLAGS) player.cpp 

deck.o : deck.cpp deck.h card.h 
	$(COMPILER) $(COMPILER_FLAGS) deck.cpp

card.o : card.cpp card.h 
	$(COMPILER) $(COMPILER_FLAGS) card.cpp

clean: 
	-rm -f *.o test gameuno

