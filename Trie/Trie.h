// author : ShivamBhalodia
#ifndef TRIE_H  //if Trie.h hasn't been included yet
#define TRIE_H  //#define it so the compiler knows it has been included and can prevent including it twice

#include<unordered_map>
#include<vector>
using namespace std;

struct node
{
    //True if word ends at current node.
    bool isEndOfWord;
  
    //Number of words which have the prefix till current node.
    int totalPrefix;
  
    //Child nodes
    unordered_map<char,node*>childNode;
};

//This class represents a generic trie data structure
class Trie
{
	public:
		
      	    //Constructor to create an empty trie.
    	    Trie();
      
	    //Constructor to create a trie with some words.
	    Trie(vector<string>s);
	    
	    //Create new node
	    node* newNode();
	    
	    //Used to insert a word in the trie.
	    void insert(string s);
	    
	    //Delete word from the trie
	    void remove(string s);
	      
	    //Total words in the trie.
	    int wordsInTrie();
	      
	    //List all words in the trie
	    vector<string>displayTrie();
	      
	    //Word is present or not in trie.
	    bool checkWord(string s);
	    
	    //Check whether the root is empty
	    bool isEmpty(node *temp);
	      
	    //Number of words in the trie with a given prefix.
	    int totalPrefixWords(string prefix,int check);
      
  	private:
  		
	    node *root;
	    int totalWords;
	      
	    void displayTrieDone(node *temp,string prefix,vector<string>&trieToList);
	    node* removeDone(node *root,string s,int depth);
};

Trie::Trie()
{
	root=newNode();
  	totalWords=0;
}

Trie::Trie(vector<string>s)
{
	root=newNode();
  	totalWords=0;
  	for(string s1:s)
  	{
    		insert(s1);
  	}
}

node* Trie::newNode() 
{ 
  	node *temp=new node; 
  	temp->isEndOfWord=false; 
  	temp->totalPrefix=0;
  	return temp; 
} 

void Trie::insert(string s)
{
    node *temp=root;
    for(int i=0;i<s.length();i++)
    {
      	temp->totalPrefix++;
      	auto it=temp->childNode.find(s[i]);
      	if(it==temp->childNode.end())
      	{
          	temp->childNode[s[i]]=newNode();
      	}
      	temp=temp->childNode[s[i]];
    }
  
    temp->isEndOfWord=true;
    temp->totalPrefix++;
    totalWords++;
}

void Trie::remove(string s)
{
    if(checkWord(s))
    {
    	totalWords--;
    	root=removeDone(root,s,0);
    }	
}

node* Trie::removeDone(node *temp,string s,int depth=0)
{
    if(temp==NULL)
	return NULL;

    temp->totalPrefix--;
    
    if(depth==s.size()) 
    { 
        if(temp->isEndOfWord) 
            temp->isEndOfWord=false; 
  
        if(isEmpty(temp)) 
    	{ 
            //delete(temp); 
            //temp=NULL; 
        } 
        return temp; 
    }
    
    temp->childNode[s[depth]]=removeDone(temp->childNode[s[depth]],s,depth+1); ;
  
    if(isEmpty(temp) && temp->isEndOfWord==false) 
    { 
        //delete(temp); 
        //temp=NULL; 
    } 
    return temp;
}
                
int Trie::wordsInTrie()
{
  	return totalWords;
}

vector<string>Trie::displayTrie()
{
    vector<string>trieToList;
    displayTrieDone(root,"",trieToList);
    return trieToList;
}

void Trie::displayTrieDone(node *temp,string prefix,vector<string>&trieToList)
{
    if(temp->isEndOfWord)
    {
        trieToList.push_back(prefix);
    }
    for(auto p:temp->childNode)
    {
        prefix.push_back(p.first);
        displayTrieDone(p.second,prefix,trieToList);
        prefix.pop_back();
    }
}
      
bool Trie::checkWord(string s)
{
    int c=totalPrefixWords(s,0);
    if(c>0)
        return true;
    else 
        return false;
}

bool Trie::isEmpty(node *temp) 
{ 
    if(temp->childNode.size()==0)
    	return true; 
} 

int Trie::totalPrefixWords(string prefix,int check=1)
{
    if(root==NULL)
        return 0;
    node *temp=root;
    for(int i=0;i<prefix.length();i++)
    { 
        auto it=temp->childNode.find(prefix[i]);
        if(it==temp->childNode.end())
            return 0;
        else
            temp=temp->childNode[prefix[i]];
    }

    if(check || temp->isEndOfWord)
      	return temp->totalPrefix;
    else
      	return 0;
}
      
#endif // TRIE
