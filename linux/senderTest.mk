CXX=g++

EXE_DIR = executables

LDFLAGS=-lm -pthread -g -Wall

INCLUDES = -I./../sourceCode/threadBase/ \
-I./../sourceCode/ptrQueue/ \
-I./../sourceCode/k_Time/ \
-I./../sourceCode/threadedUdpReceiver/ \
-I./../sourceCode/udpSender/

OBJS = ../sourceCode/k_time.o \
../sourceCode/ptrQueue.o \
../sourceCode/threadBase.o \
../sourceCode/udpSender.o \
../sourceCode/treadedUdpReceiver.o \
../sourceCode/tests/senderMain.o \
	
%.o: %.cpp
	$(CXX) -g -c -o $@ $< $(INCLUDES)

senderTest.out: $(OBJS)
	$(CXX) -o $(EXE_DIR)/$@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE_DIR)/senderTest.out

