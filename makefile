COMPILER = clang
ARG = -c -Wall

ifeq ($(OS),Windows_NT)
	DELCMD = del
	EXTENSION = .exe
else
	DELCMD = rm
	EXTENSION =
endif

prog: main.o terminal_ui.o editdistance.o elementOps.o stringConstructor.o
	$(COMPILER) main.o terminal_ui.o editdistance.o elementOps.o stringConstructor.o
	-o EditDistance$(EXTENSION)

main.o: main.cpp terminal_ui.o editdistance.o stringConstructor.o
	$(COMPILER) $(ARG) main.cpp

terminal_ui.o: terminal_ui.cpp
	$(COMPILER) $(ARG) terminal_ui.cpp

editdistance.o: editdistance.cpp
	$(COMPILER) $(ARG) editdistance.cpp

elementOps.o: elementOps.cpp
	$(COMPILER) $(ARG) elementOps.cpp

stringConstructor.o: stringConstructor.cpp elementOps.o
	$(COMPILER) $(ARG) stringConstructor.cpp

clean:
	$(DELCMD) *.o

cleanbin:
	$(DELCMD) a$(EXTENSION)
	$(DELCMD) EditDistance$(EXTENSION)
