#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include<cstring>
#include <bits/stdc++.h> 
using namespace std;
bool NP(string word,stack <string> &s1);
bool VP(string word,stack <string> &s1);
bool ProN(string word,stack <string> &s1);
bool Det(string word,stack <string> &s1);
bool Nom(string word,stack <string> &s1);
bool Verb(string word,stack <string> &s1);
bool Noun(string word,stack <string> &s1);
bool ProNoun(string word,stack <string> &s1);
string* Break(string word);
int NumOfWords(string sen);
bool S(string word,stack <string> &s1){
	if(NP(word,s1) || VP(word,s1)){
		s1.push("NP ");
		return true;
	}
	return true;
}
bool NP(string word,stack <string> &s1){
	if(ProNoun(word,s1)==true){
		s1.push("Pro ");
		return true;
	}
	//Det(word);
	if(Nom(word,s1)==true){
		s1.push("Nom ");
		return true;
	}
}
bool VP(string word,stack <string> &s1){
	//Verb(word);
	NP(word,s1);
}
bool Nom(string word,stack <string> &s1){
	if(Noun(word,s1)==true){
		s1.push("Noun ");
		return true;	
	}
	//Nom(word);
}
//reading corpus
bool Noun(string word,stack <string> &s1){
	string* var;
	string noun[6801];
	int i=0;
	ifstream myfile ("nouns.txt");
	if (myfile.is_open())
	{
	while ( getline (myfile,noun[i]) )
	{
	  i++;
	}
	myfile.close();
	}
	else cout << "Unable to open file"; 
	if (binary_search(noun, noun + 6801,word)){
		//cout<<word<<endl;
		s1.push(word);
		return true;
	}
	else return false;			
}
bool ProNoun(string word,stack <string> &s1){
	string* var;
	string pronoun[77];
	int i=0;
	ifstream myfile ("pronouns.txt");
	if (myfile.is_open())
	{
	while ( getline (myfile,pronoun[i]) )
	{
	  i++;
	}
	myfile.close();
	}
	else cout << "Unable to open file"; 
	if (binary_search(pronoun, pronoun + 77,word)){
			s1.push(word);
			return true;
		}
		else return false;	
}
string* Break(string sen){
	string* var=new string[10];
	int x=0;
	for(int i=0;i<=strlen(sen.c_str());i++){
		if(sen[i]==' ' || i==strlen(sen.c_str())){
			x++;
		}
		else{
			var[x]+=sen[i];
		}
	}
	return var;
}
int NumOfWords(string sen){
	int num=1;
	for(int i=0;i<=strlen(sen.c_str());i++){
		if(sen[i]==' '){
			num++;
		}
	}
	return num;
}
int main () {
	string sen;
	string* var;
	bool check=true;
	int i=0;
	cout<<"Enter the sentence to parse\n";
	getline(cin,sen);
	var=Break(sen);
	stack <string> s[NumOfWords(sen)];
	//cout<<NumOfWords(sen);
	//cout<<var[2];
	cout<<"S"<<endl;
	for(int i=0;i<NumOfWords(sen);i++){
		check=S(var[i],s[i]);
	}
	int x=NumOfWords(sen);
	while(!s[i].empty()){
		if(i==x){
			i=0;
			cout<<endl;
		}
		cout<<s[i].top();
		s[i].pop();	
		i++;
	}
	
	if(check==false){
		cout<<"Incorrect Structure\n";
	}
  return 0;
}
 


