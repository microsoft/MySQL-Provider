CC = g++
PROGRAM = testMySqlRealQuery
SOURCE = testMySqlRealQuery.cpp

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) -Wl,-rpath=/tmp -g -o $(PROGRAM) $(SOURCE) `mysql_config --cflags` `mysql_config --libs`

clean:
	 rm -f $(PROGRAM) *~
