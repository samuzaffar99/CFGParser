#include <algorithm> //vv  nice Abdullah
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstring>
#include <bits/stdc++.h>
#include <vector>
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
bool ProperNoun(string s);
void Replace(string s1);
void Showlist(list <string> g);
//list
list <string> plist;
list<string>::iterator itr;
//end list
void Showlist(list <string> g){
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
//        	Replace(str);
//			Showlist(plist);
//            Replace(s2); //debug
//            Showlist(plist);
            return true;
        }
    }
    return false;
}

class Parser{
string input; //input string
int nWords; //Number of words
vector<string> V;
bool DebugOut;
public:
    Parser(){
        cout<<"Enter the sentence to parse\n";
        getline(cin,input); //get string from user
        nWords=NumOfWords(input);
        DebugOut=0;
        if(DebugOut){
            cout<<"Number of Words in string: "<<nWords<<endl; //debug
        }
    }

    void Parse(){
        if(input!=""){
            S(input);
            V.push_back("S");
            if(DebugOut){
                cout<<"S"<<endl; //debug
            }
        }
    }

    void Force(){
        V.push_back("Noun");
        V.push_back("Noun Nominal");
        V.push_back("Det Nominal");
        V.push_back("Verb NP");
        V.push_back("Pronoun");
        V.push_back("NP VP");
        V.push_back("S");
    }

    void Vout(){
        cout<<"Vector Contains: "<<endl;
        for(int i=0;i<V.size();i++){
            cout<<V.at(i)<<endl;
        }
        cout<<endl;
    }

