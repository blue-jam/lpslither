#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv){
	char buf[256];

	if(argc < 3){
		fprintf(stderr, "usage: %s [dat] [list]\n", argv[0]);
	}

	FILE *fp1 = fopen(argv[1], "r");
	int h, w;
	vector<string> f;
	fscanf(fp1, "%d%d", &h, &w);
	for(int i = 0; i < h; ++i){
		fscanf(fp1, "%s", buf);
		f.push_back(string(buf));
	}
	fclose(fp1);

	FILE *fp2 = fopen(argv[2], "r");
	vector<tuple<char,int,int>> v;
	while(fgets(buf, sizeof(buf), fp2) != NULL){
		int i, j, s;
		if(buf[0] == '#') continue;
		sscanf(buf, "%*[^_]_%d_%d%d", &i, &j, &s);
		if(s == 0) continue;
		v.push_back(make_tuple(buf[0], i, j));
	}
	fclose(fp2);

	vector<string> out(h * 2 + 1, string(w * 2 + 1, ' '));
	for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j){
		out[i * 2 + 1][j * 2 + 1] = f[i][j];
	}

	for(auto t : v){
		char c = get<0>(t);
		int i = get<1>(t);
		int j = get<2>(t);
		if(c == 'N'){
		}
		else if(c == 'U' || c == 'D'){
			out[i*2][j*2] = '+';
			out[i*2+1][j*2] = '|';
			out[i*2+2][j*2] = '+';
		}
		else if(c == 'L' || c == 'R'){
			out[i*2][j*2] = '+';
			out[i*2][j*2+1] = '-';
			out[i*2][j*2+2] = '+';
		}
		else{
			cerr << "invalid :-(" << endl;
		}
	}

	for(string l : out){
		cout << l << endl;
	}
	return 0;
}
