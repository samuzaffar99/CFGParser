#include <algorithm> //vv  nice Abdullah
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
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
    cout<<"String to Find: "<<s<<endl; //debug
    while(!F.eof()){
        getline(F,s2);
        if(s2==s){
            cout<<"String Found: "<<s<<endl; //debug
            return true;
        }
    }
    return false;
}

class Parser{
string input; //input string
int nWords; //Number of words
int cWords;
vector<string> V;
vector<string> V1;
bool DebugOut;
public:
    Parser(){
        cout<<"Enter the sentence to parse\n";
        getline(cin,input); //get string from user
        nWords=NumOfWords(input);
        DebugOut=1;
        cWords=0;
        if(DebugOut){
            cout<<"Number of Words in string: "<<nWords<<endl; //debug
        }
    }

    bool Parse(){
        if(input!=""){
            V1.push_back("S");
            if(S(input)){
                V.push_back("S");
                if(DebugOut){
                    cout<<"S"<<endl; //debug
                }
                return true;
            }
            if(DebugOut){
                cout<<"Failed Parse"<<endl; //debug
            }
            V1.pop_back();
            return false;
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
//        for(string const& i: list) {
//            cout<<i<<"\n";
//        }
        cout<<endl;
    }

    void VInsert(string t){
        if(t=="Det Nominal" || t=="Noun Nominal" || t=="ProperNoun" || t=="Preposition NP" || t=="Verb NP" || t=="Verb PP" || t=="Verb NP PP"){
            //insert
        }
    }

    void Print(){
        V=V1;
        int k=0;
        if(V.empty()|| cWords!=nWords){
            if(DebugOut){
                cout<<nWords<<" "<<cWords<<endl; //debug
            }
            cout<<"Incorrect Structure"<<endl;
            return;
        }
        string t,s;
        int n=0;
        while(k!=V.size()){
            s=V.at(k)+" "+s;
            //V.pop_back();
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
            k++;
        }
    }
    bool S(string s){
        V1.push_back("NP VP");
        if(NP(s) && VP(WordCut(s))){
            V.push_back("NP VP");
            if(DebugOut){
                cout<<"NP VP"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();
        if(DebugOut){
            cout<<"Failed S"<<endl; //debug
        }
        return false;
    }

    bool NP(string s){
        V1.push_back("Pronoun");cWords++;
        if(Pronoun(s)){
            V.push_back("Pronoun");
            if(DebugOut){
                cout<<"Pronoun"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("ProperNoun");cWords++;
        if(ProperNoun(s)){
            V.push_back("ProperNoun");
            if(DebugOut){
                cout<<"ProperNoun"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Det Nominal");cWords++;
        if(Det(s) && Nominal(WordCut(s))){
            V.push_back("Det Nominal");
            if(DebugOut){
                cout<<"Det Nominal"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        if(DebugOut){
            cout<<"Failed NP"<<endl; //debug
        }
        return false;
    }

    bool Nominal(string s){
        V1.push_back("Noun Nominal");cWords++;
        if(Noun(s) && Nominal(WordCut(s))){
            V.push_back("Noun Nominal");
            if(DebugOut){
                cout<<"Noun Nominal"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Noun");cWords++;
        if(Noun(s)){
            V.push_back("Noun");
            if(DebugOut){
                cout<<"Noun"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        if(DebugOut){
            cout<<"Failed Nominal"<<endl; //debug
        }
        return false;
    }

    bool VP(string s){
        V1.push_back("Verb NP");cWords++;
        if(Verb(s) && NP(WordCut(s))){
            V.push_back("Verb NP");
            if(DebugOut){
                cout<<"Verb NP"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Verb NP PP");cWords++;
        if(Verb(s) && NP(WordCut(s)) && PP(WordCut(WordCut(s)))){
            V.push_back("Verb NP PP");
            if(DebugOut){
                cout<<"Verb NP PP"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Verb PP");cWords++;
        if(Verb(s) && PP(WordCut(s))){
            V.push_back("Verb PP");
            if(DebugOut){
                cout<<"Verb PP"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Verb");cWords++;
        if(Verb(s)){
            V.push_back("Verb");
            if(DebugOut){
                cout<<"Verb"<<endl;
            }
            return true;
        }
        V1.pop_back();cWords--;

        if(DebugOut){
            cout<<"Failed VP"<<endl; //debug
        }
        return false;
    }

    bool PP(string s){
        V1.push_back("Preposition NP");cWords++;
        if(Preposition(s) && NP(WordCut(s))){
            V.push_back("Preposition NP");
            if(DebugOut){
                cout<<"Preposition NP"<<endl; //debug
            }
            return true;
        }
        V1.pop_back();cWords--;

        if(DebugOut){
            cout<<"Failed PP"<<endl; //debug
        }
        return false;
    }

    bool Pronoun(string s){
        //V1.push_back("Pronoun");
        if(Finder(s,"pronouns.txt")){
            //cWords++;
            return true;
        }
        //V1.pop_back();
        return false;
    }

    bool Preposition(string s){
        //V1.push_back("Preposition");
        if(Finder(s,"prepositions.txt")){
            //cWords++;
            return true;
        }
        //V1.pop_back();

        return false;
    }

    bool Noun(string s){
        //V1.push_back("Noun");
        if(Finder(s,"nouns.txt")){
            //cWords++;
            return true;
        }
        //V1.pop_back();
        return false;
    }

    bool Verb(string s){
        //V1.push_back("Verb");
        if(Finder(s,"verbs.txt")){
            //cWords++;
            return true;
        }
        //V1.pop_back();
        return false;
    }

    bool Det(string s){
        //V1.push_back("Det");
        if(Finder(s,"determiners.txt")){
            //cWords++;
            return true;
        }
        //V1.pop_back();
        return false;
    }

    bool ProperNoun(string s){
        //V1.push_back("ProperNoun");
        //V1.pop_back();
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
