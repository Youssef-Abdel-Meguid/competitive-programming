#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;


class SlimeXGrandSlimeAuto {
public:
	int travel(vector <int> cars, vector <int> districts, vector <string> roads, int inverseWalkSpeed, int inverseDriveSpeed);
};



const int maxn = 100500;

int head[maxn], prv[maxn], record[maxn], d[maxn];



struct Node{
	int u, v, flow, cost;
	int nxt;
} edge[maxn];
int e;

void addEdge(int u, int v, int flow, int cost){
	edge[e].u = u, edge[e].v = v, edge[e].flow = flow, edge[e].cost = cost;
	edge[e].nxt = head[u], head[u] = e++;
	edge[e].u = v, edge[e].v = u, edge[e].flow = 0, edge[e].cost = -cost;
	edge[e].nxt = head[v], head[v] = e++;
}

int maxFlow(int s, int t){
	int flow = 0;
	while (true){
		memset(d, 63, sizeof(d));
		queue<int> q;	q.push(s);
		d[s] = 0;
		while (!q.empty()){
			int u = q.front();	 q.pop();
			for (int i = head[u]; i != -1; i = edge[i].nxt) if (edge[i].flow > 0 && d[edge[i].v] > d[u] + edge[i].cost){
				prv[edge[i].v] = u, record[edge[i].v] = i;
				q.push(edge[i].v);
				d[edge[i].v] = d[u] + edge[i].cost;
			}
		}
		if (d[t] == 1061109567) break;
		for (int x = t; x != s; x = prv[x]){
			int ed = record[x];
			edge[ed].flow--;
			edge[ed ^ 1].flow++;
			flow += edge[ed].cost;
		}
	}
	return flow;
}

int di[105][105];



int SlimeXGrandSlimeAuto::travel(vector <int> cars, vector <int> districts, vector <string> roads, int inverseWalkSpeed, int inverseDriveSpeed) {
	memset(head, -1, sizeof(head));
	e = 0;
	int nCitites = roads.size(), nCars = cars.size(), nDistricts = districts.size();
	for (int i = 0; i < nCitites; i++) for (int j = 0; j < nCitites; j++) if (i != j){
		int co;
		if (roads[i][j] == '.')  co = 123456789;
		else if (roads[i][j] >= '0' && roads[i][j] <= '9') co = roads[i][j] - '0' + 1;
		else if (roads[i][j] >= 'a' && roads[i][j] <= 'z') co = roads[i][j] - 'a' + 11;
		else if (roads[i][j] >= 'A' && roads[i][j] <= 'Z') co = roads[i][j] - 'A' + 37;
		di[i][j] = co;
	}
	for (int k = 0; k < nCitites; k++) for (int i = 0; i < nCitites; i++)for (int j = 0; j < nCitites; j++)
		di[i][j] = min(di[i][j], di[i][k] + di[k][j]);
	int n = nDistricts + nCars + 2;
	int s = n - 2, t = n - 1;
	for (int i = 0; i < nDistricts; i++){
		int si = (i == 0) ? 0 : districts[i - 1];
		int ti = districts[i];
		addEdge(s, i, 1, 0);
		addEdge(i, t, 1, di[si][ti] * inverseWalkSpeed);
		for (int j = 0; j < nCars; j++) addEdge(i, j + nDistricts, 1, di[si][cars[j]] * inverseWalkSpeed + di[cars[j]][ti] * inverseDriveSpeed);
	}
	for (int i = 0; i < nCars; i++) addEdge(i + nDistricts, t, 1, 0);
	return maxFlow(s, t);
}




















// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, vector <string> p2, int p3, int p4, bool hasAnswer, int p5) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p2[i] << "\"";
	}
	cout << "}" << "," << p3 << "," << p4;
	cout << "]" << endl;
	SlimeXGrandSlimeAuto *obj;
	int answer;
	obj = new SlimeXGrandSlimeAuto();
	clock_t startTime = clock();
	answer = obj->travel(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p5 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p5;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	}
	else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	}
	else if (hasAnswer) {
		cout << "Match :-)" << endl;
	}
	else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;

	vector <int> p0;
	vector <int> p1;
	vector <string> p2;
	int p3;
	int p4;
	int p5;

	{
		// ----- test 0 -----
		int t0[] = { 1 };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		int t1[] = { 2, 3, 0 };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		string t2[] = { "..0.", "...1", "0..2", ".12." };
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 5;
		p4 = 1;
		p5 = 36;
		all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		int t0[] = { 1 };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		int t1[] = { 2, 0 };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		string t2[] = { ".A.", "A.B", ".B." };
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 2;
		p4 = 1;
		p5 = 262;
		all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		int t0[] = { 2, 2 };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		int t1[] = { 1, 2, 1 };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		string t2[] = { ".a4", "a..", "4.." };
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 3;
		p4 = 1;
		p5 = 95;
		all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		int t0[] = { 1 };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		int t1[] = { 2, 0 };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		string t2[] = { ".B.", "B.A", ".A." };
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 2;
		p4 = 1;
		p5 = 262;
		all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		int t0[] = { 2, 5, 1, 2 };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		int t1[] = { 1, 5, 1, 2, 4 };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		string t2[] = { ".12.4.", "1....7", "2..3..", "..3..5", "4.....", ".7.5.." };
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 53;
		p4 = 37;
		p5 = 1259;
		all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 5 -----
		int t0[] = { 0, 1, 1, 0, 1 };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		int t1[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		string t2[] = { ".D", "D." };
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 81;
		p4 = 51;
		p5 = 156000;
		all_right = KawigiEdit_RunTest(5, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	}
	else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING


//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!