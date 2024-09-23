//Vietnamese Dictionary
#include <iostream>
#include <string>
#include<cctype>
#include<fstream>
#define M 101
using namespace std;

typedef struct Word {
    string word;
    string type;
    string mean;
}Word;


struct DictNode {
    Word word;
    DictNode*next;
};

void init (DictNode * heads[])
{
    for (int i=0;i<M;i++){
        heads [i]=NULL;
    }
}

int hashF(string en){
    int h=0;
      for (int i=0;i<en.length();i++ )
        h+= (int ) tolower(en[i])*(i+1);
    
    
    return h%M;
}

int hashFunc(Word w){
    
    return hashF(w.word);
}

DictNode *createWord(Word w){
    DictNode *word= new DictNode;
    word -> word = w;
    word ->next =NULL;
}


void addWord(DictNode *heads[], Word w){
    int h=hashFunc(w);
    DictNode *r =heads[h];
    DictNode *p=createWord(w);
      if (r == NULL)
        heads [h]=p;
      else 
      {
          int t = hashFunc(r->word);
          while (r->next !=NULL){
              if (t==h)
              break; 
            else
              r = r-> next;
          }
        if (t!=h)  
          r ->next =p;
      }     
}

void updateWord(DictNode *heads[], Word w){
    int h =hashFunc(w);
    DictNode* r=heads[h];
       if (r!=NULL){
            int t = hashFunc(r->word);
          do{
              if (t==h){
                   cout << "==UPDATED==\n";
                   r->word =w;
                    break;
              }
               
            
              r = r-> next;
          
       }while (r!=NULL);
       }
}

void deleteWord(DictNode*heads[],string en){
    int h=hashF(en);
    DictNode* r=heads[h];
    DictNode*prev=NULL;
      while (r !=NULL){
          if (r ->word.word.compare(en)==0){
              if (prev == NULL)
                  heads [h] =r ->next;

              else 
                  prev ->next =r ->next;
              
              
              r  ->next =NULL;
              delete (r);
              break;
              
          }
          prev =r;
          r =r->next;
      }
}



void search(DictNode*heads[], string en)
{
    int h =hashF(en);
    DictNode*r=heads[h];
      while (r!=NULL)
      {
          int h1=hashFunc(r->word);
          if (h ==h1)
          {
              cout <<r->word.word << ":(" << r->word.type<< ")\n"<< r->word.mean<< endl;
              break;
          }
          r=r->next;
      }
}

void readDict(DictNode*heads[])
{
   ifstream f;
   f.open("word.txt", ios::in);
      while (!f.eof()){
          Word w;
            getline(f,w.word);
            getline(f,w.type);
            getline(f,w.mean);
              addWord(heads,w);
      }
   
   
   f.close();
}



void display (DictNode *heads[])
{
    for (int i=0;i<M;i++)
      if (heads[i]!= NULL)
      {
         
            DictNode *p=heads[i];
            while (p != NULL)
            {
          cout << p->word.word<< ": ("<<p->word.type<< "): "<< p->word.mean<< endl;
                  p = p->next;
            }
      }
}

int main ()
{
    char choice;
    Word w;
    string en;
    int num;
    DictNode*dicts[M];
        init(dicts);
        readDict(dicts);    
   cout << "====TU DIEN ANH VIET====\n\n";
      
           
    do {
        cout << "1.Search."<< endl ;
        cout << "2.Add Word."<< endl;
        cout << "3.Update Word."<< endl;
        cout << "4.Delete Word."<<endl;
        cout << "5.Show all the words in the dictionary."<< endl;
        cout << "6.Exit.\n\n" ;
        cout << "Please choose a number: ";
        cin >> num;
           switch (num)
           {
           case 1:
              { cout << "Enter the word you want to search: ";
               cin>> en;
               search(dicts,en);
               break;
               }
           case 2:
               {
                  
                   cout << "Enter the word you want to add: ";
                     cin >> w.word;
                       cout << endl;
                   cout << "Enter the part of speech: ";
                     cin >> w.type; 
                       cout << endl;
                   cout << "Enter the meaning of the word: ";
                     cin >> w.mean;    
                        cout << endl;
                       addWord(dicts,w);
                       
                   cout << "Do you want to see all the dictionary after you adding the word (y/n): ";  
                      cin >> choice;
                         if (choice == 'y'){ display(dicts);}
                         else {cout << "Exit\n" ;}
                         break;
               }
           case 3:
               {
                   cout << "Enter the word you want to update: ";
                    cin >> w.word;
                     cout<< endl;
                   cout << "Enter the part of speech you want to update: ";
                    cin >> w.type;
                     cout<< endl;
                   cout << "Enter the meaning of word you want to update: ";
                    cin >> w.mean;
                     cout<< endl;     
                    updateWord(dicts,w);
                   cout << "Do you want to see all the dictionary after you updating the word (y/n): ";  
                      cin >> choice;
                         if (choice == 'y'){ display(dicts);}
                         else {cout << "Exit\n" ;}
                         break; 
               }
           case 4:
               {
                   cout << "Enter the word you want to delete: ";
                     cin >> w.word;
                        deleteWord(dicts,w.word);
                       cout << endl<< "===DELETED==="<< endl;
                    cout << "Do you want to see all the dictionary after you deleting the word (y/n): ";  
                      cin >> choice;
                         if (choice == 'y'){ display(dicts);}
                         else {cout << "Exit\n" ;}
                         break; 
               }
           case 5:
              display(dicts);
              break;
           case 6:
              cout << "Exit!\n";
               break; 
           default:
              cout << "\n\nInvalid number, please try again:\n"<< endl;
              
               break;
           }

    }while(num!=6);         
        

           
return 0;
}
