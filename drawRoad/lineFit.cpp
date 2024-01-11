/*
 * @Author: niew nie_w@reachauto.com
 * @Date: 2023-04-20 15:09:32
 * @LastEditors: niew nie_w@reachauto.com
 * @LastEditTime: 2023-04-20 15:16:22
 * @FilePath: \roadFusion\includes\lineFit.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%A
 */

#include "lineFit.h"

LineFit::LineFit()
{
		
}

Eigen::VectorXd LineFit::GetLinecoeff(vector<double> &Vx, vector<double> &Vy, int order)
{

	Eigen::VectorXd coeff;
	coeff.setZero();
	//if (Vx.size() < 3)
	//{
	//	std::vector<double> outVecPointX, outVecPointY;
	//	outVecPointX.clear();
	//	outVecPointY.clear();
	//	std::shared_ptr<CubicSpline1D> pcsp = std::make_shared<CubicSpline1D>(Vx,Vy);
	//	for (auto i = Vx[0]; i < Vx[Vx.size() - 1]; i = i + 0.5)
	//	{
	//		outVecPointX.push_back(i);
	//		outVecPointY.push_back(pcsp->calc_der0(i));
	//	}
	//	double i = Vx[Vx.size() - 1];
	//	outVecPointX.push_back(i);
	//	outVecPointY.push_back(pcsp->calc_der0(i));
	//	coeff = FitterLeastSquareMethod(outVecPointX, outVecPointY, 3);
	//}
	//else
	{
		coeff = FitterLeastSquareMethod(Vx, Vy, 3);
	}

	return coeff;
}

LineFit::~LineFit()
{
}

Eigen::VectorXd LineFit::FitterLeastSquareMethod(vector<double> &X, vector<double> &Y, int orders)
{
	Eigen::Map<Eigen::VectorXd> xvals(X.data(), X.size());
	Eigen::Map<Eigen::VectorXd> yvals(Y.data(), Y.size());
	Eigen::MatrixXd A(xvals.size(), orders + 1);
	for (int i = 0; i < xvals.size(); i++)
	{
		A(i, 0) = 1.0;
	}
	for (int j = 0; j < xvals.size(); j++)
	{
		for (int i = 0; i < orders; i++)
		{
			A(j, i + 1) = A(j, i) * xvals(j);
		}
	}
	Eigen::VectorXd result = A.householderQr().solve(yvals);
	return result;
}