

#include "readData.h"
#include <iostream>


readLog::readLog()
{

	count = 0;
}

readLog::~readLog()
{
}

std::vector<std::string> readLog::splitString(const std::string& strs)
{
	std::string temp;
	std::vector<std::string> splitOut;
	splitOut.clear();
	//std::cout << strs << " " << strs.size() << std::endl;
	for (int i = 0; i < strs.size(); i++)
	{
		if (strs[i] == ',')
		{
			splitOut.push_back(temp);
			temp = "";
		}
		else
		{
			temp = temp + strs[i];
		}

		if (i == strs.size() - 1)
		{
			splitOut.push_back(temp);
		}
	}
	return splitOut;
}


std::vector<std::string> splitStringwithSymbol(const std::string& strs, const std::string& symbol)
{
	std::string temp;
	std::vector<std::string> splitOut;
	splitOut.clear();

	for (int i = 0; i < strs.size(); i++)
	{
		//std::cout << strs[i] << std::endl;
		if (strs[i] == ' ')
		{


			splitOut.push_back(temp);
			temp = "";
		}
		else
		{

			temp = temp + strs[i];

			// std::cout << temp << std::endl;
		}

		if (i == strs.size() - 1) {
			splitOut.push_back(temp);
		}
	}
	return splitOut;
}

std::vector<std::string> readLog::splitWithSymbol(const std::string& strs, const std::string& splitWithSymbol)
{
	std::vector<std::string> strData;
	size_t pos = strs.find(splitWithSymbol, 0);
	std::string head = strs.substr(0, pos);
	if (pos == strs.npos)
		return std::vector<std::string>();
	strData.push_back(head);
	std::string tmpStr = strs.substr(pos + 1, strs.size());
	strData.push_back(tmpStr);
	return strData;
}

