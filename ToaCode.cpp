#include <algorithm> //vv  nice Abdullah
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
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
stringstream dout;
//bool DebugOut;
public:
    Parser(){
        cout<<"Enter the sentence to parse\n";
        getline(cin,input); //get string from user
        nWords=NumOfWords(input);
        //DebugOut=1;
        cWords=0;
        dout<<"Number of Words in string: "<<nWords<<endl; //debug
    }

    bool Parse(){
        if(input!=""){
            V1.push_back("S");
            if(S(input)){
                V.push_back("S");
                dout<<"S"<<endl; //debug
                return true;
            }
            dout<<"Failed Parse"<<endl; //debug
            V1.pop_back();
            return false;
        }
    }
    void PrintDebug(){
        cout<<dout.str()<<endl;
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
            dout<<nWords<<" "<<cWords<<endl; //debug
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
        dout<<"Testing S"<<endl; //debug
        V1.push_back("NP VP");
        if(NP(s) && VP(WordCut(s))){
            V.push_back("NP VP");
            dout<<"NP VP"<<endl; //debug
            dout<<"Succeeded S"<<endl; //debug
            return true;
        }
        V1.pop_back();
        dout<<"Failed S"<<endl; //debug
        return false;
    }

    bool NP(string s){
        dout<<"Testing NP"<<endl; //debug
        V1.push_back("Pronoun");cWords++;
        if(Pronoun(s)){
            V.push_back("Pronoun");
            dout<<"Pronoun"<<endl; //debug
            dout<<"Succeeded NP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("ProperNoun");cWords++;
        if(ProperNoun(s)){
            V.push_back("ProperNoun");
            dout<<"ProperNoun"<<endl; //debug
            dout<<"Succeeded NP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Det Nominal");cWords++;
        if(Det(s) && Nominal(WordCut(s))){
            V.push_back("Det Nominal");
            dout<<"Det Nominal"<<endl; //debug
            dout<<"Succeeded NP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        dout<<"Failed NP"<<endl; //debug
        return false;
    }

    bool Nominal(string s){
        dout<<"Testing Nominal"<<endl; //debug
        V1.push_back("Noun Nominal");cWords++;
        if(Noun(s) && Nominal(WordCut(s))){
            V.push_back("Noun Nominal");
            dout<<"Noun Nominal"<<endl; //debug
            dout<<"Succeeded Nominal"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Noun");cWords++;
        if(Noun(s)){
            V.push_back("Noun");
            dout<<"Noun"<<endl; //debug
            dout<<"Succeeded Nominal"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        dout<<"Failed Nominal"<<endl; //debug
        return false;
    }

    bool VP(string s){
        dout<<"Testing VP"<<endl; //debug
        V1.push_back("Verb NP");cWords++;
        if(Verb(s) && NP(WordCut(s))){
            V.push_back("Verb NP");
            dout<<"Verb NP"<<endl; //debug
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Verb NP PP");cWords++;
        if(Verb(s) && NP(WordCut(s)) && PP(WordCut(WordCut(s)))){
            V.push_back("Verb NP PP");
            dout<<"Verb NP PP"<<endl; //debug
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Verb PP");cWords++;
        if(Verb(s) && PP(WordCut(s))){
            V.push_back("Verb PP");
            dout<<"Verb PP"<<endl; //debug
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        V1.push_back("Verb");cWords++;
        if(Verb(s)){
            V.push_back("Verb");
            dout<<"Verb"<<endl;
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        dout<<"Failed VP"<<endl; //debug
        return false;
    }

    bool PP(string s){
        dout<<"Testing PP"<<endl; //debug
        V1.push_back("Preposition NP");cWords++;
        if(Preposition(s) && NP(WordCut(s))){
            V.push_back("Preposition NP");
            dout<<"Preposition NP"<<endl; //debug
            dout<<"Succeeded PP"<<endl; //debug
            return true;
        }
        V1.pop_back();cWords--;

        dout<<"Failed PP"<<endl; //debug
        return false;
    }

    bool Pronoun(string s){
        dout<<"Testing Pronoun"<<endl; //debug
        //V1.push_back("Pronoun");
        if(Finder(s,"pronouns.txt")){
            //cWords++;
            dout<<"Succeeded Pronoun"<<endl; //debug
            return true;
        }
        //V1.pop_back();
        dout<<"Failed Pronoun"<<endl; //debug
        return false;
    }

    bool Preposition(string s){
        dout<<"Testing Preposition"<<endl; //debug
        //V1.push_back("Preposition");
        if(Finder(s,"prepositions.txt")){
            //cWords++;
            dout<<"Succeeded ProperNoun"<<endl; //debug
            return true;
        }
        //V1.pop_back();
        dout<<"Failed Preposition"<<endl; //debug
        return false;
    }

    bool Noun(string s){
        dout<<"Testing Noun"<<endl; //debug
        //V1.push_back("Noun");
        if(Finder(s,"nouns.txt")){
            //cWords++;
            dout<<"Succeeded Noun"<<endl; //debug
            return true;
        }
        //V1.pop_back();
        dout<<"Noun"<<endl; //debug
        return false;
    }

    bool Verb(string s){
        dout<<"Testing Verb"<<endl; //debug
        //V1.push_back("Verb");
        if(Finder(s,"verbs.txt")){
            //cWords++;
            dout<<"Succeeded Verb"<<endl; //debug
            return true;
        }
        //V1.pop_back();
        dout<<"Failed Verb"<<endl; //debug
        return false;
    }

    bool Det(string s){
        dout<<"Testing Det"<<endl; //debug
        //V1.push_back("Det");
        if(Finder(s,"determiners.txt")){
            //cWords++;
            dout<<"Succeeded Det"<<endl; //debug
            return true;
        }
        //V1.pop_back();
        dout<<"Failed Det"<<endl; //debug
        return false;
    }

    bool ProperNoun(string s){
        dout<<"Testing ProperNoun"<<endl; //debug
        //V1.push_back("ProperNoun");
        if(s[0]>='A' && s[0]<='Z'){
            cout<<"Proper Noun is: "<<s<<endl;
            //cWords++;
            dout<<"Succeeded ProperNoun"<<endl; //debug
            return true;
        }
        //V1.pop_back();
        dout<<"Failed ProperNoun"<<endl; //debug
        return false;
    }
};

int main(){
    Parser A;
    A.Parse();
    //A.Force();
    A.Vout();
    A.Print();
    A.PrintDebug();
  return 0;
}
