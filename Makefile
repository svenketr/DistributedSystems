LIBS = -lprotobuf-c -lpthread -lssl

SRC = lsp.cpp connection.cpp functions.cpp lspmessage.pb-c.c \
	connectionInfo.cpp serializer.cpp MessageReceiver.cpp \
	MessageProcessor.cpp inbox.cpp MessageSender.cpp \
	lsppacket.cpp RequestMessageProcessor.cpp ServerMessageProcessor.cpp \
	WorkerMessageProcessor.cpp epoch.cpp lsp_server.cpp lsp_client.cpp

# -lpthread -> includes the pthread library for linking
build:
	g++ -g -o server server.cpp $(SRC) $(LIBS)
	g++ -g -o request client.cpp $(SRC) $(LIBS)
	g++ -g -o worker worker.cpp $(SRC) $(LIBS)

clean:
	rm -f *.o *.gch *.s server request worker client
	
#test:
#	g++ -Wall -g -c SHA tempSHAgenerator.cpp
#	g++ -g -c server server.cpp $(SRC)
#	g++ -g -c request client.cpp $(SRC)
#	g++ -g -c worker worker.cpp $(SRC)# DO NOT DELETE
# DO NOT DELETE

# For compiling we do not need the -lssl option.
# -l option is only used for linking. It is required while building
#compile:
#	g++ -S tempSHAgenerator.cpp
#	g++ -S server.cpp $(SRC)
#	g++ -S client.cpp $(SRC)
#	g++ -S worker.cpp $(SRC)
#	
