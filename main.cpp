#include <iostream>
#include<string>
#include<unordered_map>
#include<queue>
#include<bits/stdc++.h>
#include<math.h>

using namespace std;

class node 
{
    public:
    
    char ch;
    int frequency;
    node*left;
    node*right;
    
    node(char c,int f)
    {
        ch=c;
        frequency=f;
        this->left=NULL;
        this->right=NULL;
    }

};

class Comp {
				public:
				bool operator()(node* a,node* b)
				{
				return (a->frequency)>(b->frequency);
		        }
};
void encoding(string str,unordered_map<char,string> &encode,node*root)
{
    if(root==NULL)
     return;
     
     if(root->left==NULL&&root->right==NULL)
     {
        encode[root->ch] =str;
     }
    encoding(str+"0",encode,root->left);
    encoding(str+"1",encode,root->right);
}
void decoding(node* root, int &i, string s)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}
    ++i;
	if (s[i] =='0')
		decoding(root->left, i, s);
	else
		decoding(root->right, i, s);
}
void huffmanCoding(string t)
{
   unordered_map<char,int> map;
   priority_queue<node*,vector<node*>,Comp> pq;
   
   for(int i=0;i<t.size();++i)
   {
       if(map.count(t[i])>0)
           map[t[i]]++;
       else
           map[t[i]]=1;
   }
   unordered_map<char,int>::iterator it;
   it=map.begin();
   while(it!=map.end())
   {
       char cha=it->first;
       int f=it->second;
       node*newnode=new node(cha,f);
       pq.push(newnode);
       ++it;
   }
   int total;
   while(pq.size()!= 1)    //huffman tree is constructed here
   {
       node* node1=pq.top();
       pq.pop();
       node* node2=pq.top();
       pq.pop();
       total=(node1->frequency)+(node2->frequency);
       node*newnode=new node('\0',total);
       newnode->left=node1;
       newnode->right=node2;
       pq.push(newnode);
   }
   cout<<pq.top()->ch;
   node*root=pq.top();
   
   unordered_map<char,string>encode; //encoding
   
   encoding("",encode,root);
   unordered_map<char,string>::iterator ite=encode.begin();
   while(ite!= encode.end())
   {
       cout<<ite->first<<" - "<<ite->second<<endl;
       ite++;
   }
   cout<<"\nORIGINAL STRING :"<<t;
   cout<<"\nNUMBER OF BITS IN ORIGINAL STRING :"<<t.size()*8;
   
   string s="";
   for(int i=0;i<t.size();++i)
   {
       s+=encode[t[i]];
   }
   cout<<"\nENCODED STRING :"<<s;
   cout<<"\nNUMBER OF BITS IN ENCODED STRING :"<<s.size();
   double y=s.size();
   double z=(t.size()*8);
   double ratio=(z/y);
   cout<<"\n COMPRESSION RATIO :"<<ratio;
   cout<<"\nTHE SIZE OF THE COMPRESSED FILE IS "<<100/ratio<<"%"<<" OF THE ORIGINAL ASCII FILE";
   int i=-1;
	cout << "\nDECODED STRING : \n";
	while (i<y-1) 
	{
		decoding(root, i, s);
		
	}
}
int main()
{
    string t;
    cout<<"ENTER THE STRING :";
    getline(cin,t);
    huffmanCoding(t);
    return 0;
}


