CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJ = main.o Univers.o Mouton.o Loup.o SelsMineraux.o Herbe.o Entite.o Animal.o
DEPS = Univers.h Mouton.h Loup.h SelsMineraux.h Herbe.h Entite.h Animal.h

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

simulation: $(OBJ)
	$(CXX) -o $@ $^ -lpthread

.PHONY: clean

clean:
	rm -f *.o simulation
