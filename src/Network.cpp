//Author: Andres Garcia de Alba
//
//Implementation file for the class Network.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Network.h"
#include "VLSMfunctions.h"

using namespace std;


void Network::setAddress(int network[], int subnet[]){
	for (int i = 0; i < 4; i++){
		if (subnet[i] > 0)
		{
			//network octets of net_address[] is based on subnet[] and set according to network[]
			net_address[i] = network[i];
		}
		else
		{
			net_address[i] = 0;
			network[i] = 0;
		}
	}//end of for loop
}

void Network::setMask(long int no_users[], int subnet[], int i){
	long int temp = totalUsers(no_users[i]);
	
	//if <= 254 users, subnet will increment in the 4th octet.
	//and subnet will be 255.255.255.?
	if (temp <= 254)
	{
		//first 3 octets get set to 255
		mask[0] = 255;
		mask[1] = 255;
		mask[2] = 255;
		mask[3] = subMask(no_users[i]); //return subnet mask;

		//must update subnet[] since the other networks rely on it
		subnet[0] = mask[0];
		subnet[1] = mask[1];
		subnet[2] = mask[2];
		subnet[3] = mask[3];
	}
	//else <= 65534, subnet will increment in the 3rd octet.
	//and subnet will be 255.255.?.0
	else if (temp <= 65534)
	{
		//first 2 octets get set to 255
		mask[0] = 255;
		mask[1] = 255;
		mask[2] = subMask(no_users[i]); //return subnet mask;
		mask[3] = 0;

		//must update subnet[] since the other networks rely on it
		subnet[0] = mask[0];
		subnet[1] = mask[1];
		subnet[2] = mask[2];
		subnet[3] = mask[3];
	}
	//else <= 16777214, subnet will increment in the 2nd octet.
	//and subnet will be 255.?.0.0
	else if (temp <= 16777214)
	{
		//only the 1st octet is set to 255
		mask[0] = 255;
		mask[1] = subMask(no_users[i]); //return subnet mask
		mask[2] = 0;
		mask[3] = 0;

		//must update subnet[] since the other networks rely on it
		subnet[0] = mask[0];
		subnet[1] = mask[1];
		subnet[2] = mask[2];
		subnet[3] = mask[3];
	}
	//else <= 4294967294, subnet will increment in the 1st octet.
	//and subnet will be ?.0.0.0
	else if (temp <= 4294967294)
	{
		mask[0] = subMask(no_users[i]); //return subnet mask
		mask[1] = 0;
		mask[2] = 0;
		mask[3] = 0;

		//must update subnet[] since the other networks rely on it
		subnet[0] = mask[0];
		subnet[1] = mask[1];
		subnet[2] = mask[2];
		subnet[3] = mask[3];
	}
}
	
void Network::setFirstAddress(int network[]){
	//address is set according to network[] with an increment of 1 in the last octet
	first_address[0] = network[0];
	first_address[1] = network[1];
	first_address[2] = network[2];
	first_address[3] = network[3] + 1;
}

void Network::setLastAddress(int network[], long int no_users[], int subnet[], int i){
	long int temp = totalUsers(no_users[i]);

	//if users is less than or eq to 254, last address will occur in the 4th octet
	if (temp <= 254)
	{
		last_address[0] = network[0];
		last_address[1] = network[1];
		last_address[2] = network[2];
		last_address[3] = first_address[3] + temp - 1;
	}
	//else if users is less than or eq to 65534, last address will occur in the 3rd octet
	else if (temp <= 65534) 
	{
		last_address[0] = network[0];
		last_address[1] = network[1];
		last_address[2] = network[2] + magicNumber(subnet, 2) - 1;
		last_address[3] = 254;
	}
	//else if users is less than or eq to 16777214, last address will occur in the 2nd octet
	else if (temp <= 16777214)
	{
		last_address[0] = network[0];
		last_address[1] = network[1] + magicNumber(subnet, 1) - 1;
		last_address[2] = 255;
		last_address[3] = 254;
	}
	//else if users is less than or eq to 4294967294, last address will occur in the 1st octet
	else if (temp <= 4294967294)// slash 4
	{
		last_address[0] = network[0] + magicNumber(subnet, 0) - 1;
		last_address[1] = 255;
		last_address[2] = 255;
		last_address[3] = 254;
	}
}

void Network::setBroadcastAddress(){
	//address is set according to last_address with an increment of 1 in the last octet
	broadcast[0] = last_address[0];
	broadcast[1] = last_address[1];
	broadcast[2] = last_address[2];
	broadcast[3] = last_address[3] + 1;
}

void Network::printNet(){
	string net;

	ofstream outfile;
	outfile.open("outTemp.txt");

	outfile << net_address[0] << "." << net_address[1] << "." << net_address[2] << "." << net_address[3];
	outfile.close();

	ifstream infile;
	infile.open("outTemp.txt");

	getline(infile, net);
	infile.close();

	remove("outTemp.txt");

	cout << net;
}

void Network::printFirst(){
	string net;

	ofstream outfile;
	outfile.open("outTemp.txt");

	outfile << first_address[0] << "." << first_address[1] << "." << first_address[2] << "." << first_address[3];
	outfile.close();

	ifstream infile;
	infile.open("outTemp.txt");

	getline(infile, net);
	infile.close();

	remove("outTemp.txt");

	cout << net;
}

void Network::printLast(){
	string net;

	ofstream outfile;
	outfile.open("outTemp.txt");

	outfile << last_address[0] << "." << last_address[1] << "." << last_address[2] << "." << last_address[3];
	outfile.close();

	ifstream infile;
	infile.open("outTemp.txt");

	getline(infile, net);
	infile.close();

	remove("outTemp.txt");

	cout << net;
}

void Network::printBroadcast(){
	string net;

	ofstream outfile;
	outfile.open("outTemp.txt");

	outfile << broadcast[0] << "." << broadcast[1] << "." << broadcast[2] << "." << broadcast[3];
	outfile.close();

	ifstream infile;
	infile.open("outTemp.txt");

	getline(infile, net);
	infile.close();

	remove("outTemp.txt");

	cout << net;
}

void Network::printMask(){
	string net;

	ofstream outfile;
	outfile.open("outTemp.txt");

	outfile << mask[0] << "." << mask[1] << "." << mask[2] << "." << mask[3];
	outfile.close();

	ifstream infile;
	infile.open("outTemp.txt");

	getline(infile, net);
	infile.close();

	remove("outTemp.txt");

	cout << net;
}

Network::Network()
{
	for (int i = 0; i < 4; i++){
		net_address[i] = 0;
	}
	for (int i = 0; i < 4; i++){
		first_address[i] = 0;
	}
	for (int i = 0; i < 4; i++){
		last_address[i] = 0;
	}
	for (int i = 0; i < 4; i++){
		broadcast[i] = 0;
	}
	for (int i = 0; i < 4; i++){
		mask[i] = 0;
	}
}