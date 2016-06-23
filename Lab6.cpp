#include <iostream>
#include <stdexcept>
using namespace std;
class IncorrectInput: public invalid_argument
{
};
template <class TYPE>
class Matrix{
private:
	size_t rowsNum;
	size_t columnsNum;
	TYPE** matrix;
public:
	Matrix(void){
	};	
	Matrix(const size_t _rowsNum, const size_t _columnsNum){
		rowsNum = _rowsNum;
		columnsNum = _columnsNum;
		matrix = new TYPE* [_rowsNum];
		for (int i = 0; i < _rowsNum; i++){
			matrix[i] = new TYPE [_columnsNum];
		}
		for (int i = 0; i < _rowsNum; i++){
			for (int j = 0; j < _columnsNum; j++){
				TYPE temp;
				matrix[i][j] = temp;
			}
		}
	}
	Matrix(const Matrix& src){
		rowsNum = src.rowsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}

	}
	Matrix(Matrix&& src){
		rowsNum = src.rowsNum;
		columnsNum = src.columnsNum;
		matrix = src.matrix;
		src.matrix = nullptr;
	}
	~Matrix(){
		for (int i = 0; i < rowsNum; i++ ){
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	Matrix Transpose(void) const{
		Matrix result(columnsNum, rowsNum);
		for (int i = 0; i < columnsNum; i++){
			for (int j = 0; j < rowsNum; j++){
				result.matrix[i][j] = matrix[j][i];
			}
		}
		return result;
	}
	TYPE& operator () (unsigned int byRaw, unsigned int byColumn){
		if (byRaw >= rowsNum){
			throw out_of_range ("Raw index out of range");
		}
		if ((byColumn >= columnsNum) || (byColumn < 0)){
			throw out_of_range ("Column index out of range");
		}
		return matrix[byRaw][byColumn];		
	}
	Matrix& operator = (const Matrix& src){
		if ((rowsNum != src.rowsNum) || (columnsNum != src.columnsNum)){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		rowsNum = src.rowsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix& operator = (Matrix&& src){
		if ((rowsNum != src.rowsNum) || (columnsNum != src.columnsNum)){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		rowsNum = src.rowsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix operator + (const Matrix& arg2) const{
		if ((rowsNum != arg2.rowsNum) || (columnsNum != arg2.columnsNum)){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		Matrix result(rowsNum, columnsNum);
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				result.matrix[i][j] = matrix[i][j] + arg2.matrix[i][j];
			}
		}
		return result;
	}
	Matrix operator * (const Matrix& arg2) const{
		if (columnsNum != arg2.rowsNum){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		Matrix result(rowsNum, arg2.columnsNum);
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				TYPE temp(0);
				for (int t = 0; t < columnsNum; t++){
					temp += (matrix[i][t] * arg2.matrix[t][j]);
				}
				result.matrix[i][j] = temp;
			}
		}
		return result;
	}
	Matrix operator | (const Matrix& arg2) const{
		if (rowsNum != arg2.rowsNum){
			throw out_of_range("Number of rows of 1st arg must be equal to number of rows of 2nd arg");
		}
		Matrix result(rowsNum, columnsNum + arg2.columnsNum);
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				result.matrix[i][j] = matrix[i][j];
			}
			for (int j = 0; j < arg2.columnsNum; j++){
				result.matrix[i][j + columnsNum] = arg2.matrix[i][j];
			}
		}
		return result;
	}
	Matrix operator * (const TYPE k) const{
		Matrix result(rowsNum, columnsNum);
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				result.matrix[i][j] = k * matrix[i][j];
			}
		}
		return result;
	}
	template <class TYPE_2>
	friend Matrix operator * (const TYPE_2, const Matrix&);
};

template <class TYPE_2>
Matrix<TYPE_2> operator * (const TYPE_2 k, const Matrix<TYPE_2>& src){
	Matrix<TYPE_2> result(src.rowsNum, src.columnsNum);
		for (int i = 0; i < src.rowsNum; i++){
			for (int j = 0; j < src.columnsNum; j++){
				result.matrix[i][j] = k * src.matrix[i][j];
			}
		}
		return result;
}
template <class TYPE>
class uniquePtr{
private:
	TYPE* ptr;
public:
	uniquePtr(TYPE* _ptr){
		ptr = _ptr;
	}
	uniquePtr(uniquePtr&& src){
		ptr = src.ptr;
		src.ptr = nullptr;
	}
	~uniquePtr(void){
		delete ptr;
	}
};
int main(){
	try{
		Matrix<int> matrix1(2, 3);
		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 3; j++){
				cin >> matrix1(i, j);
			}
		}
		cout << endl;
		Matrix<int> matrix2(3, 2);
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 2; j++){
				cin >> matrix2(i, j);
			}
		}
		cout << endl;
		Matrix<int> matrix3(3,3);
		matrix3 = matrix2 * matrix1;

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				cout << matrix3(i, j) << " ";
			}
			cout << endl;
		}
	}
	catch(out_of_range &ex){
		cout << ex.what() << endl;
	}
	return 0;
}
