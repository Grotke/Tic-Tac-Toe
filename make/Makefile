PROJ_DIR = ..

PROJ_HEADERS = $(PROJ_DIR)/include

CPPFLAGS += -I$(PROJ_HEADERS) -lSDL2 -lSDL2_image

CXXFLAGS += -g -Wall -std=c++11

EXECUTABLE = Tic-Tac-Toe

all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) *.o

Button.o:
	$(CXX) $(CXXFLAGS) $(PROJ_DIR)/src/Button.cpp $(CPPFLAGS) -c -o Button.o

main.o:
	$(CXX) $(CXXFLAGS) $(PROJ_DIR)/src/main.cpp $(CPPFLAGS) -c -o main.o

$(EXECUTABLE): Button.o main.o 
	$(CXX) $(CXXFLAGS) $^ $(CPPFLAGS) -o $@




