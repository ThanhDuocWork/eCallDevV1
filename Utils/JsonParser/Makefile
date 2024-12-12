main: JsonParser.o libJsonParser.so 
	g++ Example/TestParserJson.cpp -o Example/main -lJsonParser

libJsonParser.so: 
	g++ -shared -o Libs/libJsonParser.so JsonParser.o -ljson-c
	sudo cp Libs/libJsonParser.so /usr/lib

JsonParser.o: libjson-c.so libjson-c.so.5
	g++ -c -fpic Src/JsonParser.cpp

libjson-c.so: 
	sudo cp Libs/JsonC/Src/libjson-c.so.5 /usr/lib
libjson-c.so.5: 
	sudo cp Libs/JsonC/Src/libjson-c.so.5 /usr/lib
