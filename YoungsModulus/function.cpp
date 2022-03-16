#include "Header.h"

//求二次函数的根
vector<double> roots_2(const std::vector<double>& coeffs) 
{
	assert(coeffs.size() == 3); //判断是否是二次函数
	double a = coeffs[2];
	double b = coeffs[1];
	double c = coeffs[0];
	double delta = b * b - 4 * a * c;

	vector<double> ans;
	//p.s.有部分数据没有交点，这里采取的处理办法是抛弃此数据
	if (delta > 0)
	{
		double ans1 = (-b + sqrt(delta)) / (2 * a);
		ans.push_back(ans1);
		double ans2 = (-b - sqrt(delta)) / (2 * a);
		ans.push_back(ans2);
	}
	return ans;
}


//求斜率值
std::vector<double> slope_value(const std::vector<double>& coeff)
{
	vector<double> slope;
	assert(coeff.size() == 4);//判断是否为三次多项式拟合
	slope.resize(coeff.size()-1);
	//导数值计算
	for (int i = 1; i < coeff.size(); i++)
	{
		slope[i-1] = i * coeff[i];
	}
	return slope;
}


//多项式拟合
std::vector<double> polyfit(const std::vector<double>& t, const std::vector<double>& v, std::vector<double>& coeff, int order)
{
	MatrixXd T(t.size(), order + 1);
	VectorXd V = VectorXd::Map(&v.front(), v.size());
	VectorXd result;

	//检查输入是否正确
	assert(t.size() == v.size());
	assert(t.size() >= order + 1);

	for (size_t i = 0; i < t.size(); ++i)
	{
		for (size_t j = 0; j < order + 1; ++j)
		{
			T(i, j) = pow(t.at(i), j);
		}
	}
	//cout << T << endl;

	// 最小二乘拟合
	result = T.householderQr().solve(V);
	coeff.resize(order + 1);
	for (int k = 0; k < order + 1; k++)
	{
		coeff[k] = result[k];
	}

	vector<double> slope;
	slope = slope_value(coeff);

	return slope;
}