void readLog::parseLog()
{
	std::string strs;

	int LineNum0 = 0;
	int LineNum1 = 0;
	int BoudariesNum0 = 0;
	int BoudariesNum1 = 0;
	GNSSPos.clear();
	laneLine.clear();
	laneCenter.clear();
	while (std::getline(in_fp, strs))
	{
		std::vector<std::string> data = splitWithSymbol(strs, ":");
		if (data.size() != 2)
			continue;
		//std::cout << strs << std::endl;


		std::vector<std::string> logData = splitString(data[1]);
		if (data[0].compare("in_test_loc1") == 0)
		{
			if (stod(logData[0]) != 0)
			{
				point temp;
				temp.timeStamp = stoll(logData[0]);
				temp.lat = stod(logData[5]);
				temp.lon = stod(logData[6]);
				temp.heading = stod(logData[7] ) ;
				temp.linkId = stoi(logData[2]);
				GNSSPos.push_back(temp );
				GNSSPosMap.insert(std::make_pair(temp.timeStamp, temp));

			}
		}

		if (data[0].compare("in_test_loc") == 0)
		{
			//std::cout << strs << std::endl;
			if (stod(logData[0]) != 0)
			{
				point temp;
				temp.timeStamp = stoll(logData[0]);
				temp.lat = stod(logData[5]);
				temp.lon = stod(logData[6]);
				temp.heading = stod(logData[7]) *57.3;
				temp.linkId = stoi(logData[2]);
				GNSSPos.push_back(temp);
				GNSSPosMap.insert(std::make_pair(temp.timeStamp, temp));

			}
		}


		//if (data[0].compare("in_test_ekf") == 0)
		//{
		//	{
		//		point temp;
		//		temp.timeStamp = stoll(logData[0]);
		//		temp.lat = stod(logData[1]) ;
		//		temp.lon = stod(logData[2]) ;
		//		temp.heading = stod(logData[3]);
		//		EKF.push_back(temp);
		//	}
		//}


		if (data[0].compare("in_test_line_left1") == 0)
		{

			int geometry_size = std::stoi(logData[5]);

			int readNUm = logData.size();
			line line;
			line.lineid = stoi(logData[2]);
			line.side = stoi(logData[3]);
			line.linkId = stoi(logData[0]);
			for (int i = 0; i < geometry_size; i++)
			{

				point temp;
				temp.lon = std::stod(logData[2 * i + 8]) * 0.001;
				temp.lat = std::stod(logData[2 * i + 9]) * 0.001;
				line.points.push_back(temp);

			}
			laneLine.insert(std::make_pair(line.lineid, line));
		}


		if (data[0].compare("in_test_line_") == 0)
		{

			int geometry_size = std::stoi(logData[5]);
			line line;
			line.lineid = stoi(logData[2]);
			line.side = 1;// stoi(logData[3]);
			line.linkId = stoi(logData[0]);

			for (int i = 0; i < geometry_size; i++)
			{
				point temp;
				temp.lon = std::stod(logData[2 * i + 7]) ;
				temp.lat = std::stod(logData[2 * i + 8]) ;
				line.points.push_back(temp);

			}
			laneLine.insert(std::make_pair(line.lineid, line));
		}


		//if (data[0].compare("in_test_line_lane") == 0)
		//{
		//	tmpLaneMarking.linkid = std::stoi(logData[0]);
		//	tmpLaneMarking.laneid = std::stoi(logData[1]);
		//	int geometry_size = std::stoi(logData[3]);

		//	line line;
		//	line.lineid = std::stoi(logData[1]);
		//	line.side = 1;
		//	for (int i = 0; i < geometry_size; i++)
		//	{
		//		point temp;
		//		temp.lon = std::stod(logData[2 * i + 4]) * 0.001;
		//		temp.lat = std::stod(logData[2 * i + 5]) * 0.001;
		//		line.points.push_back(temp);

		//	}
		//	laneCenter.insert(std::make_pair(line.lineid, line));
		//}

		if (data[0].compare("in_test_line_right") == 0)
		{

			int geometry_size = std::stoi(logData[5]);
			line line;
			line.lineid = stoi(logData[2]);
			line.side = stoi(logData[3]);
			line.linkId = stoi(logData[0]);
			for (int i = 0; i < geometry_size; i++)
			{

				point temp;
				temp.lon = std::stod(logData[2 * i + 8]) * 0.001;
				temp.lat = std::stod(logData[2 * i + 9]) * 0.001;
				line.points.push_back(temp);

			}

			laneLine.insert(std::make_pair(line.lineid, line));
		}


	
		if (data[0].compare("Out_Road_line1") == 0)
		{
			ARoadLine line;
			if (logData.size() > 11)
			{
				line.Id = std::stoll(logData[3]);
				line.Position = (afLinePosition)std::stoi(logData[4]);
				line.LineA0 = std::stod(logData[6]);
				line.LineA1 = std::stod(logData[7]);
				line.LineA2 = std::stod(logData[8]);
				line.LineA3 = std::stod(logData[9]);
				line.LineStart = std::stoi(logData[10]);
				line.LineEnd = std::stoi(logData[11]);
				uint64_t time = std::stoll(logData[2]);
				//roadLine.push_back(std::make_pair(time, line));



				auto iter = OutLine.find(time);
				if (iter != OutLine.end())
				{
					roadLines tmp = iter->second;
			
					tmp.line.push_back(line);
					tmp.count++;
					
					OutLine.erase(iter->first);
					OutLine.insert(std::make_pair(time, tmp));
				}
				else
				{
					roadLines tmp;
					tmp.line.push_back(line);
					tmp.count = 1;
					OutLine.insert(std::make_pair(time, tmp));
				}
			}

		}

		
			if (data[0].compare("Out_Road_line") == 0)
			{
				ARoadLine line;
				if (logData.size() > 11)
				{
					line.Id = std::stoll(logData[3]);
					line.Position = (afLinePosition)std::stoi(logData[4]);
					line.LineA0 = std::stod(logData[6]);
					line.LineA1 = std::stod(logData[7]);
					line.LineA2 = std::stod(logData[8]);
					line.LineA3 = std::stod(logData[9]);
					line.LineStart = std::stoi(logData[10]);
					line.LineEnd = std::stoi(logData[11]);
					uint64_t time = std::stoll(logData[2]);
					//roadLine.push_back(std::make_pair(time, line));

					auto iter = Outbound.find(time);
					if (iter != Outbound.end())
					{
						roadLines tmp = iter->second;

						tmp.line.push_back(line);
						tmp.count++;

						Outbound.erase(iter->first);
						Outbound.insert(std::make_pair(time, tmp));
					}
					else
					{
						roadLines tmp;
						tmp.line.push_back(line);
						tmp.count = 1;
						Outbound.insert(std::make_pair(time, tmp));
					}
				}

			}


		if (data[0].compare("in_LD_line") == 0)
		{
			if (logData.size() < 12) continue;
			ARoadLine line;
			line.Id = std::stoll(logData[4]);

			line.Position = (afLinePosition)std::stoi(logData[5]);
			line.LineA0 = std::stod(logData[7]);
			line.LineA1 = std::stod(logData[8]);
			line.LineA2 = std::stod(logData[9]);
			line.LineA3 = std::stod(logData[10]);
			line.LineStart = std::stoi(logData[11]);
			line.LineEnd = std::stoi(logData[12]);
			uint64_t time = std::stoll(logData[0]);
			//if (line.Position == 2 || line.Position == 3)
			{
				LDLine.push_back(std::make_pair(time, line));
			}

		}

		if (data[0].compare("in_LD_Boudary") == 0)
		{
			if (logData.size() < 12) continue;
			ARoadLine line;
			line.Id = std::stoll(logData[4]);
			line.Position = (afLinePosition)std::stoi(logData[5]);
			line.LineA0 = std::stod(logData[7]);
			line.LineA1 = std::stod(logData[8]);
			line.LineA2 = std::stod(logData[9]);
			line.LineA3 = std::stod(logData[10]);
			line.LineStart = std::stoi(logData[11]);
			line.LineEnd = std::stoi(logData[12]);
			uint64_t time = std::stoll(logData[0]);
			LDBoudary.push_back(std::make_pair(time, line));
		}

		//if (data[0].compare("in_test_diff") == 0)
		//{

		//	LineError line;
		//	uint64_t time = std::stoll(logData[0]);
		//	double  A0 = std::stod(logData[1]);
		//	double  A1 = std::stod(logData[2]);
		//	line.timeStamp = time;
		//	line.A0 = A0;
		//	line.A1 = A1;
		//	lineError.insert(std::make_pair(time, line));

		//}


		//if (data[0].compare("leftMapLine") == 0)
		//{
		//	linecoeff line;
		//	uint64_t time = std::stoll(logData[0]);
		//	line.timeStamp = time;
		//	line.left = std::stod(logData[1]);
		//	line.right = std::stod(logData[3]);
		//	MapA0.push_back(std::make_pair(time, line));
		//}


		//if (data[0].compare("leftMapLineA1") == 0)
		//{
		//	linecoeff line;
		//	uint64_t time = std::stoll(logData[0]);
		//	line.timeStamp = time;
		//	line.left = std::stod(logData[1]);
		//	line.right = std::stod(logData[3]);
		//	MapA1.push_back(std::make_pair(time, line));
		//}

		//if (data[0].compare("leftLDLine") == 0)
		//{
		//	linecoeff line;
		//	uint64_t time = std::stoll(logData[0]);
		//	line.timeStamp = time;
		//	line.left = std::stod(logData[1]);
		//	line.right = std::stod(logData[3]);
		//	LDA0.push_back(std::make_pair(time, line));
		//}


		//if (data[0].compare("leftLDLineA1") == 0)
		//{
		//	linecoeff line;
		//	uint64_t time = std::stoll(logData[0]);
		//	line.timeStamp = time;
		//	line.left = std::stod(logData[1]);
		//	line.right = std::stod(logData[3]);
		//	LDA1.push_back(std::make_pair(time, line));
		//}

		//if (data[0].compare("in_test_locA0") == 0)
		//{
		//	linecoeff line;
		//	uint64_t time = std::stoll(logData[0]);
		//	line.timeStamp = time;
		//	line.left = std::stod(logData[1]);
		//	line.right = std::stod(logData[2]);

		//	if(line.timeStamp > 0)
		//	LocA0.push_back(std::make_pair(time, line));
		//}

		//if (data[0].compare("check_fail") == 0)
		//{
		//	if (stod(logData[0]) != 0)
		//	{
		//		failTime.push_back(stoll(logData[0]));

		//	}
		//}

		if (data[0].compare("In") == 0)
		{
			std::vector<std::string> logData = splitStringwithSymbol(data[1], " ");


			//std::cout << logData.size()<< std::endl;

			uint64_t time = stod(logData[3]);
			point temp;
			temp.timeStamp = stoll(logData[3]);
			temp.lat = stod(logData[5]);
			temp.lon = stod(logData[7]);
			temp.heading = stod(logData[11]);

			if (temp.lat > 0)
			{
				GNSSPosOrg.push_back(temp);
			}


		}

		if (data[0].compare("outLine") == 0)
		{
			if (logData.size() < 12) continue;
			ARoadLine line;
			line.LineA0 = std::stod(logData[2]);
			line.LineA1 = std::stod(logData[4]);
			line.LineA2 = std::stod(logData[6]);
			line.LineA3 = std::stod(logData[8]);
			line.LineStart = std::stod(logData[10]) * 1000.0;
			line.LineEnd = std::stod(logData[12]) * 1000.0;
			uint64_t time = std::stoll(logData[0]);



			auto iter = MapLine.find(time);
			if (iter != MapLine.end())
			{
				roadLines tmp = iter->second;

				tmp.line.push_back(line);
				tmp.count++;

				MapLine.erase(iter->first);
				MapLine.insert(std::make_pair(time, tmp));
			}
			else
			{
				roadLines tmp;
				tmp.line.push_back(line);
				tmp.count = 1;
				MapLine.insert(std::make_pair(time, tmp));
			}
		}
	}

	std::cout << count << std::endl;
}

void readLog::setFileName(const std::string& logName)
{
	in_fp.open(logName.c_str());
	if (!in_fp)
	{
		std::cout << "open fail" << std::endl;
	}
}
