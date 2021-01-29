Snakes:SnakesNLadders.o DE1SoCfpga.o Player.o Person.o Computer.o
	g++ SnakesNLadders.o DE1SoCfpga.o Player.o Person.o Computer.o -o Snakes

SnakesNLadders.o: SnakesNLadders.cpp DE1SoCfpga.h 
	g++ -g -Wall -c SnakesNLadders.cpp

DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -g -Wall -c DE1SoCfpga.cpp

SnakesNLadders.o: SnakesNLadders.cpp Player.h
	g++ -g -Wall -c SnakesNLadders.cpp

Player.o: Player.cpp Player.h
	g++ -g -Wall -c Player.cpp

SnakesNLadders.o: SnakesNLadders.cpp Person.h Computer.h
	g++ -g -Wall -c SnakesNLadders.cpp

Person.o: Person.cpp Person.h
	g++ -g -Wall -c Person.cpp

Computer.o: Computer.cpp Computer.h
	g++ -g -Wall -c Computer.cpp

clean:
	rm SnakesNLadders.o DE1SoCfpga.o Player.o Person.o Computer.o Snakes

