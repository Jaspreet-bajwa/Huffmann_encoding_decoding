CXX = g++
CXXFLAGS = -g -std=c++14
RM = rm

all: decoder encoder

clean: 
	$(RM) *.o encoder decoder

encoder: encoder.o pheap.o binaryHeap.o fourheap.o
	$(CXX) $(CXXFLAGS) -o encoder encoder.o pheap.o binaryHeap.o fourheap.o


encoder.o: encoder.cpp pheap.h binaryHeap.h fourheap.h
	$(CXX) $(CXXFLAGS) -c encoder.cpp


pheap.o: pheap.h	

binaryHeap.o: binaryHeap.h

fourheap.o: fourheap.h

decoder: decoderTree.o decoder.o encoder.o
	$(CXX) $(CXXFLAGS) -o decoder decoderTree.o decoder.o 

decoderTree.o: decoderTree.cpp decoder.h 
	$(CXX) $(CXXFLAGS) -c decoderTree.cpp

decoder.o: decoder.h
