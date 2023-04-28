#include "Domino.h"
#include <string>

using namespace std;

int countOfTrue(bool** matrix, int n) {
	int count = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j]) 
				count++;
	return count/2;
}

bool findTrue(bool** matrix, int n, int &iPlace, int &jPlace) {
	bool flag = false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j]) {
				flag = true;
				iPlace = i;
				jPlace = j;
				i = n;
				j = n;
			}
	return flag;
}

bool findLastTrue(bool** matrix, int n, int& iPlace, int& jPlace) {
	bool flag = false;
	for (int i = n - 1; i >= 0; i--)
		for (int j = n - 1; j >= 0; j--) 
			if (matrix[i][j]) {
				flag = true;
				iPlace = i;
				jPlace = j;
				i = -1;
				j = -1;
			}
	return flag;
}

int maxElementOfMatrix(int** matrix, int n) {
	int max = matrix[0][0];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j] > max)
				max = matrix[i][j];
	return max;
}

void findDominoPlace(int** matrix, int n, int dominoNumber, int& iPlace, int& jPlace) {
	for (int i = n - 1; i >= 0; i--)
		for (int j= n - 1; j >= 0; j--)
			if (matrix[i][j] == dominoNumber) {
				iPlace = i;
				jPlace = j;
				i = -1;
				j = -1;
			}
}

bool matrixComparison(bool** a1, bool** a2, int n) {
	bool flag = true;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a1[i][j] != a2[i][j])
				flag = false;
	return flag;
}

void removeOneSentence(string& str) { //лучше last 
	int index = str.size() - 2;
	while (str[index] != '\n' && index > 0)
		index--;
	str.erase(index + 1);
}

void removeSpecificSentence(string& str, int number, int n) {
	int index = str.size() - 2;
	int countOfSentences = n * n / 2;
	while (countOfSentences >= number) {
		index--;
		if (str[index] == '\n')
			countOfSentences--;
	}
	str.erase(index + 1);
}

string createString(int i, int j, bool flag) {
	string current;
	current += "(";
	current += to_string(i);
	current += ":";
	current += to_string(j);
	current += ")";
	current += " - ";
	if (!flag) current += "горизонтально";
	else current += "вертикально";
	current += '\n';
	return current;
}

