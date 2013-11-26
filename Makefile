PROGRAM = project

OBJECTS = User.o Micropost.o UserManager.o ProjectService.o




all: $(PROGRAM) Main.cpp

$(PROGRAM):	$(OBJECTS)
	g++ -o $(PROGRAM) $(OBJECTS) Main.cpp $(CPPOPTIONS)

Micropost.o: Micropost.cpp Micropost.h
	g++ -c $(CPPOPTIONS) $<

User.o: User.cpp User.h
	g++ -c $(CPPOPTIONS) $<

UserManager.o: UserManager.cpp UserManager.h
	g++ -c $(CPPOPTIONS) $<

ProjectService.o: ProjectService.cpp ProjectService.h
	g++ -c $(CPPOPTIONS) $<

clean:
	rm -f *.o $(PROGRAM)
