#include "Header.h"

void YoungsModulus_value(MatrixXd mat1, MatrixXd mat2,int circleTime)
{

	// strain value
	vector<double> strain1;
	strain1.resize(mat1.rows());
	MatXXdR::Map(strain1.data(), mat1.col(3).rows(), 1) = mat1.col(3);
	// stress value
	vector<double> stress1;
	stress1.resize(mat1.rows());
	MatXXdR::Map(stress1.data(), mat1.col(2).rows(), 1) = mat1.col(2);
	// placeholder for storing polynomial coefficient
	vector<double> coeff1;
	vector<double> slope1;
	slope1 = polyfit(stress1, strain1, coeff1, 3);	//cubic polynomial

	// strain value
	vector<double> strain2;
	strain2.resize(mat2.rows());
	MatXXdR::Map(strain2.data(), mat2.col(3).rows(), 1) = mat2.col(3);
	// stress value
	vector<double> stress2;
	stress2.resize(mat2.rows());
	MatXXdR::Map(stress2.data(), mat2.col(2).rows(), 1) = mat2.col(2);
	// placeholder for storing polynomial coefficient
	vector<double> coeff2;
	vector<double> slope2;
	slope2 = polyfit(stress2, strain2, coeff2, 3);	//cubic polynomial

	//卸载段-x:stress-y:circ_strain
	vector<double> circ_strain;
	circ_strain.resize(mat2.rows());
	MatXXdR::Map(circ_strain.data(), mat2.col(4).rows(), 1) = mat2.col(4);
	vector<double> coeff3;
	vector<double> circ_slope;
	circ_slope = polyfit(stress2, circ_strain, coeff3, 3);

	double max_stress = mat1.col(2).maxCoeff();//计算最大和最小值
	double min_stress = mat1.col(2).minCoeff();

	vector<double> coeff;
	assert(slope1.size() == slope2.size());

	coeff.resize(slope1.size());

	for (int i = 0; i < slope1.size(); i++)
	{
		coeff[i] = slope1[i] - slope2[i];
	}

	vector<double> root;
	root = roots_2(coeff);

	if (root.size() == 0)
	{
		cout << "root.size() == 0" << endl;
		return;
	}

	vector<double> crossPoint;

	//判断两条曲线在有效区间内是否只有一个交点
	for (int i = 0; i < root.size(); i++)
	{
		if (root[i] < max_stress&& root[i] > min_stress)
		{
			crossPoint.push_back(root[i]);
		}
	}


	if (crossPoint.size() == 0)
	{
		cout << "crossPoint.size() == 0" << endl;
		return;
	}

	double E_point_stress = crossPoint[0];//弹性段特征点
	double E_value = pow(slope1[0] + slope1[1] * E_point_stress + slope1[2] * (pow(E_point_stress, 2)),-1)/10;//Gpa
	double circ_strain_slope = circ_slope[0] + circ_slope[1] * E_point_stress + circ_slope[2] * (pow(E_point_stress, 2));
	double v_value = circ_strain_slope / (slope1[0] + slope1[1] * E_point_stress + slope1[2] * pow(E_point_stress, 2));

	cout << "circleTime:" << circleTime << "  E_value:" << E_value << "  v_value:" << v_value << "  Cross_Point:" << crossPoint[0] << endl;
	final_vec.push_back(circleTime);
	final_vec.push_back(E_value);
	final_vec.push_back(v_value);

}