    void VInsert(string t){
        if(t=="Det Nominal" || t=="Noun Nominal" || t=="ProperNoun" || t=="Preposition NP" || t=="Verb NP" || t=="Verb PP" || t=="Verb NP PP"){
            //insert
        }
    }
    void Print(){
        if(V.empty()){
            cout<<"Incorrect Structure"<<endl;
            return;
        }
        string t,s;
        int n=0;
        while(!V.empty()){
            t=V.back();
            s=t+" "+s;
            V.pop_back();
            if(t=="S" || t=="NP" || t=="VP" || t=="PP" || t=="Nominal" || t=="NP VP"){
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' '){
                        nt++;
                    }
                    cout<<input[i];
                }
                cout<<s<<endl;
            }
            if(t=="Preposition" || t=="Noun" || t=="Verb" || t=="Det" || t=="Pronoun"){
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' '){
                        nt++;
                    }
                    cout<<input[i];
                }
                cout<<s<<endl;
                n++;
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' ' || input[i]==0){
                        nt++;
                    }
                    cout<<input[i];
                }
                cout<<endl;
            }
            if(t=="Det Nominal" || t=="Noun Nominal" || t=="ProperNoun" || t=="Preposition NP" || t=="Verb NP" || t=="Verb PP"){
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' '){
                        nt++;
                    }
                    cout<<input[i];
                }
                cout<<s<<endl;
                n++;
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' ' || input[i]==0){
                        nt++;
                    }
                    cout<<input[i];
                }
                s=WordCut(s);
                cout<<s<<endl;
            }
            if(t=="Verb NP PP"){
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' '){
                        nt++;
                    }
                    cout<<input[i];
                }
                cout<<s<<endl;
                n++;
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' ' || input[i]==0){
                        nt++;
                    }
                    cout<<input[i];
                }
                s=WordCut(s);
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' ' || input[i]==0){
                        nt++;
                    }
                    cout<<input[i];
                }
                s=WordCut(s);
                cout<<s<<endl;
            }
            s=WordCut(s);
        }
    }

    void Print2(){
        if(V.empty()){
            cout<<"Incorrect Structure"<<endl;
            return;
        }
        string t,s;
        int n=0;
        while(!V.empty()){
            s=V.back()+" "+s;
            V.pop_back();
            t=GetFirst(s);
            for(int i=0,nt=0;nt!=n;i++){
                if(input[i]==' ' || input[i]==0){
                    nt++;
                }
                cout<<input[i];
            }
            cout<<s<<endl;
            if(t=="Preposition" || t=="Noun" || t=="Verb" || t=="Det" || t=="Pronoun"){
                n++;
                s=WordCut(s);
                for(int i=0,nt=0;nt!=n;i++){
                    if(input[i]==' ' || input[i]==0){
                        nt++;
                    }
                    cout<<input[i];
                }
                cout<<s<<endl;
            }
            s=WordCut(s);
        }
    }

    bool S(string s){
//        plist.push_back("NP");
//        plist.push_back("VP");
//        itr=plist.begin();
//        Showlist(plist);
        if(NP(s)){
//            itr++;
            if(VP(WordCut(s))){
                V.push_back("NP VP");
                if(DebugOut){
                    cout<<"NP VP"<<endl; //debug
                }
                return true;
            }
        }
        if(DebugOut){
            cout<<"Failed S"<<endl; //debug
        }
        return false;
    }

    bool NP(string s){
        if(Pronoun(s)){
            V.push_back("Pronoun");
            if(DebugOut){
                cout<<"Pronoun"<<endl; //debug
            }
            return true;
        }
//        cout<<*itr<<endl;
        if(ProperNoun(s)){
            V.push_back("ProperNoun");
            if(DebugOut){
                cout<<"ProperNoun"<<endl; //debug
            }
            return true;
        }
        if(Det(s)){
//            cout<<"here\n"; //debug
//            plist.push_back("Nominal");
//            Showlist(plist);
//            itr++;
            if(Nominal(WordCut(s))){
                V.push_back("Det Nominal");
                if(DebugOut){
                    cout<<"Det Nominal"<<endl; //debug
                }
                return true;
            }
        }
        if(DebugOut){
            cout<<"Failed NP"<<endl; //debug
        }
        return false;
    }

    bool Nominal(string s){
        if(Noun(s)){
            if(NumOfWords(s)>1){
                if(Nominal(WordCut(s))){
                    V.push_back("Noun Nominal");
                    if(DebugOut){
                        cout<<"Noun Nominal"<<endl; //debug
                    }
                    return true;
                }
            }
            V.push_back("Noun");
            if(DebugOut){
                cout<<"Noun"<<endl; //debug
            }
            return true;
        }
        if(DebugOut){
            cout<<"Failed Nominal"<<endl; //debug
        }
        return false;
    }

    bool VP(string s){
//    	itr++;
//    	Replace("Verb");
//    	Showlist(plist);
        if(Verb(s)){
//                plist.push_back("NP");
//                Showlist(plist);
//                itr++;
            if(NP(WordCut(s))){
                if(PP(WordCut(WordCut(s)))){
                    V.push_back("Verb NP PP");
                    if(DebugOut){
                        cout<<"Verb NP PP"<<endl; //debug
                    }
                    return true;
                }
                V.push_back("Verb NP");
                if(DebugOut){
                    cout<<"Verb NP"<<endl; //debug
                }
                return true;
            }
            V.push_back("Verb");
            if(DebugOut){
                cout<<"Verb"<<endl;
            }
            return true;
            if(PP(WordCut(s))){
                V.push_back("Verb PP");
                if(DebugOut){
                    cout<<"Verb PP"<<endl; //debug
                }
                return true;
            }

        }
        if(DebugOut){
            cout<<"Failed VP"<<endl; //debug
        }
        return false;
    }

    bool PP(string s){
        if(Preposition(s)){
            if(NP(WordCut(s))){
                V.push_back("Preposition NP");
                if(DebugOut){
                    cout<<"Preposition NP"<<endl; //debug
                }
                return true;
            }
        }
        if(DebugOut){
            cout<<"Failed PP"<<endl; //debug
        }
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

    bool ProperNoun(string s){
        return false;
    }
};

int main(){
    Parser A;
    A.Parse();
    //A.Force();
    A.Vout();
    A.Print2();
  return 0;
}



