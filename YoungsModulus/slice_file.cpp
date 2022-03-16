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

int leftnum = 0;//������ֵ
int midnum = 0;//������ֵ
int counter = 0;//�����¼�����˵ڼ���
double circleT = 0.5;//��ʼ��Ϊ0.5����Ϊ��һ��ѭ�����ضε�circleTimeΪ0.5��p.s.���Ҫж��-���أ���Ϊ1������Ҫ����mat1,mat2˳��&if(srcMatrixs(counter, 0) < 1)
bool flag = true;//�ж��Ǽ��ػ���ж�ؽ׶Σ����ؽ׶�Ϊtrue��ж��Ϊfalse��

void sliceMatrix(MatrixXd& srcMatrixs)
{
    for (counter = 0; counter < srcMatrixs.rows(); counter++)
    {
        //if (srcMatrixs(counter, 0) < 1)//����Ǽ���-ж������Ҫ���if��
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
                flag = false;//��һ��Ϊж�ؽ׶�
            }
            else
            {
                MatrixXd mat1 = srcMatrixs.middleRows(leftnum, midnum - leftnum);
                MatrixXd mat2 = srcMatrixs.middleRows(midnum, counter - midnum);
                leftnum = counter;
                circleT = srcMatrixs(counter, 0);
                flag = true;
                YoungsModulus_value(mat1, mat2, circleT);//ע�⣡��������ĳ���ж���ټ��أ�����Ҫ����mat1,mat2
            }

        }

    }
}