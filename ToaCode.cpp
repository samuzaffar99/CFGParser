#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include<cstring>
#include <bits/stdc++.h>
using namespace std;
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
    cout<<s2<<endl; //debug
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
bool Finder(string s,string FN){
    ifstream F(FN);
    string s2;
    s=GetFirst(s);
    cout<<"String to Find: "<<s<<endl; //debug
    while(!F.eof()){
        getline(F,s2);
        if(s2==s){
            cout<<"Match Found: "<<s2<<endl; //debug
            //cout<<s2<<endl; //debug
            return true;
        }
    }
    return false;
}
bool S(string s){
    if(NP(s)){
        if(VP(WordCut(s))){
            cout<<"NP VP"<<endl; //debug
            return true;
        }
    }
    cout<<"Failed S"<<endl; //debug
    return false;
}

bool NP(string s){
    if(Pronoun(s)){
        cout<<"Pronoun"<<endl; //debug
        return true;
    }
//    if(ProperNoun(s)){
//        return true;
//    }
    if(Det(s)){
        if(Nominal(WordCut(s))){
            cout<<"Det Nominal"<<endl; //debug
            return true;
        }
    }
    cout<<"Failed NP"<<endl; //debug
    return false;
}

bool Nominal(string s){
    if(Noun(s)){
        if(NumOfWords(s)>1){
            if(Nominal(WordCut(s))){
                cout<<"Noun Nominal"<<endl; //debug
                return true;
            }
        }
        cout<<"Noun"<<endl; //debug
        return true;
    }
    cout<<"Failed Nominal"<<endl; //debug
    return false;
}

bool VP(string s){
    if(Verb(s)){
        if(NP(WordCut(s))){
            if(PP(WordCut(WordCut(s)))){
                cout<<"Verb NP PP"<<endl; //debug
                return true;
            }
            cout<<"Verb NP"<<endl; //debug
            return true;
        }
        if(PP(WordCut(s))){
            cout<<"Verb NP"<<endl; //debug
            return true;
        }
    }
    cout<<"Failed VP"<<endl; //debug
    return false;
}

bool PP(string s){
    if(Preposition(s)){
        if(NP(WordCut(s))){
            cout<<"Preposition NP"<<endl; //debug
            return true;
        }
    }
    cout<<"Failed PP"<<endl; //debug
    return false;
}
bool Pronoun(string s){
    return Finder(s,"pronouns.txt");
}

bool Preposition(string s){
    return Finder(s,"prepositions.txt");
}

bool Noun(string s){
    return Finder(s,"nouns.txt");
}

bool Verb(string s){
    return Finder(s,"verbs.txt");
}
bool Det(string s){
    return Finder(s,"determiners.txt");
}
//string* Break(string word);
//int NumOfWords(string sen);
//Ahmeds version
//bool S(string word,stack <string> &s1){
//	if(NP(word,s1) || VP(word,s1)){
//		s1.push("NP ");
//		return true;
//	}
//	return true; //redundant? function always returns true
//}
//My version
//bool S(string word,stack <string> &s1){
//	if(NP(word,s1)){
//        cout<<"Pushed NP"<<endl; //debug
//		s1.push("NP ");
//		return true;
//	}
//	if(VP(word,s1)){
//	    cout<<"Pushed VP"<<endl; //debug
//        s1.push("VP ");
//        return true;
//	}
//	return false;
//}
//bool NP(string word,stack <string> &s1){
//	if(ProNoun(word,s1)){
//        cout<<"Pushed Pro"<<endl; //debug
//		s1.push("Pro ");
//		return true;
//	}
//	//Det(word);
//	if(Nom(word,s1)){
//	    cout<<"Pushed Nom"<<endl; //debug
//		s1.push("Nom ");
//		return true;
//	}
//	return false;
//}
//bool VP(string word,stack <string> &s1){
//	//Verb(word);
//	NP(word,s1);
//}
//bool Nom(string word,stack <string> &s1){
//	if(Noun(word,s1)){
//		s1.push("Noun ");
//		return true;
//	}
//	else return false;
//	//Nom(word);
//}
////reading corpus
//bool Noun(string word,stack <string> &s1){
//	string* var;
//	string noun[6801];
//	int i=0;
//	ifstream myfile ("nouns.txt");
//	if (myfile.is_open())
//	{
//	while ( getline (myfile,noun[i]) )
//	{
//	  i++;
//	}
//	myfile.close();
//	}
//	else cout << "Unable to open file";
//	if (binary_search(noun, noun + 6801,word)){
//		//cout<<word<<endl;
//		s1.push(word);
//		return true;
//	}
//	else return false;
//}
//bool ProNoun(string word,stack <string> &s1){
//	string* var;
//	string pronoun[77];
//	int i=0;
//	ifstream myfile ("pronouns.txt");
//	if (myfile.is_open()){
//        while ( getline (myfile,pronoun[i]) ){
//          i++;
//        }
//        myfile.close();
//	}
//	else cout << "Unable to open file";
//	if (binary_search(pronoun, pronoun + 77,word)){
//			s1.push(word);
//			return true;
//    }
//    else return false;
//}
//bool Verb(string word,stack <string> &s1){
//	string* var;
//	string noun[6801];
//	int i=0;
//	ifstream myfile ("verb.txt");
//	if(myfile.is_open()){
//        while( getline (myfile,noun[i]) ){
//          i++;
//        }
//        myfile.close();
//	}
//	else cout << "Unable to open file";
//	if (binary_search(noun, noun + 6801,word)){
//		//cout<<word<<endl;
//		s1.push(word);
//		return true;
//	}
//	else return false;
//}
//string* Break(string sen){
//	string* var=new string[10];
//	for(int i=0,x=0;i<=strlen(sen.c_str());i++){
//		if(sen[i]==' ' || i==strlen(sen.c_str())){
//			x++;
//		}
//		else{
//			var[x]+=sen[i];
//		}
//	}
//	cout<<*var<<endl; //debug
//	return var;
//}




int main(){
	string input; //input string
	//string* var;
	//bool check=true;
	cout<<"Enter the sentence to parse\n";
	getline(cin,input); //get string from user
	//var=Break(input);
	int nWords=NumOfWords(input);
	cout<<"Number of Words in string: "<<nWords<<endl; //debug
	WordCut(input);
	S(input);
	//stack <string> s[nWords];

	//cout<<"S"<<endl;
//	for(int i=0;i<nWords;i++){
//		if(S(var[i])==0){ //eliminate the need for check
//            cout<<"Incorrect Structure\n";
//            return 0;
//		}
//	}
//	int i=nWords;
//	while(!s[i].empty()){
//		if(i==nWords){ //why is this?
//			i=0;
//			cout<<endl;
//		}
//		cout<<s[i].top();
//		s[i].pop();
//		i++;
//	}
  return 0;
}



