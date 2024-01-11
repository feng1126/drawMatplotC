#pragma once

#include <map>
#include <vector>
#include "aFRoad.h"


struct point
{
    uint64_t timeStamp;
    double lat;
    double lon;
    double heading;
    int linkId;

};

struct line
{
    uint64_t timeStamp;
    int side;
    int lineid;
    int linkId;
    std::vector<point> points;

};

struct LineError
{
    uint64_t timeStamp;
    double  A0;
    double  A1;

};


struct linecoeff
{
    uint64_t timeStamp;
    double  left;
    double  right;

};


struct  roadLines
{
    uint64_t timeStamp;
    //ARoadLine line[50];
    std::vector<ARoadLine> line;
    int count;
};

