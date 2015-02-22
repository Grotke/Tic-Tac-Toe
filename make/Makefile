PROJ_DIR = ..

PROJ_HEADERS = $(PROJ_DIR)/include

PROJ_SOURCE = $(PROJ_DIR)/src

CPPFLAGS += -I$(PROJ_HEADERS) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

CXXFLAGS += -g -Wall -std=c++11

EXECUTABLE = Tic-Tac-Toe

all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) *.o

ai.o:  $(PROJ_SOURCE)/ai.cpp $(PROJ_HEADERS)/ai.h	
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/ai.cpp $(CPPFLAGS) -c -o ai.o

timer.o: $(PROJ_SOURCE)/timer.cpp $(PROJ_HEADERS)/timer.h	
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/timer.cpp $(CPPFLAGS) -c -o timer.o

ltexture.o: $(PROJ_SOURCE)/ltexture.cpp $(PROJ_HEADERS)/ltexture.h
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/ltexture.cpp $(CPPFLAGS) -c -o ltexture.o

board.o: $(PROJ_SOURCE)/board.cpp $(PROJ_HEADERS)/board.h $(PROJ_HEADERS)/timer.h $(PROJ_HEADERS)/ltexture.h
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/board.cpp $(CPPFLAGS) -c -o board.o

screen.o: $(PROJ_SOURCE)/screen.cpp  $(PROJ_HEADERS)/screen.h  $(PROJ_HEADERS)/button.h $(PROJ_HEADERS)/ltexture.h	
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/screen.cpp $(CPPFLAGS) -c -o screen.o

button.o: $(PROJ_SOURCE)/button.cpp  $(PROJ_HEADERS)/button.h  $(PROJ_HEADERS)/customevents.h  $(PROJ_HEADERS)/ltexture.h $(PROJ_HEADERS)/customevents.h 
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/button.cpp $(CPPFLAGS) -c -o button.o

screengenerator.o: $(PROJ_SOURCE)/screengenerator.cpp $(PROJ_HEADERS)/screengenerator.h $(PROJ_HEADERS)/button.h  $(PROJ_HEADERS)/customevents.h  $(PROJ_HEADERS)/screen.h 
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/screengenerator.cpp $(CPPFLAGS) -c -o screengenerator.o

main.o: $(PROJ_SOURCE)/main.cpp $(PROJ_HEADERS)/board.h  $(PROJ_HEADERS)/customevents.h $(PROJ_HEADERS)/screen.h $(PROJ_HEADERS)/screengenerator.h
	$(CXX) $(CXXFLAGS) $(PROJ_SOURCE)/main.cpp $(CPPFLAGS) -c -o main.o

$(EXECUTABLE): ai.o timer.o ltexture.o board.o screen.o button.o screengenerator.o main.o 
	$(CXX) $(CXXFLAGS) $^ $(CPPFLAGS) -o $@




