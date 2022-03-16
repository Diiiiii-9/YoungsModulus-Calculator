#include "Header.h"

void saveData(string fileName, MatrixXd  matrix)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(fileName);
    if (file.is_open())
    {
        file << matrix.format(CSVFormat);
        file.close();
    }
}

MatrixXd openData(string fileToOpen)
{
    // the matrix entries are stored in this variable row-wise. 
    vector<double> matrixEntries;

    // in this object we store the data from the matrix
    ifstream matrixDataFile(fileToOpen);

    // this variable is used to store the row of the matrix that contains commas 
    string matrixRowString;

    // this variable is used to store the matrix entry;
    string matrixEntry;

    // this variable is used to track the number of rows
    int matrixRowNumber = 0;

    getline(matrixDataFile, matrixRowString);//read the title and throw it. XD

    while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString
    {
        stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.

        while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
        {
            matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
        }
        matrixRowNumber++; //update the column numbers
    }

    // here we convet the vector variable into the matrix and return the resulting object, 
    // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

}

int leftnum = 0;//区间左值
int midnum = 0;//区间中值
int counter = 0;//负责记录处理到了第几行
double circleT = 0.5;//初始化为0.5（因为第一个循环加载段的circleTime为0.5）p.s.如果要卸载-加载，则为1，且需要更改mat1,mat2顺序&if(srcMatrixs(counter, 0) < 1)
bool flag = true;//判断是加载还是卸载阶段（加载阶段为true，卸载为false）

void sliceMatrix(MatrixXd& srcMatrixs)
{
    for (counter = 0; counter < srcMatrixs.rows(); counter++)
    {
        //if (srcMatrixs(counter, 0) < 1)//如果是加载-卸载则不需要这个if段
        //{
        //    leftnum = counter;
        //    continue;
        //}
        
        if (srcMatrixs(counter, 0) > circleT)
        {
            if (flag)
            {
                midnum = counter;
                circleT = srcMatrixs(counter, 0);
                flag = false;//下一次为卸载阶段
            }
            else
            {
                MatrixXd mat1 = srcMatrixs.middleRows(leftnum, midnum - leftnum);
                MatrixXd mat2 = srcMatrixs.middleRows(midnum, counter - midnum);
                leftnum = counter;
                circleT = srcMatrixs(counter, 0);
                flag = true;
                YoungsModulus_value(mat1, mat2, circleT);//注意！！！如果改成先卸载再加载，则需要调换mat1,mat2
            }

        }

    }
}