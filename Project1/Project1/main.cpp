//#include<iostream>
//#include<string>
//#include<vector>
//#include<cstring>
//#include<algorithm>
//#include<unordered_map>
//using namespace std;
//
//struct Team {
//	char c;
//	int score;
//};
//
//bool cmp(Team t1, Team t2)
//{
//	if (t1.score > t2.score) {
//		return true;
//	}
//	else if(t1.c < t2.c){
//		return true;
//	}
//}
//
//int main()
//{
//	string str;
//	Team t;
//	Team t1;
//	vector<Team> vec;
//	while (getline(cin, str)) {
//		t.c = str[0];
//		t1.c = str[2];
//		const char c1 = str[4];
//		const char c2 = str[6];
//		int v1 = c1 - '0';
//		int v2 = c2 - '0';
//		if (v1 > v2) {
//			t.score = 3;
//			t1.score = 0;
//		}
//		else if (v1 == v2) {
//			t.score = 1;
//			t1.score = 1;
//		}
//		else if (v1 < v2) {
//			t.score = 0;
//			t1.score = 3;
//		}
//		bool flag = false;
//		bool flag1 = false;
//		for (auto & elem : vec) {
//			if (t.c == elem.c) {
//				elem.score += t.score;
//				flag = true;
//			}
//			if (t1.c == elem.c) {
//				elem.score += t1.score;
//				flag1 = true;
//			}
//		}
//		if (!flag) {
//			vec.push_back(t);
//		}
//		if (!flag1) {
//			vec.push_back(t1);
//		}
//	}
//	sort(vec.begin(), vec.end(), cmp);
//	bool flag2 = false;
//	for (auto & elem : vec) {
//		if (!flag2) {
//			cout << elem.c << " " << elem.score;
//			flag2 = true;
//		}
//		if (flag2) {
//			cout << ","  << elem.c << " " << elem.score;
//		}
//	}
//	cout << endl;
//	return 0;
//}
//#include<iostream>
//using namespace std;
//
//int timeNeed(int M, int N, int X, int Y, int target)
//{
//	int pureprofit;
//	int result = 0;
//	int periodprofit;
//	int periodsprofit;
//	int periodnum;
//	pureprofit = M * X;
//	if (pureprofit >= target) {
//		return int((target + X - 1) / X);
//	}
//	periodprofit = M * X - N * Y;
//	if (periodprofit <= 0) {
//		return -1;
//	}
//	periodsprofit = target - pureprofit;
//	periodnum = (periodsprofit + periodprofit - 1) / periodprofit;
//	result += periodnum * (M + N);
//	target -= periodnum * periodprofit;
//	while (target > 0) {
//		result++;
//		target -= X;
//	}
//	return result;
//}
//int main()
//{
//	int T, M, N, X, Y,P;
//	while (T--) {
//		cin >> M >> N >> X >> Y >> P;
//		cout << timeNeed(M, N, X, Y, P - 100000) << endl;
//	}
//	return 0;
//}
#include<iostream>
#include<vector>
using namespace std;
#define N 10010
int arr[N];
void quicksort(int nums[], int low, int high)
{
	int i = low;
	int j = high;
	if (low < high) {
		int temp = nums[i];
		while (i < j) {
			while (j > i&&nums[j] >= temp) {
				--j;
			}
			if (i < j) {
				nums[i] = nums[j];
				++i;
			}
			while (j > i&&nums[i] < temp) {
				++i;
			}
			if (i < j) {
				nums[j] = nums[i];
				--j;
			}
		}
		nums[i] = temp;
		quicksort(nums, low, i - 1);
		quicksort(nums, i + 1, high);
	}
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	int low = 0;
	int high = n - 1;
	quicksort(arr, low, high);
	int index = 1;
	while (index < high && (index + 1) <= high) {
		int temp = arr[index];
		arr[index] = arr[index + 1];
		arr[index + 1] = temp;
		index = index + 2;
	}
	for (int i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}