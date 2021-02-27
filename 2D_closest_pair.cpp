#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <limits>  
#include <math.h>
#pragma warning(disable:4996) 
using namespace std;

typedef class Point {
public:
	int x;
	int y;
};

void qswap(vector<Point>& point, int x, int y) {
	Point temp = point[x];
	point[x] = point[y];
	point[y] = temp;
}

void quicksort(vector<Point>& point, int l, int r) {
	int i = l, j = r, mid;
	int pivot;
	mid = l + (r - l) / 2;
	pivot = point[mid].y;

	while (i<r || j>l) {
		while (point[i].y < pivot)
			i++;
		while (point[j].y > pivot)
			j--;

		if (i <= j) {
			qswap(point, i, j);
			i++;
			j--;
		}
		else {
			if (i < r)
				quicksort(point, i, r);
			if (j > l)
				quicksort(point, l, j);
			return;
		}
	}
}

long long distance(Point a, Point b) {
	long long ax = a.x;
	long long ay = a.y;
	long long bx = b.x;
	long long by = b.y;
	return (pow(ax - bx, 2) + pow(ay - by, 2));
}

long long brute_force(vector<Point> point, int front, int end, int size) {
	long long min_dis = numeric_limits<long long>().max();
	for (int i = 0; i < (end - front); i++) {
		for (int j = i + 1; j <= (end - front); j++) {
			if (distance(point[i], point[j]) < min_dis) {
				min_dis = distance(point[i], point[j]);
			}
		}
	}
	return min_dis;
}

bool compare_x(Point& a, Point& b) {
	return a.x < b.x;
}

bool compare_y(Point a, Point b) {
	return a.y < b.y;
}

float find_median(vector<Point> point, int front, int end) {
	if ((end - front + 1) % 2 == 0) {
		nth_element(point.begin(), point.begin() + front + (end - front) / 2, point.end(), compare_x);
		nth_element(point.begin(), point.begin() + front + (end - front + 1) / 2, point.end(), compare_x);

		return(float((float(point[(end - front) / 2].x) + float(point[(end - front + 1) / 2].x)) / 2));
	}
	else {
		nth_element(point.begin(), point.begin() + front + (end - front) / 2, point.end(), compare_x);
		return(point[(end - front) / 2].x);
	}
}

long long TwoDCP(vector<Point> point, int front, int end) {
	// �p�G�I�ƳѤU�֩󵥩�3�I�]2��3���I�^�A�����μɤO�D��
	if ((end - front) <= 36) {
		return brute_force(point, front, end, end - front);
	}
	// �o�줤���
	float median = find_median(point, 0, point.size() - 1);
	// ��@�U�`�@���X�ӬۦP�Ȫ�����ơA�H�K����������
	int count = 0;
	for (int i = 0; i <= end - front; i++) {
		if (point[i].x == median) {
			count++;
		}
	}
	//	cout << count<<"\n";
		// �J��h��median�ɡA�n��h��left_count�bleft�����Aright_count�bright����
	int left_count, right_count;
	if (count % 2 == 0) {
		left_count = count / 2;
		right_count = count / 2;
	}
	else {
		left_count = (count + 1) / 2;
		right_count = count / 2;
	}
	vector<Point> left;
	vector<Point> right;
	// �Τ���ƨӧ�point�������k��ӳ����A�䤤point.x == median���ɭԷ|�ݥ��k����֥[�J����A
	for (int i = 0; i < point.size(); i++) {
		if (float(point[i].x) < median) {
			left.push_back(point[i]);
		}
		else if (float(point[i].x) > median) {
			right.push_back(point[i]);
		}
		else {
			if (left_count > 0) {
				left.push_back(point[i]);
				left_count--;
			}
			else {
				right.push_back(point[i]);
			}
		}
	}
	// ��������A���k�ⳡ����point���٬O�|�O��y�Ѥp��j
	//	Divide�����k������p�D
	long long left_min_dis = TwoDCP(left, 0, left.size() - 1);
	//	vector<Point>().swap(left);
	long long right_min_dis = TwoDCP(right, 0, right.size() - 1);
	//	vector<Point>().swap(right);
		// ��X�ⳡ����X���̤p�Z��
	long long min_dis = min(left_min_dis, right_min_dis);
	// ���ۦҼ{�ⳡ������ɳB�A��median�Z��min_dis���I���n�Q�Ҽ{�i�h
	vector<Point> intersection;
	for (int i = 0; i < point.size(); i++) {
		if (abs(float(point[i].x) - median) <= float(sqrt(min_dis))) {
			intersection.push_back(point[i]);
		}
	}

	for (int i = 0; i < intersection.size(); i++) {
		int check = 0;
		// �o�Ӱj��u�|�]�̦h6���]BY�X���ҩ��^
		for (int j = i + 1; j < intersection.size(); j++) {
			if (distance(intersection[i], intersection[j]) < min_dis) {
				min_dis = distance(intersection[i], intersection[j]);
			}
			check++;
			if (check == 8) {
				continue;
			}
		}
	}
	return min_dis;
}



int main() {
	vector<Point> point;
	int input_number;
	scanf("%d", &input_number);

	for (int i = 0; i < input_number; i++) {
		Point temp;
		scanf("%d %d", &temp.x, &temp.y);
		point.push_back(temp);
	}

	quicksort(point, 0, point.size() - 1);

	cout << TwoDCP(point, 0, point.size() - 1);

}
