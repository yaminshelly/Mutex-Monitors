run: consumer.o supplier.o vending-machine.o
	gcc consumer.o supplier.o vending-machine.o  -o scheduler-analyzer -pthread 
consumer.o : consumer.c
	gcc -c  consumer.c
supplier.o : supplier.c
	gcc -c supplier.c
vending-machine.o : vending-machine.c
	gcc -c vending-machine.c 
	
clean:
	rm -f $(binaries) *.o run
	
	
executable:
	$(CC) $(CFLAGS) $(SOURCES) $(LIBRARIES) -o $(BINARIES)

default: executable
