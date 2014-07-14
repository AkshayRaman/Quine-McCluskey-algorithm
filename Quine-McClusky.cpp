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
#include <conio.h>
#include <math.h>

using namespace std;

class QM
{
public:

int VARIABLES;
string dontcares;

vector<string> getVars()
{
   vector<string> v;
   string letters[]={"a","b","c","d","e","f","g","h"};
   for(int i=0;i<this->VARIABLES;i++)
    v.push_back(letters[i]);

   return v;
}

QM(int a)
{
   VARIABLES=a;
   dontcares.append(a,'-');

}

string decToBin(int n)
{
   if ( n == 0 ) return "0";
   if ( n == 1 ) return "1";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}

string pad(string bin)
{
   int max=VARIABLES-bin.length();
   for(int i=0; i<max; i++)
       bin="0"+bin;
   return bin;
}

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

bool in_vector(vector<string> a,string b)
{
   for(int i=0;i<a.size();i++)
     if(a[i].compare(b)==0)
      return true;
    return false;
   }

vector<string> reduce(vector<string> minterms)
{
/*for (int i=0; i<minterms.size(); i++)
       cout << minterms[i]<<endl;
       cout <<endl;*/

 vector<string> newminterms;

      int max=minterms.size();
      int checked[max];
      for(int i=0;i<max;i++)
      {
          for(int j=i;j<max;j++)
          {
               if(isGreyCode(minterms[i],minterms[j]))
           {
               checked[i]=1;checked[j]=1;
               if(!in_vector(newminterms,replace_complements(minterms[i],minterms[j])))
               newminterms.push_back(replace_complements(minterms[i],minterms[j]));
           }
          }

      }

      for(int i=0;i<max;i++)
      {
          //cout<<checked[i]<<endl;
          if(checked[i]!=1 && ! in_vector(newminterms,minterms[i]))
           newminterms.push_back(minterms[i]);
      }

       return newminterms;
}

string getValue(string a)
{
   string temp="";
   vector<string> vars=this->getVars();
   if(a==dontcares)
     return "1";
   else
   {
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
   }
   return temp;
}

bool VectorsEqual(vector<string> a,vector<string> b)
{
   if(a.size()!=b.size())
 return false;

 else
{
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i])
        return false;
    }
    return true;

}

}

};

int main ()
{
   char check='y';
   while(check=='y')
   {
   system("CLS");
   int no;
   cout<<endl<<"Enter the number of variables:"<<endl;
   cin>>no;

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
   cout<<"The reduced boolean expression in SOP form:"<<endl;

   for (i=0;i<minterms.size()-1; i++)
       cout <<q.getValue(minterms[i])<<"+";
       cout<<q.getValue(minterms[i])<<endl;

    cout<<"Would you like to enter another expression? (y/n)"<<endl;
    cin>>check;
   }
   cout<<endl<<"Thank you"<<endl<<"Created by Akshay";
   //getch();
}
