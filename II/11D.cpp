#include <cstdio>
#include <iostream>
#include <set>
#include <math.h>
#include <string.h>
using namespace std;
int const size = 8;
char const empty = '0';
char const wall = '1';
char const player = '2';
char const terminator = '3';
set<pair<pair<int, int>, pair<int, int> > > winPositions;
char pos[size][size];
pair<int, int> playerPos;
pair<int, int> terminatorPos;
set<pair<int, int> > wallsPos;
bool hasWallV(int i, int pos1, int pos2)
{
	int temp = 0;
	if (pos1 > pos2) {
		temp = pos1;
		pos1 = pos2;
		pos2 = temp;
	}
	for (int j = pos1; j < pos2; ++j)
		if (pos[i][j] == wall)
			return true;
	return false;
}
bool hasWallH(int j, int pos1, int pos2)
{
	int temp = 0;
	if (pos1 > pos2) {
		temp = pos1;
		pos1 = pos2;
		pos2 = temp;
	}
	for (int i = pos1; i < pos2; ++i)
		if (pos[i][j] == wall)
			return true;
	return false;
}
bool hasWallDiag(int pos1, int pos2, int pos3, int pos4, bool isMainDiag)
{
	int temp = 0;
	if (pos1 > pos3) {
		temp = pos1;
		pos1 = pos3;
		pos3 = temp;
		temp = pos2;
		pos2 = pos4;
		pos4 = temp;
	}
	if (isMainDiag) {
		int diagI = pos1;
		int diagJ = pos2;
		while (diagI != pos3 && diagJ != pos4) {
			if (pos[diagI][diagJ] == wall)
				return true;
			diagI++;
			diagJ++;
		}
		return false;
	} else {
		int diagI = pos1;
		int diagJ = pos2;
		while (diagI != pos3 && diagJ != pos4) {
			if (pos[diagI][diagJ] == wall)
				return true;
			 diagI++;
			diagJ--;
		}
		return false;
	}
}
bool isDangerous(pair<int, int> pPos, pair<int, int> tPos)
{
	if (tPos.first >= size || tPos.first < 0 || tPos.second >= size || tPos.first < 0)
		return false;
	if (pos[tPos.first][tPos.second] == wall)
		return false;
	if (pPos.first == tPos.first) {
		int line = pPos.first;
		if (!hasWallV(line, pPos.second, tPos.second))
			return true;
	}
	if (pPos.second == tPos.second) {
		int line = pPos.second;
		if (!hasWallH(line, pPos.first, tPos.first))
			return true;
	}
	if ((pPos.first - tPos.first) == (pPos.second - tPos.second)) {
		if (!hasWallDiag(pPos.first, pPos.second, tPos.first, tPos.second, true))
			return true;
	}
	if ((pPos.first - tPos.first) == (- pPos.second + tPos.second)) {
		if (!hasWallDiag(pPos.first, pPos.second, tPos.first, tPos.second, false))
			return true;
	}
	return false;
}
bool terminatorHasWinPos(int i, int j, int k, int m)
{
	pair<int, int> pPos = make_pair(i, j);
	return (isDangerous(pPos, make_pair(k, m))
			|| isDangerous(pPos, make_pair(k - 1, m))
			|| isDangerous(pPos, make_pair(k + 1, m))
			|| isDangerous(pPos, make_pair(k, m + 1))
			|| isDangerous(pPos, make_pair(k, m - 1))
			|| isDangerous(pPos, make_pair(k + 1, m + 1))
			|| isDangerous(pPos, make_pair(k - 1, m + 1))
			|| isDangerous(pPos, make_pair(k + 1, m - 1))
			|| isDangerous(pPos, make_pair(k - 1, m - 1)));
}
bool containsPos(int i, int j, int k, int m)
{
	pair<pair<int, int>, pair<int, int> > res = make_pair(make_pair(i, j), make_pair(k, m));
	return (winPositions.find(res) != winPositions.end());
}
bool playerHasWinNextPos(int i, int j, int k, int m)
{
	bool result = true;
	if (m > 0)
		if (pos[k][m-1] != wall)
			result &= containsPos(i, j, k, m - 1);
	if (m < size - 1)
		if (pos[k][m+1] != wall)
			result &= containsPos(i, j, k, m + 1);
	if (k > 0) {
		if (pos[k-1][m] != wall)
			result &= containsPos(i, j, k - 1, m);
		if (m < size - 1)
			if (pos[k-1][m+1] != wall)
				result &= containsPos(i, j, k - 1, m + 1);
		if (m > 0)
			if (pos[k-1][m-1] != wall)
				result &= containsPos(i, j, k - 1, m - 1);
	}
	if (k < size - 1) {
		if (pos[k+1][m] != wall)
			result &= containsPos(i, j, k + 1, m);
		if (m < size - 1)
			if (pos[k+1][m+1] != wall)
				result &= containsPos(i, j, k + 1, m + 1);
		if (m > 0)
			if (pos[k+1][m-1] != wall)
				result &= containsPos(i, j, k + 1, m - 1);
	}
	return result;
}
int main()
{
	freopen("terminator.in", "rt", stdin);
	freopen("terminator.out", "wt", stdout);
	char temp[size];
	for (int i = 0; i < size; ++i) {
		scanf("%s", temp);
		for (int j = 0; j < size; ++j) {
			char c = temp[j];
			if (c ==  player)
				playerPos = make_pair(i, j);
			else if (c == terminator)
				terminatorPos = make_pair(i, j);
			pos[i][j] = c;
		}
	}
	for (int j = 0; j < size; ++j) {
		// беглец в клетке [7, j], перебираем всех терминаторов
		for (int k = size - 1; k >= 0; --k)
			for (int m = 0; m < size; ++m) {
				// терминатор в клетке [k, m]
				if (pos[size - 1][j] == wall)
					continue;
				if (pos[k][m] == wall)
					continue;
				if (!isDangerous(make_pair(size - 1, j), make_pair(k, m))) {
					winPositions.insert(make_pair(make_pair(size - 1, j), make_pair(k, m)));
				}
			}
	}
	bool update = true;
	while (update) {
		update = false;
		for (int i = size - 2; i >= 0; --i) {
			for (int j = 0; j < size; ++j) {
				if (pos[i][j] == wall)
					continue;
				// беглец в клетке [i, j], перебираем всех терминаторов
				for (int k = size - 1; k >= 0; --k)
					for (int m = 0; m < size; ++m) {
						// терминатор в клетке [k, m]
						if (pos[k][m] == wall)
							continue;
						if (isDangerous(make_pair(i, j), make_pair(k, m)))
							continue;
						for (int pPosI = i + 1; pPosI >= i - 1; --pPosI) {
							if ((pPosI < 0) || (pPosI > size - 1))
								continue;
							for (int pPosJ = j - 1; pPosJ <= j + 1; ++pPosJ) {
								if ((pPosJ < 0) || pPosJ > (size - 1))
									continue;
								if (pos[pPosI][pPosJ] == wall)
									continue;
								if (!containsPos(i, j, k, m)
									&& !terminatorHasWinPos(pPosI, pPosJ, k, m)
									&& playerHasWinNextPos(pPosI, pPosJ, k, m))
								{
									winPositions.insert(make_pair(make_pair(i, j), make_pair(k, m)));
									update = true;
									//cout << i << " " << j << " " << k << " " << m << "\n";
								}
							}
						}
					}
			}
		}
	}
	if (containsPos(playerPos.first, playerPos.second, terminatorPos.first, terminatorPos.second))
		cout << "1";
	else
		cout << "-1";
	return 0;
}


