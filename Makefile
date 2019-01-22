CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -O -g -MMD  # use -MMD to generate dependencies
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
GTKLIBS = `pkg-config gtkmm-3.0 --libs --libs` 
OBJECTS = Subject.o Card.o Command.o Deck.o Player.o HumanPlayer.o ComputerPlayer.o Model.o Controller.o View.o Main.o # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=straights

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(GTKFLAGS) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(GTKLIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(GTKFLAGS) $(CXXFLAGS) $(GTKLIBS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
