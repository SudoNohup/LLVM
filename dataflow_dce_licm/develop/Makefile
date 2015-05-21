all: licm-pass.so dce-pass.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0

%.so: %.o 
	$(CXX) -dylib -flat_namespace -shared $^ -o $@

licm-pass.o: licm-pass.cpp domAnalysis.h IDFA.h

dce-pass.o: dce-pass.cpp IDFA.h dceAnalysis.h

clean:
	rm -f *.o *~ *.so
