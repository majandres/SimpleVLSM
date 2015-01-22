//Author: Andres Garcia de Alba
//
//Specification file for the class Network.


#ifndef NETWORK_H
#define NETWORK_H

class Network
{
public:
	void setAddress(int network[], int subnet[]);
	void setFirstAddress(int network[]);
	void setLastAddress(int network[], long int no_users[], int subnet[], int i);
	void setBroadcastAddress();
	void setMask(long int no_users[], int subnet[], int i);
	void printNet();
	void printFirst();
	void printLast();
	void printBroadcast();
	void printMask();
	Network(); // default constructor

private:
	int net_address[4];
	int first_address[4];
	int last_address[4];
	int broadcast[4];
	int mask[4];
};

#endif // !NETWORK_H