void printMatrix(bool** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void printMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void removeDomino(bool**& isVertical, int**& occupiedCells, int n, string& dominoPositions) {
	int countOfVertical = countOfTrue(isVertical, n);
	bool flag1 = false;
	switch (countOfVertical) {
	case 0:
		for (int i = n - 1; i >= n - 2; i--)
			for (int j = n - 1; j >= n - 2; j--) {
				occupiedCells[i][j] = 0;
				isVertical[i][j] = true;
			}
		/*removeOneSentence(dominoPositions);
		removeSpecificSentence(dominoPositions, n * n / 2 - n * 2 - 1, n);*/
		/*printMatrix(occupiedCells, n);
		printMatrix(isVertical, n);*/
		break;
	case 2:
		int iVertical, jVertical;
		flag1 = findTrue(isVertical, n, iVertical, jVertical);
		if (jVertical == 0 && iVertical == 0 && isVertical[iVertical][n - 1]) { //переход на 4 доминошки
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = false;
				}
			for (int i = n - 1; i >= n - 2; i--)
				for (int j = n - 1; j >= n - 4; j--) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = true;
				}
			/*for (int i=0; i<4; i++)
				removeOneSentence(dominoPositions);*/
			/*printMatrix(occupiedCells, n);
			printMatrix(isVertical, n);*/
		}
		else if (jVertical != 0) { //не самая левая позиция - переводим левее
			for (int i = iVertical + 1; i >= iVertical; i--)
				for (int j = jVertical + 1; j >= jVertical; j--) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = false;
				}
			for (int i = iVertical + 1; i >= iVertical; i--)
				for (int j = jVertical - 1; j >= jVertical - 2; j--) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = true;
				}
			/*printMatrix(occupiedCells, n);
			printMatrix(isVertical, n);*/
		}
		else if (jVertical == 0 && isVertical[iVertical][jVertical + 1]) { //самая левая позиция - одна справа, одна слева
			for (int i = iVertical; i <= iVertical + 1; i++) 
				for (int j = jVertical + 1; j < n - 1; j++) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = false;
				}
			for (int i = iVertical; i <= iVertical + 1; i++) {
				occupiedCells[i][n - 1] = 0;
				isVertical[i][n - 1] = true;
			}
			/*printMatrix(occupiedCells, n);
			printMatrix(isVertical, n);*/
		}
		else if (jVertical == 0 && isVertical[iVertical][n - 1]) { //по бокам - поднимаем выше на 1
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = false;
				}
			for (int i = iVertical - 1; i <= iVertical; i++)
				for (int j = n - 2; j <= n - 1; j++) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = true;
				}
			/*printMatrix(occupiedCells, n);
			printMatrix(isVertical, n);*/
		}
		break;
	case 4:
		int iVertical1, jVertical1, iVertical2, jVertical2;
		flag1 = findTrue(isVertical, n, iVertical1, jVertical1);
		bool falg2 = findLastTrue(isVertical, n, iVertical2, jVertical2);
		if (iVertical1 == 0 && jVertical1 == 0 && iVertical2 == n - 1 && jVertical2 == n - 1 //вертикальные по краям
			&& isVertical[iVertical1][n - 1] && isVertical[iVertical2][0]) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = true;
				}
		}
		else if (iVertical1 == 0 && jVertical1 == 0 && iVertical2 == 1 && jVertical2 == 3) { // вертикальные в самом начале
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					occupiedCells[i][j] = 0;
					isVertical[i][j] = false;
				}
			for (int i = 0; i < 2; i++) {
				isVertical[i][0] = true;
				isVertical[i][n - 1] = true;
			}
			for (int i = n - 2; i < n; i++) {
				isVertical[i][0] = true;
				isVertical[i][n - 1] = true;
			}
		}
		else {
			if (jVertical1 != 0) { //не самая левая позиция - переводим левее
				for (int i = iVertical1 + 1; i >= iVertical1; i--)
					for (int j = jVertical1 + 1; j >= jVertical1; j--) {
						occupiedCells[i][j] = 0;
						isVertical[i][j] = false;
					}
				for (int i = iVertical1 + 1; i >= iVertical1; i--)
					for (int j = jVertical1 - 1; j >= jVertical1 - 2; j--) {
						occupiedCells[i][j] = 0;
						isVertical[i][j] = true;
					}
				/*printMatrix(occupiedCells, n);
				printMatrix(isVertical, n);*/
			}
			else if (jVertical1 == 0 && iVertical1 != 0) {
				for(int i = iVertical1; i <= iVertical1 + 1; i++) 
					for (int j = 0; j <= 1; j++) {
						occupiedCells[i][j] = 0;
						isVertical[i][j] = false;
					}
				for (int i = iVertical1 - 2; i <= iVertical1 - 1; i++)
					for (int j = n - 2; j <= n - 1; j++) {
						occupiedCells[i][j] = 0;
						isVertical[i][j] = true;
					}
				/*printMatrix(occupiedCells, n);
				printMatrix(isVertical, n);*/
			}
			else if (jVertical1 == 0 && iVertical1 == 0) {
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++) {
						occupiedCells[i][j] = 0;
						isVertical[i][j] = false;
					}
				if (jVertical2 != 1) { //просто двигаем влево
					jVertical2 = jVertical2 - 2;
					for (int i = iVertical2 - 1; i <= iVertical2; i++)
						for (int j = jVertical2 - 1; j <= jVertical2; j++) {
							occupiedCells[i][j] = 0;
							isVertical[i][j] = true;
						}
					if (jVertical2 != 1) {
						iVertical1 = iVertical2;
						jVertical1 = jVertical2 - 2;
					}
					else {
						iVertical1 = iVertical2 - 2;
						jVertical1 = n - 1;
					}
					for (int i = iVertical1 - 1; i <= iVertical1; i++)
						for (int j = jVertical1 - 1; j <= jVertical1; j++) {
							occupiedCells[i][j] = 0;
							isVertical[i][j] = true;
						}
					/*printMatrix(occupiedCells, n);
					printMatrix(isVertical, n);*/
				}
				else {
					iVertical2 = iVertical2 - 2;
					jVertical2 = n - 1;
					for (int i = iVertical2 - 1; i <= iVertical2; i++)
						for (int j = jVertical2 - 1; j <= jVertical2; j++) {
							occupiedCells[i][j] = 0;
							isVertical[i][j] = true;
						}
					iVertical1 = iVertical2;
					jVertical1 = jVertical2 - 2;
					for (int i = iVertical1 - 1; i <= iVertical1; i++)
						for (int j = jVertical1 - 1; j <= jVertical1; j++) {
							occupiedCells[i][j] = 0;
							isVertical[i][j] = true;
						}
					/*printMatrix(occupiedCells, n);
					printMatrix(isVertical, n);*/
				}
			}
		}
		break;
	}
	//bool flag = false;
	//int i = 0;
	//int j = 0;
	//bool** previousVertical = new bool*[n];
	//for (int i = 0; i < n; i++)
	//	previousVertical[i] = new bool[n];
	//for (int i = 0; i < n; i++)
	//	for (int j = 0; j < n; j++)
	//		previousVertical[i][j] = isVertical[i][j];
	//int currentRemovedDomino = 0;
	//if (!findTrue(isVertical, n, i, j)) {
	//	while (!flag) {
	//		currentRemovedDomino = maxElementOfMatrix(occupiedCells, n);
	//		findDominoPlace(occupiedCells, n, currentRemovedDomino, i, j);
	//		occupiedCells[i][j] = 0;
	//		occupiedCells[i][j - 1] = 0;
	//		removeOneSentence(dominoPositions);
	//		printMatrix(occupiedCells, n);
	//		if (i != n - 1) {
	//			isVertical[i][j] = true;
	//			isVertical[i + 1][j] = true;
	//			isVertical[i][j - 1] = true;
	//			isVertical[i + 1][j - 1] = true;
	//			/*if (!matrixComparison(isVertical, previousVertical, n)) 
	//				flag = true;*/
	//			flag = true;
	//			printMatrix(isVertical, n);
	//		}
	//	}
	//}
	//else {
	//	int iVertical, jVertical;
	//	flag = findTrue(isVertical, n, iVertical, jVertical);
	//	while (occupiedCells[iVertical][jVertical] != 0) {
	//		currentRemovedDomino = maxElementOfMatrix(occupiedCells, n);
	//		findDominoPlace(occupiedCells, n, currentRemovedDomino, i, j);
	//		if (!isVertical[i][j]) {
	//			occupiedCells[i][j] = 0;
	//			occupiedCells[i][j - 1] = 0;
	//			removeOneSentence(dominoPositions);
	//			printMatrix(occupiedCells, n);
	//		}
	//		else {
	//			occupiedCells[i][j] = 0;
	//			occupiedCells[i - 1][j] = 0;
	//			removeOneSentence(dominoPositions);
	//			printMatrix(occupiedCells, n);
	//		}
	//	}
	//	currentRemovedDomino = maxElementOfMatrix(occupiedCells, n);
	//	findDominoPlace(occupiedCells, n, currentRemovedDomino, i, j);
	//	occupiedCells[i][j] = 0;
	//	occupiedCells[i][j - 1] = 0;
	//	removeOneSentence(dominoPositions);
	//	printMatrix(occupiedCells, n);
	//	bool flag2 = isVertical[i + 1][j] * isVertical[i + 1][j - 1];
	//	while (flag2) {
	//		currentRemovedDomino = maxElementOfMatrix(occupiedCells, n);
	//		findDominoPlace(occupiedCells, n, currentRemovedDomino, i, j);
	//		occupiedCells[i][j] = 0;
	//		occupiedCells[i][j - 1] = 0;
	//		removeOneSentence(dominoPositions);
	//		printMatrix(occupiedCells, n);
	//		flag2 = isVertical[i + 1][j] * isVertical[i + 1][j - 1];
	//	}
	//	isVertical[i][j] = true;
	//	isVertical[i + 1][j] = true;
	//	isVertical[i][j - 1] = true;
	//	isVertical[i + 1][j - 1] = true;
	//}
	//while (!flag) {
	//	currentRemovedDomino = maxElementOfMatrix(occupiedCells, n);
	//	findDominoPlace(occupiedCells, n, currentRemovedDomino, i, j);
	//	if (!isVertical[i][j] && !isVertical[i][j - 1] && occupiedCells[i][j] && occupiedCells[i][j - 1]) {
	//		occupiedCells[i][j] = 0;
	//		occupiedCells[i][j - 1] = 0;
	//		removeOneSentence(dominoPositions);
	//		printMatrix(occupiedCells, n);
	//	}
	//	else if (isVertical[i][j] && isVertical[i - 1][j] && occupiedCells[i][j] && occupiedCells[i - 1][j]) {
	//		occupiedCells[i][j] = 0;
	//		occupiedCells[i - 1][j] = 0;
	//		removeOneSentence(dominoPositions);
	//		printMatrix(occupiedCells, n);
	//	}
	//	//if (i == 0 && j == 0 || (i != n - 1 && (j > n / 2 && !isVertical[i][j - 1] && !isVertical[i][j - 2] || j <= n / 2 && !isVertical[i - 1][j] && !isVertical[i - 1][j + 1]))) {
	//	//	isVertical[i][j] = true;
	//	//	isVertical[i + 1][j] = true;
	//	//	isVertical[i][j + 1] = true;
	//	//	isVertical[i + 1][j + 1] = true;
	//	//	/*if (!matrixComparison(isVertical, previousVertical, n)) 
	//	//		flag = true;*/
	//	//	flag = true;
	//	//	printMatrix(isVertical, n);
	//	//}
	//	if (j > 0) j--;
	//	else {
	//		i--;
	//		j = n - 1;
	//	}
	//}
}

