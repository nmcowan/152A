#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char *argv[]){

	ifstream DataBase, IP;
	string ipAddress, dataIP, mask, asNum, token, orig_dataIP, orig_ipAddress;
	vector<string> address;

	int i = 0;
	DataBase.open(argv[1]);
	IP.open(argv[2]);

	while(IP >> ipAddress){
		orig_ipAddress = ipAddress.substr(0, ipAddress.length());
		int posIP = ipAddress.find(".");

		while(DataBase >> dataIP >> mask >> asNum){

			int maskNum = atoi(mask.c_str());

			orig_dataIP = dataIP.substr(0, dataIP.length());
			int posDB = dataIP.find(".");

			string firstIP = ipAddress.substr(0,posIP);
			string firstDB = dataIP.substr(0, posDB);

			//if first digits match 
			if(!firstIP.compare(firstDB)){
				cout << "match " << dataIP << endl;
				int shift = (ipNum >> 32 - maskNum);
				cout << "shift " << shift << endl;
			}

		}
	}


	DataBase.close();
	IP.close();

return 0;
}