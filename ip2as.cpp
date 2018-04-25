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
		int posIP = ipAddress.find(".");
		vector<string> longestPrefix;
		vector<int> maskVector;
		maskVector.push_back(0);

		DataBase.open(argv[1]);


		while(DataBase >> dataIP >> mask >> asNum){
			orig_dataIP = dataIP.substr(0,dataIP.length());
			vector<string> addressIP, addressDB;
			int maskNum = atoi(mask.c_str());
			int orig_maskNum = maskNum;

			if(maskNum < maskVector.back()){
				break;
			}

			typedef boost::tokenizer<boost::char_separator<char>> tokenizerIP;
  			boost::char_separator<char> sep{"."};
  			tokenizerIP tokIP{ipAddress, sep};
  			for (const auto &t : tokIP)
  				addressIP.push_back(t);

  			typedef boost::tokenizer<boost::char_separator<char>> tokenizerDB;
  			boost::char_separator<char> sepDB{"."};
  			tokenizerDB tokDB{dataIP, sepDB};
  			for (const auto &t : tokDB)
  				addressDB.push_back(t);

			//if first digits match 
			if(!addressDB[0].compare(addressIP[0])){
				maskNum -= 8;
				for(int i = 1; i <= 3; i++){
					if(maskNum >= 8 && !addressIP[i].compare(addressDB[i])){
						maskNum -= 8;
					} else if(maskNum >= 8 && addressIP[i].compare(addressDB[i])){
						break;
					}

					if(maskNum < 8){
						int ipNum = atoi(addressIP[i].c_str());
						int dbNum = atoi(addressDB[i].c_str());

						int shiftIP = ipNum >> (8 - maskNum);
						int shiftDB = dbNum >> (8 - maskNum);


						if(shiftDB == shiftIP){
							maskVector.push_back(orig_maskNum);

							dataIP.append("/");
							dataIP.append(mask);
							dataIP.append(" ");
							dataIP.append(asNum);
							dataIP.append(" ");
							dataIP.append(orig_ipAddress);
							longestPrefix.push_back(dataIP);
							continue;
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