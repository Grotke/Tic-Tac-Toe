PROJ_DIR = ..

PROJ_HEADERS = $(PROJ_DIR)/include

CPPFLAGS += -I$(PROJ_HEADERS) -lSDL2 -lSDL2_image

CXXFLAGS += -g -Wall -std=c++11

EXECUTABLE = Tic-Tac-Toe

all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) *.o


ltexture.o:
	$(CXX) $(CXXFLAGS) $(PROJ_DIR)/src/ltexture.cpp $(CPPFLAGS) -c -o ltexture.o

button.o:
	$(CXX) $(CXXFLAGS) $(PROJ_DIR)/src/button.cpp $(CPPFLAGS) -c -o button.o
main.o:
	$(CXX) $(CXXFLAGS) $(PROJ_DIR)/src/main.cpp $(CPPFLAGS) -c -o main.o

$(EXECUTABLE): ltexture.o button.o main.o 
	$(CXX) $(CXXFLAGS) $^ $(CPPFLAGS) -o $@




