#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include <unordered_map>
#include "data.h"

class  readLog
{
public:
	readLog();
	~ readLog();

	std::vector<std::string> splitString(const std::string& strs);
	void parseLog();
	void setFileName(const std::string& logName);
	std::vector<std::string> splitWithSymbol(const std::string& strs, const std::string& splitWithSymbol);

 	AFusionRoads sCameraLine = {0};
	std::vector<point> GNSSPos;

	std::vector<point> GNSSPosOrg;

	std::vector<uint64_t> failTime;



	std::map<uint64_t, point > GNSSPosMap;

	std::vector<point> EKF;
	std::map<int, line> laneLine;
	
	std::map<uint64_t, LineError> lineError;




	std::map<uint64_t, roadLines> OutLine;

	std::map<uint64_t, roadLines>  Outbound;

	std::vector<std::pair<uint64_t, ARoadLine>> roadLine;
	std::vector<std::pair<uint64_t, ARoadLine>> LDLine;
	std::vector<std::pair<uint64_t, ARoadLine>> LDBoudary;
	std::vector<std::pair<uint64_t, line>> centerLine;

	std::vector<std::pair<uint64_t, linecoeff>> MapA0;
	std::vector<std::pair<uint64_t, linecoeff>> MapA1;
	std::vector<std::pair<uint64_t, linecoeff>> LDA0;
	std::vector<std::pair<uint64_t, linecoeff>> LDA1;
	std::vector<std::pair<uint64_t, linecoeff>>  LocA0;


	std::map<uint64_t, line> laneCenter;

	std::map<uint64_t, roadLines> MapLine;


private:
	std::ifstream in_fp;

	int count;


};

