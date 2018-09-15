all:Iot

Iot: 
	gcc *.c -o Iot.out -lcrypto -lssl -lwiringPi

clean:
	rm -rf *.gch Iot.out