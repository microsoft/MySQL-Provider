CC = g++
PROGRAM = testMySqlAPI
SOURCE = testMySqlAPI.cpp

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) -g -o $(PROGRAM) $(SOURCE) `mysql_config --cflags` `mysql_config --libs`

clean:
	 rm -f $(PROGRAM) *~
