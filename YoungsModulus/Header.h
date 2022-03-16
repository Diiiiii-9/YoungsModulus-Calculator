#pragma once
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/QR>
#include <unsupported/Eigen/Polynomials>

using namespace std;
using namespace Eigen;//使用之前需要把Eigen库添加

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatXXdR;
extern Matrix<double, Dynamic, Dynamic> final_E_value;//全局变量；最终的矩阵
extern std::vector<double> final_vec;//全局变量；最终的向量组

//slice_file.cpp
void saveData(string fileName, MatrixXd  matrix);
MatrixXd openData(string fileToOpen);
//void sliceMatrixByCircleTime(MatrixXd& srcMatrix);
void sliceMatrix(MatrixXd& srcMatrixs);

//YoungsModulus.cpp
void YoungsModulus_value(MatrixXd mat1, MatrixXd mat2, int circleTime);

//function.cpp
vector<double> roots_2(const std::vector<double>& coeffs);
std::vector<double> polyfit(const std::vector<double>& t, const std::vector<double>& v, std::vector<double>& coeff, int order);
std::vector<double> slope_value(const std::vector<double>& coeff);