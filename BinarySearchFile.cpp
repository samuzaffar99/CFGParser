#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int binarySearchString(string arr[],string word,int c) 
{
	int lower=0;
	int upper=c-1;
	
	while (lower<=upper) 
	{
    	int mid=lower+(upper-lower)/2;
    	int res;
    	
    	if (word==(arr[mid]))
    	{
    		res=0;
		}
    	if (res==0)
    	{
    		return mid;
		}
    	if (word>(arr[mid]))
    	{
    		lower=mid+1;
		}
    	else
    	{
    		upper=mid-1;
		}
   }
   return -1;
}
int main () 
{
	string input;
    int count=0;
    int c=1;
    
    cout<<"Input sentence"<<endl;
	getline(cin,input);
	
	for (int i=0;i<input.length();i++)
	{
		if(input[i]==' ')
		{
			c++;
		}
	}
	
	string arr[c];
    string str;
        
    for(auto i:input)
    {
		if(i==' ')
    	{
        	arr[count]=str;
        	count++;
            str.erase();
        }
        else
        {
            str=str+i;
		}
    }
	    
    arr[count]=str;
    count++;
	
	string word;
	cout<<"Input search term"<<endl;
	cin>>word;
	
	int result=binarySearchString(arr,word,c);
   
	if(result==-1)
	{
		cout<<("Element not present");
	}
	else
	{
		cout<<("Element found at index ")<<result;
	}
}
