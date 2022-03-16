#include "Header.h"

Matrix<double, Dynamic, Dynamic> final_E_value;
std::vector<double> final_vec;

int main(void)
{
    // source file
    string input_source = "C:\\Users\\diiii\\Desktop\\test\\src-7-69-12";

    // matrix to be loaded from a file
    MatrixXd matrix_source;

    // load the matrix from the file
    matrix_source = openData(input_source + ".csv");

    sliceMatrix(matrix_source);

    cout << "size of vector:" << final_vec.size() << endl;
    int sizeOfVec = final_vec.size();
    final_E_value = Map<MatXXdR>(final_vec.data(), sizeOfVec / 3, 3);

    string out_source = input_source + "_output.csv";

    saveData(out_source, final_E_value);

	return 0;
}