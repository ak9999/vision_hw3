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

h1_obj=image.o h1.o
h2_obj=image.o h2.o
h3_obj=image.o h3.o
h4_obj=image.o h4.o

PROGRAM1=h1
PROGRAM2=h2
PROGRAM3=h3
PROGRAM4=h4

all: $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4)

$(PROGRAM1): $(h1_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(h1_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM2): $(h2_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(h2_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM3): $(h3_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(h3_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM4): $(h4_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(h4_obj) $(INCLUDES) $(LIBS_ALL)

package:
	(zip KHAN_HW3.zip *.h *.cc *.cpp Makefile README.txt)

output_simple_1:
	make clean_images
	./h1 hough_simple_1.pgm edge_simple_1.pgm
	./h2 edge_simple_1.pgm 150 binary_simple_1.pgm
	./h3 binary_simple_1.pgm h3output_simple_1.pgm array.txt

output_simple_2:
	make clean_images
	./h1 hough_simple_2.pgm edge_simple_2.pgm
	./h2 edge_simple_2.pgm 150 binary_simple_2.pgm
	./h3 binary_simple_2.pgm h3output_simple_2.pgm array.txt

output_complex_1:
	make clean_images
	./h1 hough_complex_1.pgm edge_complex.pgm
	./h2 edge_complex.pgm 150 binary_complex.pgm
	./h3 binary_complex.pgm h3output_complex.pgm array.txt

clean_images:
	(rm -f edge_*.pgm)
	(rm -f binary_*.pgm)
	(rm -f h3output_*.pgm)
	(rm -f array.txt)


clean:
	(rm -f *.o;)
	(rm -f h1;)
	(rm -f h2;)
	(rm -f h3;)
	(rm -f h4;)
	make clean_images
