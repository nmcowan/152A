#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/tokenizer.hpp>

using namespace std;

int main(int argc, char *argv[]){

	ifstream DataBase, IP;
	string ipAddress, dataIP, mask, asNum, token, orig_dataIP, orig_ipAddress;
	ofstream output;
	string temp;
	output.open("output.txt");

	IP.open(argv[2]);

	while(getline(IP,ipAddress)){
		orig_ipAddress = ipAddress.substr(0, ipAddress.length());

		vector<string> addressIP, longestPrefix;
		vector<int> maskVector;
		maskVector.push_back(0);

		typedef boost::tokenizer<boost::char_separator<char>> tokenizerIP;
  		boost::char_separator<char> sep{"."};
  		tokenizerIP tokIP{ipAddress, sep};
  		for (const auto &t : tokIP)
  			addressIP.push_back(t);


		DataBase.open(argv[1]);

		while(getline(DataBase, temp,'\n')){
			//parse each line into appropriate field

			stringstream parse(temp);
			parse >> dataIP >> mask >> asNum;
			orig_dataIP = dataIP.substr(0,dataIP.length());


			//Create vector to store each byte of IP address
			vector<string> addressDB;

			int maskNum = atoi(mask.c_str());
			int orig_maskNum = maskNum;

			//Parse the IP address by "."
  			typedef boost::tokenizer<boost::char_separator<char>> tokenizerDB;
  			boost::char_separator<char> sepDB{"."};
  			tokenizerDB tokDB{dataIP, sepDB};
  			for (const auto &t : tokDB)
  				addressDB.push_back(t);

			//If the first byte matches and the current mask is greater than the last
			if( (!addressDB[0].compare(addressIP[0])) && (maskNum > maskVector.back()) ){
				maskNum -= 8;

				//For the other 3 bytes in the IP address
				for(int i = 1; i <= 3; i++){
					//If the mask is greater than 8 and the 2nd bytes are equal
					if(maskNum >= 8 && !addressIP[i].compare(addressDB[i])){
						maskNum -= 8;
						continue;
					} else if(maskNum >= 8 && addressIP[i].compare(addressDB[i])){
						break;
					}

					//If the mask is now less than 8
					if( (maskNum < 8)){
						//Convert strings to ints and shift the byte 
						int ipNum = atoi(addressIP[i].c_str());
						int dbNum = atoi(addressDB[i].c_str());

						int shiftIP = ipNum >> (8 - maskNum);
						int shiftDB = dbNum >> (8 - maskNum);

						if(shiftDB == shiftIP){

							//push the current mask 
							maskVector.push_back(orig_maskNum);

							//Add for final output
							dataIP.append("/");
							dataIP.append(mask);
							dataIP.append(" ");
							dataIP.append(asNum);
							dataIP.append(" ");
							dataIP.append(orig_ipAddress);
							longestPrefix.push_back(dataIP);
							break;
						}
					}

				}
			}


		}


		//check if empty
		if(!longestPrefix.empty())
			output << longestPrefix.back() << endl;
		else{
			output << "N/A" << endl;
		}

		DataBase.close();
		longestPrefix.clear();
	}

	output.close();
	IP.close();

return 0;
}