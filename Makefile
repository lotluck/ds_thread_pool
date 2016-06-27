ROOTPATH = $(shell pwd)
SRC      = $(ROOTPATH)/src
HEAD     = $(ROOTPATH)/head
BIN      = $(ROOTPATH)/bin
LIB      = $(ROOTPATH)/lib

all : collect
	cd $(SRC) && $(CC) test.c -o test -lpthread_pool -L$(LIB)  -pthread -I$(HEAD)
	@mv $(SRC)/test $(BIN)
collect:
	cd $(SRC) && $(CC) -fpic -shared pthread_pool.c -o libpthread_pool.so -I$(HEAD)
	@mv $(SRC)/libpthread_pool.so $(LIB)
	/sbin/ldconfig $(LIB)

.PHONY:clean
clean:
	@cd $(LIB) && rm -fr libpthread_pool.so
	@rm -fr $(BIN)/test
