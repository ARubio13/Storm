all: storm

storm:
	g++ -std=c++11 -o storm storm.cpp

clean:
	rm -f storm
