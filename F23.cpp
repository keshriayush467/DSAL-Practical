#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Student 
{
    typedef struct stud
    {
        char name[100];
        char div[10];
        char address[100];
        int roll ;

    }stud;
    stud rec;
    public:
    
    void create()
    {
        char ans;

        fstream fout;
        fout.open("stud.txt", ios::out | ios::binary);
        do
        {
        cout<<"\nEnter the roll no ";
        cin>>rec.roll;
        cout<<"\nEnter the name ";
        cin>>rec.name;
        cout<<"\nEnter the division ";
        cin>>rec.div;
        cout<<"\nEnter the address ";
        cin>>rec.address;
        
        fout.write((char*)&rec, sizeof(stud));
        cout<<"\nDo u want to continue ";
        cin>>ans;
        }while(ans=='y' || ans=='Y');
        fout.close();
    }

    void display()
    {
        fstream fin;
        fin.open("stud.txt",ios::in | ios::binary);
        fin.seekg(0,ios::beg);

        cout<<"\nContents of the file are ";
        cout<<"\nRoll No \t Name \t Division \t Address ";

        while(fin.read((char*)&rec, sizeof(stud)))
        {
            cout<<"\n"<<rec.roll <<"\t" <<rec.name <<"\t" <<rec.div <<"\t" <<rec.address ; 
        }
        fin.close();
    }

    int search()
    {
        int r, i=0;
        fstream fout;
        fout.open("stud.txt",ios::in | ios::binary);
        fout.seekg(0,ios::beg);
        cout<<"\nEnter the roll no to be searched ";
        cin>>r;
        while(fout.read((char*)&rec,sizeof(stud)))
        {
            if(r==rec.roll)
            {
                cout<<"\nRecord Found ";
                cout<<"\n"<<rec.roll <<"\t" <<rec.name <<"\t" <<rec.div <<"\t" <<rec.address ; 
                return i;
            }
            i++;
        }
        fout.close();
        return 0;
    }

    void deletefunc()
    {
        int pos;
        pos=search();
        fstream f;
        f.open("stud.txt",ios::in | ios::out | ios::binary);
        f.seekg(0,ios::beg);
        if(pos==0)
        {
            cout<<"\nRecord not exist ";
        }
        int offset = pos *sizeof(stud);
        f.seekp(offset, ios::beg);
        rec.roll=-1;
        strcpy(rec.name, "NULL");
        strcpy(rec.div, "NULL");
        strcpy(rec.address, "NULL");
        f.write((char*)&rec,sizeof(stud));
        f.seekg(0);
        f.close();
        cout<<"\nRecord Deleted ";

    }
};

int main()
{
    Student S;
    int ch;
    int key;
    char ans;
    do
    {
        cout<<"\n1.Create ";
        cout<<"\n2.Display ";
        cout<<"\n3.Search ";
        cout<<"\n4.Delete ";
        cout<<"\n5. Exit ";
        cout<<"\nEnter ur choice ";
        cin>>ch;

        switch(ch)
        {
            case 1: S.create();
                    break;

            case 2: S.display();
                    break;

            case 3: S.search();
                    break;

            case 4: S.deletefunc();
                    break;

            case 5: cout<<"\nExiting System ";

        }
        cout<<"\nDo u want to continue ";
        cin>>ans;
    } while (ans=='y'|| ans=='Y');
    return 0;
    
}
