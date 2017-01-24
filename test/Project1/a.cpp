#include<iostream>
#include<string>
using namespace std;

void main(){
	string s1 = "ABCDEFG", s2 = "9898", s3 = "###", s4 = "012345";
	cout<<s1.substr(s2.length(), s3.length())<<endl;
	cout<<s4.substr(s2.find_first_of('8'), s2.length())<<endl;
	cout<<s2.find_first_of('9')<<endl;
	int x;
	cin>>x;
	return;
}