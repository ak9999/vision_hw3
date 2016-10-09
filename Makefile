# Makefile edited by Abdullah Khan

#FLAGS
C++FLAGS = -g -std=c++14 -Wall -pedantic

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAGS) $(INCLUDES) -c $< -o $@

.cpp.o:
	g++ $(C++FLAGS) $(INCLUDES) -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib

p1_obj=image.o h1.o
p2_obj=image.o h2.o
p3_obj=image.o h3.o
p4_obj=image.o h4.o

PROGRAM1=h1
PROGRAM2=h2
PROGRAM3=h3
PROGRAM4=h4

all: $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4)

$(PROGRAM1): $(h1_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p1_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM2): $(h2_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p2_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM3): $(h3_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p3_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM4): $(h4_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(p4_obj) $(INCLUDES) $(LIBS_ALL)

package:
	(zip KHAN_HW2.zip *.h *.cc *.cpp Makefile README.txt)

clean:
	(rm -f *.o;)
	(rm -f h1;)
	(rm -f h2;)
	(rm -f h3;)
	(rm -f h4;)
