#include<bits/stdc++.h>
using namespace std;

#define ll long long int

int LISBF(int * ar, int n) {
	if(n <= 0)
	       return 0;
	int res=1;
	for(int i=0; i<(1<<n); i++) {
		int curr=1;
		int prev=-1;
		bool firstTime=true;
		string bits=bitset<10>(i).to_string();
		for(int j=0; j<bits.size() and j<n; j++) {
			if(bits[j] == '1')
			{
				if(firstTime) {
					prev=ar[j];
					firstTime=false;
				}
				else {
					if(prev < ar[j]) {
						curr++;
						prev=ar[j];
					}else {
						break;
					}
				}
			}
		}
		res = max(res, curr);
	}
	return res;
}

int LISDP(int * ar, int n) {
	if(n<=0)
		return 0;
	int res=1;
	int * LISupto = new int[n];
	for(int i=0; i<n; i++)
		LISupto[i] = 1;
	for(int i=1; i<n; i++) {
		int bestPrefixLength=0;
		for(int j=0; j<i; j++) {
			if(ar[j] < ar[i]) {
				bestPrefixLength = max(bestPrefixLength, LISupto[j]);
			}
		}
		LISupto[i] = max(LISupto[i], bestPrefixLength + 1);
		res = max(res, LISupto[i]);
	}
	return res;
}

int LISUBLB(int * ar, int n) {
	if(n <= 0 )
		return 0;
	int res=1;
	vector<int> sortedList;
	for(int i=0; i<n; i++) {
		if(sortedList.empty()){
			sortedList.push_back(ar[i]);
			continue;
		}
		if(ar[i] > sortedList.back()) {
			sortedList.push_back(ar[i]);
			res++;
		}
		else if(sortedList[lower_bound(sortedList.begin(), sortedList.end(), ar[i]) - sortedList.begin()] == ar[i]){
			continue;
		}
		else {
			sortedList[lower_bound(sortedList.begin(), sortedList.end(), ar[i]) - sortedList.begin()] = ar[i];
		}
	}
	return res;
}

int main(){
	cout << "Enter length: ";
	int n;
	cin >> n;
	cout << "Enter elements: ";
	int * ar=new int[n];
	for(int i=0; i<n; i++)
		cin >> ar[i];
	cout << "\nLIS using Brute force: " << LISBF(ar, n);
	cout << "\nLIS using DP: " << LISDP(ar, n);
	cout << "\nLIS using UBLB: " << LISUBLB(ar, n);
	cout << '\n';
	return 0;
}