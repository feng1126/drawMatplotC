/*
 * @Author: niew nie_w@reachauto.com
 * @Date: 2023-04-20 15:09:32
 * @LastEditors: niew nie_w@reachauto.com
 * @LastEditTime: 2023-04-20 15:16:22
 * @FilePath: \roadFusion\includes\lineFit.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%A
 */
#ifndef _LINE_FITH_
#define _LINE_FITH_

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <cstring>
#include "Eigen/Dense"
//#include "CubicSpline1D.h"
using namespace std;

class LineFit
{
public:
	LineFit();
	~LineFit();
	Eigen::VectorXd GetLinecoeff(vector<double> &Vx, vector<double> &Vy, int order);

private:
	Eigen::VectorXd FitterLeastSquareMethod(vector<double> &X, vector<double> &Y, int orders);


};

#endif /* _LINE_FITH_ */