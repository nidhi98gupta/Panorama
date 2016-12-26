#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

class ans
{
	public:
    char answer[1000];
    int up,dw;

    ans()     //constructor
    {
      up=0;dw=0;
    }
};

class que
{
	public:
	int Ans;
	char question[500];
	ans A[10];			//array of objects of class answer

}Que[1000];

void filerd()
{
    ifstream file("data.txt");
    int ch=0;
    if(!file)
    goto end;

	while(!file.eof())
		{
			file.read((char*)&Que[ch],sizeof(Que[ch]));				//array que is global
			ch++;
		}

   end:;
}


void displayQ(int srno)
{
	ifstream q("data.txt");	//open data file
	que q1;

	for(int i=1;i<=srno;i++)		//read data till srno
		{
			if(q.eof())
				{
					cout<<"\nQuestion not found.\n";
					goto enddisplay;
				}

			q.read((char*)&q1,sizeof(q1));		//read 1 object
		}

	q.close();
	cout<<srno<<q1.question; cout<<"\n";		//display selected question
	enddisplay:;
}

void addquestion()
{
    char q[500];
	cout<<"\nEnter your question. (Enter \" ` \" to terminate)\n ";
	cin.getline(q,500,'`');
	q[0]=' ';
	strcpy(Que[4].question,q);
	ofstream f("data.txt", ios::app);
	f.write((char*)&Que[4],sizeof(Que[4]));
}

int queno()
{
	int count=0;
	ifstream rd("data.txt");
	que Q;

	while(!rd.eof())
		{
			rd.read((char*)&Q,sizeof(Q));
			count++;
		}

	rd.close();
	return (count-1);
}
