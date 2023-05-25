FLAGS = -pedantic-errors -std=c++11

game: main.o choosefile.o default.o fightenemy.o filemanip.o instructions.o printgrid.o stats.o storyline.o
	g++ $(FLAGS) $^ -o $@

main.o: main.cpp choosefile.h default.h fightenemy.h filemanip.h instructions.h printgrid.h stats.h storyline.h
	g++ $(FLAGS) -c $<

choosefile.o: choosefile.cpp choosefile.h filemanip.h storyline.h
	g++ $(FLAGS) -c $<

default.o: default.cpp default.h fightenemy.h instructions.h printgrid.h stats.h storyline.h
	g++ $(FLAGS) -c $<

fightenemy.o: fightenemy.cpp fightenemy.h default.h storyline.h stats.h instructions.h
	g++ $(FLAGS) -c $<

filemanip.o: filemanip.cpp filemanip.h default.h stats.h storyline.h
	g++ $(FLAGS) -c $<

instructions.o: instructions.cpp instructions.h filemanip.h printgrid.h storyline.h stats.h default.h
	g++ $(FLAGS) -c $<

printgrid.o: printgrid.cpp printgrid.h default.h
	g++ $(FLAGS) -c $<

stats.o: stats.cpp stats.h storyline.h
	g++ $(FLAGS) -c $<

storyline.o: storyline.cpp storyline.h
	g++ $(FLAGS) -c $<

clean:
	rm *.o output

.PHONY: clean
