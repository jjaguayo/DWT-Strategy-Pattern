GCC = g++
CCFLAGS = -I../hdrs
LDFLAGS = 

testdwt: testdwt.o haar1DTransform.o
	$(GCC) -o $@ $+

testdwt.o: ../src/testdwt.cpp
	$(GCC) $(CCFLAGS) -o $@ -c $<

haar1DTransform.o: ../src/haar1DTransform.cpp
	$(GCC) $(CCFLAGS) -o $@ -c $<

clean: 
	rm -f haar1DTransform.o testdwt.o testdwt