bool boolMatrixCheck(bool** matrix, int n) {
	int flag = true;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n; j++)
			flag = flag * matrix[i][j];
	return flag;
}

int recursiveCheckMinDominoSet(int** matrix, int n, int minCountOfDominoSet, bool**& isVertical, int**& occupiedCells, string& dominoPositions) {
	if (n % 2 == 1)
		return 0;
	int** countOfUsingDomino = new int* [7];
	for (int i = 0; i < 7; i++) {
		countOfUsingDomino[i] = new int[7];
	}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			countOfUsingDomino[i][j] = 0;
	int previousDominoNumber = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++)
			if (occupiedCells[i][j] != 0 && occupiedCells[i][j] != previousDominoNumber && !isVertical[i][j]) {
				countOfUsingDomino[matrix[i][j]][matrix[i][j + 1]]++;
				previousDominoNumber = occupiedCells[i][j];
			}
	for (int i = 0; i < n - 1; i++) 
		for (int j = 0; j < n; j++)
			if (occupiedCells[i][j] != 0 && occupiedCells[i][j] != previousDominoNumber && isVertical[i][j]) {
				countOfUsingDomino[matrix[i][j]][matrix[i + 1][j]]++;
				previousDominoNumber = occupiedCells[i][j];
			}
	int dominoNumber = maxElementOfMatrix(occupiedCells, n) + 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (j < n - 1 && !isVertical[i][j] && occupiedCells[i][j] == 0 && occupiedCells[i][j + 1] == 0) {
				countOfUsingDomino[matrix[i][j]][matrix[i][j + 1]]++;
				occupiedCells[i][j] = dominoNumber;
				occupiedCells[i][j + 1] = dominoNumber;
				//dominoPositions += createString(matrix[i][j], matrix[i][j + 1], false);
				j++;
				dominoNumber++;
			}
			else  if (isVertical[i][j] && (occupiedCells[i][j] == 0 && occupiedCells[i + 1][j] == 0 || occupiedCells[i][j] == 0 && occupiedCells[i - 1][j] == 0)){
				countOfUsingDomino[matrix[i][j]][matrix[i + 1][j]]++;
				occupiedCells[i][j] = dominoNumber;
				occupiedCells[i + 1][j] = dominoNumber;
				//dominoPositions += createString(matrix[i][j], matrix[i + 1][j], true);
				dominoNumber++;
			}
		}
	cout << endl;
	cout << "Положение доминошек" << endl;
	printMatrix(isVertical, n);
	cout << "Занятые клетки" << endl;
	printMatrix(occupiedCells, n);
	cout << endl;
	int min = maxElementOfMatrix(countOfUsingDomino, 7);
	if (min == 1)
		return min;
	if (min < minCountOfDominoSet)
		minCountOfDominoSet = min;
	if (boolMatrixCheck(isVertical, n))
		return minCountOfDominoSet;
	removeDomino(isVertical, occupiedCells, n, dominoPositions);
	return recursiveCheckMinDominoSet(matrix, n, minCountOfDominoSet, isVertical, occupiedCells, dominoPositions);
}

int main() {
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите размер матрицы" << endl;
	cin >> n;
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}
	cout << "Введите элементы матрицы" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matrix[i][j];
	int minCountOfDominoSet = n * n / 2;
	int** occupiedCells = new int* [n];
	for (int i = 0; i < n; i++)
		occupiedCells[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			occupiedCells[i][j] = 0;
	bool** isVertical = new bool* [n];
	for (int i = 0; i < n; i++)
		isVertical[i] = new bool[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			isVertical[i][j] = false;
	string dominoPositions;
	cout << recursiveCheckMinDominoSet(matrix, n, minCountOfDominoSet, isVertical, occupiedCells, dominoPositions) << endl;
	//cout << dominoPositions;
	return 0;
}