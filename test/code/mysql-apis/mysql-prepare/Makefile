CC = g++
PROGRAM = testMySqlPrepare
SOURCE = testMySqlPrepare.cpp

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) -g -Wunused -o $(PROGRAM) $(SOURCE) `mysql_config --cflags` `mysql_config --libs`

clean:
	 rm -f $(PROGRAM) *~
