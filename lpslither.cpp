#include <bits/stdc++.h>
using namespace std;

int main(){
	int h, w;
	cin >> h >> w;

	vector<string> f(h);
	for(int i = 0; i < h; ++i)
		cin >> f[i];

	cout << "Minimize" << endl << "Subject To" << endl;

	for(int i = 0; i <= h; ++i) for(int j = 0; j <= w; ++j) {
		// 入次数が1か0
		if(i > 0) cout << " + D_" << i-1 << "_" << j;
		if(j > 0) cout << " + R_" << i << "_" << j-1;
		if(i < h) cout << " + U_" << i << "_" << j;
		if(j < w) cout << " + L_" << i << "_" << j;
		cout << " <= 1" << endl;
		// 出次数が1か0
		if(i > 0) cout << " + U_" << i-1 << "_" << j;
		if(j > 0) cout << " + L_" << i << "_" << j-1;
		if(i < h) cout << " + D_" << i << "_" << j;
		if(j < w) cout << " + R_" << i << "_" << j;
		cout << " <= 1" << endl;

		// 入次数とで次数の差が0
		if(i > 0) cout << " + D_" << i-1 << "_" << j;
		if(j > 0) cout << " + R_" << i << "_" << j-1;
		if(i < h) cout << " + U_" << i << "_" << j;
		if(j < w) cout << " + L_" << i << "_" << j;
		if(i > 0) cout << " - U_" << i-1 << "_" << j;
		if(j > 0) cout << " - L_" << i << "_" << j-1;
		if(i < h) cout << " - D_" << i << "_" << j;
		if(j < w) cout << " - R_" << i << "_" << j;
		cout << " = 0" << endl;
	}

	// 辺は一方通行（同じ辺は高々1回しか使えない）
	for(int i = 0; i <= h; ++i){
	   	for(int j = 0; j < w; ++j){
			cout << " L_" << i << "_" << j << " + ";
			cout << " R_" << i << "_" << j << " <= 1" << endl;
		}
	}
	for(int i = 0; i < h; ++i){
	   	for(int j = 0; j <= w; ++j){
			cout << " U_" << i << "_" << j << " + ";
			cout << " D_" << i << "_" << j << " <= 1" << endl;
		}
	}

	// 数が書いてある周りはその数と同じ数だけ配置
	for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j){
		if(f[i][j] == '.') continue;
		int n = f[i][j] - '0';
		cout << " + L_" << i << "_" << j;
		cout << " + R_" << i << "_" << j;
		cout << " + U_" << i << "_" << j;
		cout << " + D_" << i << "_" << j;
		cout << " + L_" << i+1 << "_" << j;
		cout << " + R_" << i+1 << "_" << j;
		cout << " + U_" << i << "_" << j+1;
		cout << " + D_" << i << "_" << j+1;
		cout << " = " << n << endl;
	}

	// MTZ formulation
	int si, sj;
	si = sj = -1;
	for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j) {
		if(f[i][j] == '3') {
			si = i;
			sj = j;
		}
	}
	if(si < 0) {
		cerr << "Because there is no '3' in the field," << endl
			<< "I can't guess a fixed point for MTZ formulation. (>_<)" << endl;
		exit(1);
	}

	int num = (h + 1) * (w + 1);
	// 制約1
	cout << " N_" << si << "_" << sj << " = 1" << endl;
	// 制約2
	for(int i = 0; i <= h; ++i) for(int j = 0; j <= w; ++j) {
		if(i == si && j == sj) continue;
		cout << " N_" << i << "_" << j << " <= " << num << endl;
		cout << " N_" << i << "_" << j << " >= " << 2 << endl;
	}

	stringstream sstream;
	sstream << "N_" << si << "_" << sj;
	string start = sstream.str();
	// 制約3
	for(int i = 0; i <= h; ++i){
	   	for(int j = 0; j < w; ++j){
			stringstream ss;
			ss << "N_" << i << "_" << j;
			string src = ss.str();
			ss.str("");
			ss << "N_" << i << "_" << (j+1);
			string dst = ss.str();

			if(dst != start){
				cout << " " << src << " - " << dst << " + "
				   << (num - 1) << " R_" << i << "_" << j << " <= " << num - 2 << endl;
			}
			swap(src, dst);
			if(dst != start){
				cout << " " << src << " - " << dst << " + "
				   << (num - 1) << " L_" << i << "_" << j << " <= " << num - 2 << endl;
			}
		}
	}
	for(int i = 0; i < h; ++i){
	   	for(int j = 0; j <= w; ++j){
			stringstream ss;
			ss << "N_" << i << "_" << j;
			string src = ss.str();
			ss.str("");
			ss << "N_" << (i+1) << "_" << j;
			string dst = ss.str();

			if(dst != start){
				cout << " " << src << " - " << dst << " + "
				   << (num - 1) << " D_" << i << "_" << j << " <= " << num - 2 << endl;
			}
			swap(src, dst);
			if(dst != start){
				cout << " " << src << " - " << dst << " + "
				   << (num - 1) << " U_" << i << "_" << j << " <= " << num - 2 << endl;
			}
		}
	}

	cout << "Bounds" << endl;
	cout << "Integers" << endl;
	for(int i = 0; i <= h; ++i){
	   	for(int j = 0; j <= w; ++j){
			cout << " N_" << i << "_" << j;
		}
		cout << endl;
	}
	cout << "Binary" << endl;
	for(int i = 0; i <= h; ++i){
	   	for(int j = 0; j < w; ++j){
			cout << " L_" << i << "_" << j;
			cout << " R_" << i << "_" << j;
		}
		cout << endl;
	}
	for(int i = 0; i < h; ++i){
	   	for(int j = 0; j <= w; ++j){
			cout << " U_" << i << "_" << j;
			cout << " D_" << i << "_" << j;
		}
		cout << endl;
	}
	cout << "End" << endl;
	return 0;
}
