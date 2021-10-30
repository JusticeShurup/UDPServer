#include "iostream"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"

int fib(int number) {
	if (number == 0) {
		return 0;
	}
	else if (number <= 2) {
		return 1;
	}
	int a = 1, c = 1, b = 1;
	for (int i = 3; i <= number; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

int main() {
	Poco::Net::SocketAddress addr("127.0.0.1:1337");
	Poco::Net::DatagramSocket socket(addr);
	int last_seq = 0;
	int data[2] = { 0 };
	socket.receiveFrom(data, sizeof(int) * 2, addr);
	int seq = data[0];
   	int value = data[1];
	if (last_seq < seq) {
		last_seq = seq;
	}
	
	seq = 1;
	data[0] = seq;
	data[1] = fib(value);
	socket.sendTo(data, sizeof(int) * 2, addr);


	return 0;
}