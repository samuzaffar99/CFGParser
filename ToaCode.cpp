#include <algorithm> //vv  nice Abdullah 
#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include <iterator> 
#include<cstring>
#include <bits/stdc++.h>
using namespace std;
int gnWords=0;
bool S(string s);
bool NP(string s);
bool VP(string s);
bool Pronoun(string s);
bool Det(string s);
bool Nominal(string s);
bool Verb(string s);
bool Noun(string s);
bool PP(string s);
bool Preposition(string s);
void Replace(string s1);
void Showlist(list <string> g);
//list
list <string> plist;
list<string>::iterator itr;
//end list
void Showlist(list <string> g)
{ 
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << *it<< " "; 
    cout <<endl; 
}
void Replace(string s){
	itr=plist.erase(itr);
	//itr++;
	//cout<<"New iterrotr"<<*itr<<endl;
	plist.begin()=itr;
	plist.insert(itr,s);
	itr--;
}
int NumOfWords(string s){ //returns Number of Words in String
	int num=1; //need to set this to 0 for empty case
	for(int i=0;i<=strlen(s.c_str());i++){
		if(s[i]==' '){
			num++;
		}
	}
	return num;
}
string WordCut(string s){ //removes first word from string
    string s2=s.substr(s.find(" ")+1);
    //cout<<s2<<endl; //debug
	return s2;
}

string GetFirst(string s){
    string s2;
    for(int i=0;i<s.length();i++){ //vv nice ahmed
        if(s[i]==' '){
            break;
        }
        s2+=s[i]; //vv nice ahmed
    }
    return s2;
}
bool Finder(string s,string FN,string str){
    ifstream F(FN);
    string s2;
    s=GetFirst(s);
    //cout<<"String to Find: "<<s<<endl; //debug
    while(!F.eof()){
        getline(F,s2);
        if(s2==s){
        	Replace(str);
			Showlist(plist);	
            Replace(s2); //debug
            Showlist(plist);
            return true;
        }
    }
    return false;
}
bool S(string s){
	plist.push_back("NP");
	plist.push_back("VP");
	itr=plist.begin();
	Showlist(plist);
    if(NP(s)){
    	itr++;
        if(VP(WordCut(s))){
             //debug
            return true;
        }
        return true;
    }
   // cout<<"Failed S"<<endl; //debug
    return false;
}

bool NP(string s){
    if(Pronoun(s)){
    	
         //debug
        return true;
    }
//    cout<<"Returned false\n";
//    cout<<*itr<<endl;
//    if(ProperNoun(s)){
//        return true;
//    }
    if(Det(s)){
    	//cout<<"here\n"; //debug
    	plist.push_back("Nominal");
    		Showlist(plist);

		itr++;
        if(Nominal(WordCut(s))){
            //cout<<"Det Nominal"<<endl; //debug
            return true;
        }
    }
    //cout<<"Failed NP"<<endl; //debug
    return false;
}

bool Nominal(string s){
    if(Noun(s)){
        if(NumOfWords(s)>1){
            if(Nominal(WordCut(s))){
               // cout<<"Noun Nominal"<<endl; //debug
                return true;
            }
        }
        //cout<<"Noun"<<endl; //debug
        return true;
    }
    //cout<<"Failed Nominal"<<endl; //debug
    return false;
}

bool VP(string s){
//	itr++;
//	Replace("Verb");
//	Showlist(plist);
    if(Verb(s)){
    		plist.push_back("NP");
    			Showlist(plist);

			itr++;
        if(NP(WordCut(s))){
        	
//            if(PP(WordCut(WordCut(s)))){
//                //cout<<"Verb NP PP"<<endl; //debug
//                return true;
//            }
            //cout<<"Verb NP"<<endl; //debug
            return true;
//        }
        //cout<<"Verb"<<endl;
        return true;
//        if(PP(WordCut(s))){
//            //cout<<"Verb NP"<<endl; //debug
            return true;
        }
        
    }
    //cout<<"Failed VP"<<endl; //debug
    return false;
}

bool PP(string s){
    if(Preposition(s)){
        if(NP(WordCut(s))){
            //cout<<"Preposition NP"<<endl; //debug
            return true;
        }
    }
    //cout<<"Failed PP"<<endl; //debug
    return false;
}
bool Pronoun(string s){
    return Finder(s,"pronouns.txt","Pronoun");
}

bool Preposition(string s){
    return Finder(s,"prepositions.txt","Preposition");
}

bool Noun(string s){
    return Finder(s,"nouns.txt","Noun");
}

bool Verb(string s){
    return Finder(s,"verbs.txt","Verb");
}
bool Det(string s){
    return Finder(s,"determiners.txt","Det");
}

int main(){
	string input; //input string
	cout<<"Enter the sentence to parse\n";
	getline(cin,input); //get string from user
	int nWords=NumOfWords(input);
	gnWords=nWords;
	cout<<"Number of Words in string: "<<nWords<<endl; //debug
	WordCut(input);
	cout<<"S\n";
	S(input);
	

  return 0;
}
