#include <iostream>
#include <stdlib.h>

using namespace std;

#define N 8

class Map
{
public:
	Map();
	virtual ~Map() {};
	int m[N][N];

	void refresh();
	void printMaps();
	
	int m_h[N][N];
	int h_max_col;
	int h_max_row;
	int h_max;

	int m_v[N][N];
	int v_max_col;
	int v_max_row;
	int v_max;
};

Map::Map() 
{
	memset(m, 0, sizeof(int)*N*N);
	refresh();
}

void Map::refresh()
{
	for (int row = 0; row < N; row++) {
		for (int col = 0;  col < N; col++) {
			if (m[row][col] == 0) {
				if ((row == 0) && (col == 0)) {
					m_h[row][col] = 1;
					m_v[row][col] = 1;
				} else if (row == 0) {
					m_h[row][col] = m_h[row][col - 1] + 1;
					m_v[row][col] = 1;
				} else if (col == 0) {
					m_v[row][col] = m_v[row - 1][col] + 1;
					m_h[row][col] = 1;
				} else {
					m_h[row][col] = m_h[row][col - 1] + 1;
					m_v[row][col] = m_v[row - 1][col] + 1;
				}
			} else {
				m_h[row][col] = 0;
				m_v[row][col] = 0;
			}	
		}
	}		
}

void Map::printMaps()
{
	cout << "Game: " << endl;
	for (int row = 0; row < N; row++) {
		for (int col = 0;  col < N; col++) {
			cout << m[row][col] << " ";
		}
		cout << endl;
	}
	cout << "Herizontal : " << endl;
	for (int row = 0; row < N; row++) {
		for (int col = 0;  col < N; col++) {
			cout << m_h[row][col] << " ";
		}
		cout << endl;
	}
	cout << "Vertical: " << endl;
	for (int row = 0; row < N; row++) {
		for (int col = 0;  col < N; col++) {
			cout << m_v[row][col] << " ";
		}
		cout << endl;
	}
}

int main()
{
	Map myMap;
	myMap.printMaps();
	myMap.m[2][3] = -1;
	myMap.refresh();
	myMap.printMaps();
}
