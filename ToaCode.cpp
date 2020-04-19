#include <algorithm> //vv  nice Abdullah
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

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
bool ProperNoun(string s);

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
    string s2;
    if(NumOfWords(s)>1){
        s2=s.substr(s.find(" ")+1);
    }
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
bool Finder(string s,string FN){
    ifstream F(FN);
    string s2;
    s=GetFirst(s);
    //cout<<"String to Find: "<<s<<endl; //debug
    while(!F.eof()){
        getline(F,s2);
        if(s2==s){
            return true;
        }
    }
    return false;
}

class Parser{
string input; //input string
int nWords; //Number of words
vector<string> V;
vector<string> V1;
bool DebugOut;
public:
    Parser(){
        cout<<"Enter the sentence to parse\n";
        getline(cin,input); //get string from user
        nWords=NumOfWords(input);
        DebugOut=1;
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
        for(int i=0;i<V1.size();i++){
            cout<<V1.at(i)<<endl;
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
        V1.push_back("S");
        if(NP(s) && VP(WordCut(s))){
            V.push_back("NP VP");
            if(DebugOut){
                cout<<"NP VP"<<endl; //debug
            }
            return true;
        }
        if(DebugOut){
            cout<<"Failed S"<<endl; //debug
        }
        V1.pop_back();
        return false;
    }

    bool NP(string s){
        V1.push_back("NP");
        if(Pronoun(s)){
            V.push_back("Pronoun");
            if(DebugOut){
                cout<<"Pronoun"<<endl; //debug
            }
            return true;
        }
        else if(ProperNoun(s)){
            V.push_back("ProperNoun");
            if(DebugOut){
                cout<<"ProperNoun"<<endl; //debug
            }
            return true;
        }
        else if(Det(s) && Nominal(WordCut(s))){
            V.push_back("Det Nominal");
            if(DebugOut){
                cout<<"Det Nominal"<<endl; //debug
            }
            return true;
        }
        if(DebugOut){
            cout<<"Failed NP"<<endl; //debug
        }
        V1.pop_back();
        return false;
    }

    bool Nominal(string s){
        V1.push_back("Nominal");
        if(Noun(s) && Nominal(WordCut(s))){
            V.push_back("Noun Nominal");
            if(DebugOut){
                cout<<"Noun Nominal"<<endl; //debug
            }
            return true;
        }
        else if(Noun(s)){
            V.push_back("Noun");
            if(DebugOut){
                cout<<"Noun"<<endl; //debug
            }
            return true;
        }
        if(DebugOut){
            cout<<"Failed Nominal"<<endl; //debug
        }
        V1.pop_back();
        return false;
    }

    bool VP(string s){
        V1.push_back("VP");
        if(Verb(s) && NP(WordCut(s)) && PP(WordCut(WordCut(s)))){
            V.push_back("Verb NP PP");
            if(DebugOut){
                cout<<"Verb NP PP"<<endl; //debug
            }
            return true;
        }
        else if(Verb(s) && NP(WordCut(s))){
            V.push_back("Verb NP");
            if(DebugOut){
                cout<<"Verb NP"<<endl; //debug
            }
            return true;
        }
        else if(Verb(s) && PP(WordCut(s))){
            V.push_back("Verb PP");
            if(DebugOut){
                cout<<"Verb PP"<<endl; //debug
            }
            return true;
        }
        else if(Verb(s)){
            V.push_back("Verb");
            if(DebugOut){
                cout<<"Verb"<<endl;
            }
            return true;
        }
        if(DebugOut){
            cout<<"Failed VP"<<endl; //debug
        }
        V1.pop_back();
        return false;
    }

    bool PP(string s){
        V1.push_back("PP");
        if(Preposition(s) && NP(WordCut(s))){
            V.push_back("Preposition NP");
            if(DebugOut){
                cout<<"Preposition NP"<<endl; //debug
            }
            return true;
        }
        if(DebugOut){
            cout<<"Failed PP"<<endl; //debug
        }
        V1.pop_back();
        return false;
    }

    bool Pronoun(string s){
        V1.push_back("Pronoun");
        if(Finder(s,"pronouns.txt")){
            return true;
        }
        V1.pop_back();
        return false;
    }

    bool Preposition(string s){
        V1.push_back("Preposition");
        if(Finder(s,"prepositions.txt")){
            return true;
        }
        V1.pop_back();
        return false;
    }

    bool Noun(string s){
        V1.push_back("Noun");
        if(Finder(s,"nouns.txt")){
            return true;
        }
        V1.pop_back();
        return false;
    }

    bool Verb(string s){
        V1.push_back("Verb");
        if(Finder(s,"verbs.txt")){
            return true;
        }
        V1.pop_back();
        return false;
    }

    bool Det(string s){
        V1.push_back("Det");
        if(Finder(s,"determiners.txt")){
            return true;
        }
        V1.pop_back();
        return false;
    }

    bool ProperNoun(string s){
        V1.push_back("ProperNoun");
        V1.pop_back();
        return false;
    }
};

int main(){
    Parser A;
    A.Parse();
    //A.Force();
    A.Vout();
    A.Print();
  return 0;
}



