#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;
class IncorrectInput{};
template <class TYPE>
class Matrix{
private:
	int rawsNum;
	int columnsNum;
	TYPE** matrix;
public:
	Matrix(){
	};	
	Matrix(const unsigned int _rawsNum, const unsigned int _columnsNum){
		rawsNum = _rawsNum;
		columnsNum = _columnsNum;
		matrix = new TYPE* [_rawsNum];
		for (int i = 0; i < _rawsNum; i++){
			matrix[i] = new TYPE [_columnsNum];
		}
		for (int i = 0; i < _rawsNum; i++){
			for (int j = 0; j < _columnsNum; j++){
				TYPE temp(0);
				matrix[i][j] = temp;
			}
		}
	}
	Matrix(const Matrix& src){
		rawsNum = src.rawsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}
	}

	Matrix(Matrix&& src){
		rawsNum = src.rawsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}
		for (int i = 0; i < rawsNum; i++){
			src.matrix[i] = nullptr;
		}
		src.matrix = nullptr;
	}
	~Matrix(){
		for (int i = 0; i < rawsNum; i++ ){
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	Matrix Transpose(void) const{
		Matrix result(columnsNum, rawsNum);
		for (int i = 0; i < columnsNum; i++){
			for (int j = 0; j < rawsNum; j++){
				result.matrix[i][j] = matrix[j][i];
			}
		}
		return result;
	}
	TYPE getByIndex(int byRaw, int byColumn) const{
		if ((byRaw >= rawsNum) || (byRaw < 0)){
			throw out_of_range ("Raw index out of range");
		}
		if ((byColumn >= columnsNum) || (byColumn < 0)){
			throw out_of_range ("Column index out of range");
		}
		return matrix[byRaw][byColumn];
	}
	void putByIndex(unsigned int byRaw, unsigned int byColumn, TYPE value){
		if ((byRaw >= rawsNum) || (byRaw < 0)){
			throw out_of_range ("Raw index out of range");
		}
		if ((byColumn >= columnsNum) || (byColumn < 0)){
			throw out_of_range ("Column index out of range");
		}
		matrix[byRaw][byColumn] = value;
	}
	TYPE& operator () (unsigned int byRaw, unsigned int byColumn){
		if ((byRaw >= rawsNum) || (byRaw < 0)){
			throw out_of_range ("Raw index out of range");
		}
		if ((byColumn >= columnsNum) || (byColumn < 0)){
			throw out_of_range ("Column index out of range");
		}
		return matrix[byRaw][byColumn];		
	}
	Matrix& operator = (const Matrix& src){
		if ((rawsNum != src.rawsNum) || (columnsNum != src.columnsNum)){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		rawsNum = src.rawsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix& operator = (Matrix&& src){
		if ((rawsNum != src.rawsNum) || (columnsNum != src.columnsNum)){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		rawsNum = src.rawsNum;
		columnsNum = src.columnsNum;
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				matrix[i][j] = src.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix operator + (const Matrix& arg2) const{
		if ((rawsNum != arg2.rawsNum) || (columnsNum != arg2.columnsNum)){
			throw out_of_range("Incorrect size of 2nd arg");
		}
		Matrix result(rawsNum, columnsNum);
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				result.matrix[i][j] = matrix[i][j] + arg2.matrix[i][j];
			}
		}
		return result;
	}
	Matrix operator * (const Matrix& arg2) const{
		if (columnsNum != arg2.rawsNum){
			throw out_of_range("Incorrect size of 2nd arg");
		}

		Matrix result(rawsNum, arg2.columnsNum);
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				TYPE temp(0);
				for (int t = 0; t < columnsNum; t++){
					temp += (matrix[i][t] + arg2.matrix[t][j]);
				}
				result.matrix[i][j] = temp;
			}
		}
		return result;
	}
	Matrix operator | (const Matrix& arg2) const{
		if (rawsNum != arg2.rawsNum){
			throw out_of_range("Number of raws of 1st arg must be equal to number of raws of 2nd arg");
		}

		Matrix result(rawsNum, columnsNum + arg2.columnsNum);
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				result.matrix[i][j] = matrix[i][j];
			}
			for (int j = 0; j < arg2.columnsNum; j++){
				result.matrix[i][j + columnsNum] = arg2.matrix[i][j];
			}
		}
		return result;
	}
	Matrix operator * (const float k) const{
		Matrix result(rawsNum, columnsNum);
		for (int i = 0; i < rawsNum; i++){
			for (int j = 0; j < columnsNum; j++){
				result.matrix[i][j] = k * matrix[i][j];
			}
		}
		return result;
	}
};
class ComplexNumber{
private:
	float realPart;
	float imaginaryPart;
public:
	ComplexNumber(){
	};
	ComplexNumber(int param):
	realPart(0),
	imaginaryPart(0){
	}
	ComplexNumber(float _realPart, float _imaginaryPart):
	realPart(_realPart),
	imaginaryPart(_imaginaryPart){
	}
	ComplexNumber(const ComplexNumber& src){
		realPart = src.realPart;
		imaginaryPart = src.imaginaryPart;
	}
	ComplexNumber(ComplexNumber&& src){
		realPart = src.realPart;
		imaginaryPart = src.imaginaryPart;
	}
	~ComplexNumber(){
	}
	ComplexNumber& operator = (const ComplexNumber& src){
		realPart = src.realPart;
		imaginaryPart = src.imaginaryPart;
		return *this;
	}
	ComplexNumber& operator = (ComplexNumber&& src){
		realPart = src.realPart;
		imaginaryPart = src.imaginaryPart;
		return *this;
	}
	ComplexNumber operator + (const ComplexNumber& arg2) const{
		float realPartNew = realPart + arg2.realPart;
		float imaginaryPartNew = imaginaryPart + arg2.imaginaryPart;
		return ComplexNumber(realPartNew, imaginaryPartNew);
	}
	void print(){
		cout << "Real part: "      << realPart      << endl;
		cout << "Imaginary part: " << imaginaryPart << endl;
	}
	friend istream& operator >> (istream&, ComplexNumber&);
	friend ostream& operator << (ostream&, ComplexNumber&);
	friend istream& operator >> (istream&, ComplexNumber&&);
	friend ostream& operator << (ostream&, ComplexNumber&&);
};
const string sep =  "+i*";
istream& operator >> (istream& input, ComplexNumber& src){
	string sep_in;
		float realPart;
		float imaginaryPart;
		input >> realPart;
		input >> sep_in;
		if (sep_in != sep){
			throw IncorrectInput();
		}
		input >> imaginaryPart;
		src = ComplexNumber(realPart, imaginaryPart);
	return input;
}
istream& operator >> (istream& input, ComplexNumber&& src){
	string sep_in;
		float realPart;
		float imaginaryPart;
		input >> realPart;
		input >> sep_in;
		if (sep_in != sep){
			throw IncorrectInput();
		}
		input >> imaginaryPart;
		src = ComplexNumber(realPart, imaginaryPart);
	return input;
}
ostream& operator << (ostream& output, ComplexNumber& src){
	output << src.realPart<< " " << sep << " " << src.imaginaryPart << endl;
	return output;
}
ostream& operator << (ostream& output, ComplexNumber&& src){
	output << src.realPart<< " " << sep << " " << src.imaginaryPart << endl;
	return output;
}
int main()
{
	Matrix <int> matrix1(2, 3);
	Matrix <int> matrix2(2, 3);
	Matrix <int> matrix3(2, 3);
	Matrix <int> matrix4(3, 2);
	Matrix <ComplexNumber> matrix(1,2);
	for (int i = 0; i < 1; i++){
		for (int j = 0; j < 2; j++){
			cin >> matrix(i, j);
		}
	}
	for (int i = 0; i < 1; i++){
		for (int j = 0; j < 2; j++){
			// ComplexNumber value;
			// value = matrix.getByIndex(i, j);
			// cout << value;
			cout << matrix.getByIndex(i, j);
		}
	}
	ComplexNumber a(5);
	cout << a;
	cin >> a;
	cout << a;
	// cin >> matrix3;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			int value;
			value = matrix3.getByIndex(i, j);
			cout << value << " ";
		}
		cout << endl;
	}
	cout << "-----------" << endl;
	cout << "-----------" << endl;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			int value;
			cin >> value;
			matrix1.putByIndex(i, j, value);
		}
	}
	cout << "-----------" << endl;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			int value;
			cin >> value;
			matrix2.putByIndex(i, j, value);
		}
	}
	cout << "-----------" << endl;
	matrix3 = matrix1 + matrix2;
	matrix4 = matrix3.Transpose();
	
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			int value;
			value = matrix3.getByIndex(i, j);
			cout << value << " ";
		}
		cout << endl;
	}
	cout << "-----------" << endl;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 2; j++){
			int value;
			value = matrix4.getByIndex(i, j);
			cout << value << " ";
		}
		cout << endl;
	}
	try
	{
		matrix1 + matrix4;
	}
	catch(out_of_range &ex){
		cout << ex.what() << endl;
	}

	return 0;
}
