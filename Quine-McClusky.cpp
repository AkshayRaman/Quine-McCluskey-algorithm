#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>

using namespace std;

//Main class
class QM
{
public:

int VARIABLES;
string dontcares;

QM(int a)
{
   VARIABLES=a;
   dontcares.append(a,'-');

}

//function to get the boolean term letters
vector<string> getVars()
{
   vector<string> v;
   string letters[]={"a","b","c","d","e","f","g","h"};
   for(int i=0;i<this->VARIABLES;i++)
    v.push_back(letters[i]);

   return v;
}

/*function to convert decimal to binary
* Eg: 14 = 1110
*/
string decToBin(int n)
{
   if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}

//function to pad zeros to the binary equivalent of digits.
//Eg: If there are 4 variables, 2, that is 10 in binary is represented as 0010
string pad(string bin)
{
   int max=VARIABLES-bin.length();
   for(int i=0; i<max; i++)
       bin="0"+bin;
   return bin;
}

//function to check if two terms differ by just one bit
bool isGreyCode(string a,string b)
{
   int flag=0;
   for(int i=0;i<a.length();i++)
   {
       if(a[i]!=b[i])
        flag++;
   }
   return (flag==1);
}

//function to replace complement terms with don't cares
// Eg: 0110 and 0111 becomes 011-
string replace_complements(string a,string b)
{
   string temp="";
   for(int i=0;i<a.length();i++)
   if(a[i]!=b[i])
       temp=temp+"-";
   else
       temp=temp+a[i];

   return temp;
}

//function to check if string b exists in vector a
bool in_vector(vector<string> a,string b)
{
   for(int i=0;i<a.size();i++)
     if(a[i].compare(b)==0)
      return true;
    return false;
}

//function to reduce minterms
vector<string> reduce(vector<string> minterms)
{
/*for (int i=0; i<minterms.size(); i++)
       cout << minterms[i]<<endl;
       cout <<endl;*/

      vector<string> newminterms;

      int max=minterms.size();
      int* checked = new int[max];
      for(int i=0;i<max;i++)
      {
          for(int j=i;j<max;j++)
          {
               //If a grey code pair is found, replace the differing bits with don't cares.
               if(isGreyCode(minterms[i],minterms[j]))
               {
                  checked[i]=1;
                  checked[j]=1;
                  if(!in_vector(newminterms,replace_complements(minterms[i],minterms[j])))
                     newminterms.push_back(replace_complements(minterms[i],minterms[j]));
               }
          }
      }

      //appending all reduced terms to a new vector
      for(int i=0;i<max;i++)
      {
          //cout<<checked[i]<<endl;
          if(checked[i]!=1 && ! in_vector(newminterms,minterms[i]))
           newminterms.push_back(minterms[i]);
      }

       delete[] checked;
   
       return newminterms;
}


//Converting the boolean minterm into the variables
// Eg: 011- becomes a'bc
string getValue(string a)
{
   string temp="";
   vector<string> vars=this->getVars();
   if(a==dontcares)
     return "1";

   for(int i=0;i<a.length();i++)
   {
     if(a[i]!='-')
     {
        if(a[i]=='0')
         temp=temp+vars[i]+"\'";
        else
         temp=temp+vars[i];
     }
   }
   return temp;
}

//function to check if 2 vectors are equal
bool VectorsEqual(vector<string> a,vector<string> b)
{
   if(a.size()!=b.size())
      return false;

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i])
        return false;
    }
    return true;
}

};

//Main function
int main ()
{
   char check='y';
   while(check=='y')
   {
      int no;
      cout<<endl<<"Enter the number of variables:"<<endl;
      cin>>no;
      if(no > 8 || no < 1)
      {
          cout << "Invalid number of variables (1-8)" << endl;
          continue;
      }
      QM q(no);

      string temp="";
      cout<<"Enter the minterms(RANGE=0-"<<pow(2,no)-1<<") separated by comma:"<<endl;
      cin>>temp;

      //splitting the input
      vector<string> minterms;
      istringstream f(temp);
      string s;
      while (getline(f, s, ','))
      {
          //cout << s << endl;
         int t=atoi(s.data());
         minterms.push_back(q.pad(q.decToBin(t)));
      }

      sort(minterms.begin(),minterms.end());

      do
      {
         minterms=q.reduce(minterms);
         sort(minterms.begin(),minterms.end());
      }while(!q.VectorsEqual(minterms,q.reduce(minterms)));


      int i;
      cout << "The reduced boolean expression in SOP form:" << endl;
      for (i=0;i<minterms.size()-1; i++)
          cout <<q.getValue(minterms[i])<<"+";
      cout<<q.getValue(minterms[i])<<endl;

      cout<<"Would you like to enter another expression? (y/n)"<<endl;
      cin>>check;
   }
   cout<<endl<<"---END--"<<endl<<"Created by Akshay"<<endl;
}
