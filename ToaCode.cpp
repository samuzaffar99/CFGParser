#include <algorithm> //vv  nice Abdullah
#include <iostream>
#include <fstream>
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

string WordCut(string s, int i=1){ //removes first word from string
    string s2;
    if(NumOfWords(s)>1){
        s2=s.substr(s.find(" ")+1);
    }
    while(i>1){
        s2=s2.substr(s2.find(" ")+1);
        i--;
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


class Parser{
string input; //input string
int nWords; //Number of words
int cWords;
vector<string> V;
stringstream dout;
public:
    Parser(){
        cout<<"Enter the sentence to parse\n";
        getline(cin,input); //get string from user
        nWords=NumOfWords(input);
        cWords=0;
        dout<<"Number of Words in string: "<<nWords<<endl; //debug
    }

    bool Parse(){
        if(input!=""){
            dout<<"Testing Parse"<<endl; //debug
            V.push_back("S");
            if(S(input)){
                dout<<"Succeeded Parse"<<endl; //debug
                return true;
            }
            dout<<"Failed Parse"<<endl; //debug
            V.pop_back();
            return false;
        }
        return false;
    }

    void PrintDebug(){
        cout<<dout.str()<<endl;
    }

    void Force(){
        V.push_back("S");
        V.push_back("NP VP");
        V.push_back("Pronoun");
        V.push_back("Verb NP");
        V.push_back("Det Nominal");
        V.push_back("Noun Nominal");
        V.push_back("Noun");
    }

    void Vout(){
        cout<<"Vector Contains: "<<endl;
        for(int i=0;i<V.size();i++){
            cout<<V.at(i)<<endl;
        }
        cout<<endl;
    }

    void Print(){
        int k=0;
        if(V.empty()|| cWords!=nWords){
            dout<<"Number of Words:"<<nWords<<" Discovered Words:"<<cWords<<endl; //debug
            cout<<"Incorrect Structure"<<endl;
            return;
        }
        string t,s;
        int n=0;
        while(k!=V.size()){
            s=V.at(k)+" "+s;
            for(int i=0,nt=0;nt!=n;i++){
                if(input[i]==' ' || input[i]==0){
                    nt++;
                }
                cout<<input[i];
            }
            cout<<s<<endl;

            t=GetFirst(s);
            if(t=="Preposition" || t=="Noun" || t=="Verb" || t=="Det" || t=="Pronoun" || t=="ProperNoun"){
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

    bool Finder(string s,string FN){
        ifstream F(FN);
        string s2;
        s=GetFirst(s);
        dout<<"String to Find: "<<s<<endl; //debug
        while(!F.eof()){
            getline(F,s2);
            if(s2==s){
                dout<<"String Found: "<<s<<endl; //debug
                return true;
            }
        }
        return false;
    }

    bool S(string s){
        if(s==""){
            return false;
        }

        int tWords=cWords;
        dout<<"Testing S"<<endl; //debug
        V.push_back("NP VP");
        vector<string> Vt=V;
        if(NP(s) && VP(WordCut(s,cWords)) && cWords==nWords){
            dout<<"Succeeded S"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;
        if(NP(s)){
            Vt=V;
            int i=1;
            while(cWords>0){
                V=Vt;
                cWords--;
                for(int t=i;t>0;t--){
                    V.pop_back();
                }
                i++;
                V.pop_back();
                V.push_back("Noun");
                if(cWords==1 && V.back()=="Noun"){
                    break;
                }
                if(VP(WordCut(s,cWords))){
                    dout<<"Succeeded S"<<endl; //debug
                    return true;
                }
            }
        }
        V.pop_back();
        dout<<"Failed S"<<endl; //debug
        return false;
    }

    bool NP(string s){
        if(s==""){
            return false;
        }
        dout<<"Testing NP"<<endl; //debug
        vector<string> Vt=V;
        int tWords=cWords;

        V.push_back("Det Nominal");
        if(Det(s) && Nominal(WordCut(s))){
            dout<<"Succeeded NP"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;

        V.push_back("Pronoun");
        if(Pronoun(s)){
            dout<<"Succeeded NP"<<endl; //debug
            return true;
        }
        V.pop_back();

        V.push_back("ProperNoun");
        if(ProperNoun(s)){
            dout<<"Succeeded NP"<<endl; //debug
            return true;
        }
        V.pop_back();



        dout<<"Failed NP"<<endl; //debug
        return false;
    }

    bool Nominal(string s){
        if(s==""){
            return false;
        }
        dout<<"Testing Nominal"<<endl; //debug
        vector<string> Vt=V;
        int tWords=cWords;
        V.push_back("Noun Nominal");
        if(Noun(s) && Nominal(WordCut(s))){
            dout<<"Succeeded Nominal"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;


        V.push_back("Noun");
        if(Noun(s)){
            dout<<"Succeeded Nominal"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;

        dout<<"Failed Nominal"<<endl; //debug
        return false;
    }

    bool VP(string s){
        if(s==""){
            return false;
        }
        dout<<"Testing VP"<<endl; //debug
        int tWords=cWords;
        vector<string> Vt=V;
        V.push_back("Verb NP PP");
        if(Verb(s) && NP(WordCut(s)) && PP(WordCut(s,cWords-tWords))){
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;

        V.push_back("Verb NP");
        if(Verb(s) && NP(WordCut(s))){
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;

        V.push_back("Verb PP");
        if(Verb(s) && PP(WordCut(s))){
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;

        V.push_back("Verb");
        if(Verb(s)){
            dout<<"Succeeded VP"<<endl; //debug
            return true;
        }
        V=Vt;cWords=tWords;

        dout<<"Failed VP"<<endl; //debug
        return false;
    }

    bool PP(string s){
        if(s==""){
            return false;
        }
        dout<<"Testing PP"<<endl; //debug
        V.push_back("Preposition NP");
        if(Preposition(s) && NP(WordCut(s))){
            dout<<"Succeeded PP"<<endl; //debug
            return true;
        }
        V.pop_back();

        dout<<"Failed PP"<<endl; //debug
        return false;
    }

    bool Pronoun(string s){
        dout<<"Testing Pronoun"<<endl; //debug
        if(Finder(s,"pronouns.txt")){
            cWords++;
            dout<<"Succeeded Pronoun"<<endl; //debug
            dout<<GetFirst(s)<<" is a Pronoun"<<endl; //debug
            return true;
        }

        dout<<"Failed Pronoun"<<endl; //debug
        return false;
    }

    bool Preposition(string s){
        dout<<"Testing Preposition"<<endl; //debug
        if(Finder(s,"prepositions.txt")){
            cWords++;
            dout<<"Succeeded ProperNoun"<<endl; //debug
            dout<<GetFirst(s)<<" is a Preposition"<<endl; //debug
            return true;
        }

        dout<<"Failed Preposition"<<endl; //debug
        return false;
    }

    bool Noun(string s){
        dout<<"Testing Noun"<<endl; //debug
        if(Finder(s,"nouns.txt")){
            cWords++;
            dout<<"Succeeded Noun"<<endl; //debug
            dout<<GetFirst(s)<<" is a Noun"<<endl; //debug
            return true;
        }

        dout<<"Failed Noun"<<endl; //debug
        return false;
    }

    bool Verb(string s){
        dout<<"Testing Verb"<<endl; //debug
        if(Finder(s,"verbs.txt")){
            cWords++;
            dout<<"Succeeded Verb"<<endl; //debug
            dout<<GetFirst(s)<<" is a Verb"<<endl; //debug
            return true;
        }

        dout<<"Failed Verb"<<endl; //debug
        return false;
    }

    bool Det(string s){
        dout<<"Testing Det"<<endl; //debug
        if(Finder(s,"determiners.txt")){
            cWords++;
            dout<<"Succeeded Det"<<endl; //debug
            dout<<GetFirst(s)<<" is a Det"<<endl; //debug
            return true;
        }

        dout<<"Failed Det"<<endl; //debug
        return false;
    }

    bool ProperNoun(string s){
        dout<<"Testing ProperNoun"<<endl; //debug
        if(s[0]>='A' && s[0]<='Z'){
            cWords++;
            dout<<"Succeeded ProperNoun"<<endl; //debug
            dout<<GetFirst(s)<<" is a ProperNoun"<<endl; //debug
            return true;
        }

        dout<<"Failed ProperNoun"<<endl; //debug
        return false;
    }

};

int main(){
    char opt;
    while(1){
        Parser A;
        A.Parse();
        //A.Force();
        //A.Vout();
        A.Print();
        //A.PrintDebug();
        cout<<"Press 0 to exit, any other key to continue.."<<endl;
        cin>>opt;
        if(opt=='0'){
            break;
        }
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return 0;
}
