#include<fstream>
#include <iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
class ans
{  public:
    char answer[1000];
    int up,dw;
    char tags[10][20];
   // editanswer();
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

}Que[5];
void addquestion();
void addanswer();
//void addarticle();
//void editarticle();
//void displayarticle();
void home();
void filerd();
void update();
int ansno(int);
int queno();
void sortans();
void displayQ(int );
char voter;
static int choice1=0;
static char choice2;



void addanswer()
{ int choose,cur;
  char tans[1000];
  que Q;
  ifstream rd;
  ofstream add;
	for(int i=1;i<=queno();i++)	//to display all questions
	{displayQ(i);
	}
	cout<<"choose a question no.\n";
	cin>>choose;
	if(choose>queno())
	{	cout<<"question does not exist";
		goto end;
	}
	system("cls");
	displayQ(choose);				//display chosen question
	cout<<"write your ans";
	cin.getline(tans,10000,'`');		//input answer
rd.open("data.pano");
for(cur=1;cur<=choose;cur++)
{ rd.read((char*)&Q,sizeof(Q));		//copy respective question in Q
}
rd.close();
strcpy(Q.A[ansno(choose)].answer,tans);
Q.Ans++;
add.open("data.pano",ios::ate);
add.seekp(((choose-1)*sizeof(Q)),ios::beg);
add.write((char*)&Q,sizeof(Q));				//write object Q in file
add.close();
//update();
end:;
}




	void displayQ(int srno)
{
		ifstream q("data.pano");	//open data file
		que q1;
		for(int i=1;i<=srno;i++)		//read data till srno
		{
         if(q.eof())
			{cout<<"Question not found.";
			goto enddisplay;
			}
			q.read((char*)&q1,sizeof(q1));		//read 1 object
		}
		q.close();
		cout<<srno<<q1.question; cout<<"\n"<<q1.Ans;		//display selected question
		enddisplay:;

}






  void addquestion()
{
	cout<<"Write your question(Press '`'(below escape) to terminate)";
	char qadd[500];				//string to temporary store question
	que addq;
	cin.getline(qadd,500,'`');		//input question
	ofstream fadd("data.pano",ios::app);
	strcpy(addq.question,qadd);
	fadd.write((char*)&addq,sizeof(addq));		//add question to file
	fadd.close();
}

void filerd()
{
     ifstream file("data.pano");
	int ch=0;
	while(!file.eof())
	{
		file.read((char*)&Que[ch],sizeof(Que[ch]));				//array que is global
		ch++;
   }  cout<<Que[0].question;
}


void sortans()
{
	int ch=(queno()-1);

	for(int j=0;j<=ch;j++)								//object of question whose answers are to b sorted
	{
		for(int i=((Que[ch].Ans)-2);i>=0;i--)
		{
			for(int k=0;k<=i;k++)
			{
				if(Que[j].A[k].up<=Que[j].A[k+1].up)
				{
					ans temp;
					temp=Que[j].A[k];
					Que[j].A[k]=Que[j].A[k+1];
					Que[j].A[k+1]=temp;
				}
			}
		}

	}
}


void displayQAns()
{     filerd();
	 //  sortans();						//sort
		a:
		int srno,Ansno;
		char vote;
		cout<<"To exit, press 'e' else press any other key.";
		char exit1;
		exit1=getch();
		if(exit1=='e')				//exit to homescreen
		  {  choice2=9;
				choice1=0;
        	   home();
         }

		for(int i=0;i<queno();i++)
		{
            cout<<"Q"<<(i+1)<<". "<<Que[i].question<<endl;    //display question of queno i

				cout<<"Ans. "<<Que[i].A[0].answer;					//display first answer

		}
		cout<<"To view a question, press respective sr number \n";
		cin>>srno;
	  	system("cls");

       cout<<"Q"<<". "<<Que[srno-1].question<<endl;
		for(int i=0;i<ansno(srno);i++)        	//display question of queno i
		{  cout<<(i+1)<<". ";
			cout<<Que[srno-1].A[i].answer;
			cout<<"\n"<<"Uvotes = ";
			cout<<Que[srno-1].A[i].up;
			cout<<"\t\t"<<"Dvotes = ";
			cout<<Que[srno-1].A[i].dw;
		}
		cout<<"Press 'V' to vote\n";
      cin>>voter;
		if(voter=='V'||voter=='v')
		{		cout<<"To vote an ans, input ans no\n";
				cin>>Ansno;
				cout<<"\nU/D\n";
				cin>>vote;
				if(vote=='U'||vote=='u')
					Que[srno-1].A[Ansno-1].up++;
				else if (vote=='d'||vote=='D')
					Que[srno-1].A[Ansno-1].dw++;
				else
					cout<<"\nIncompatible Language!\n";
            cout<<"Your vote has been recorded.";
				update();
				goto a;
		}
}



void editanswer(int qno,int ano)
{
	que eans;
   char ans_[1000];
   ofstream wans;
	ifstream edit("data.pano");
	for(int i=1;i<=qno;i++)
	{
		edit.read((char*)&eans,sizeof(eans));
		if(edit.eof())
		{
			cout<<"\nQuestion not found\n";
			goto endedit;
		}
	}
	edit.close();
	cout<<"\nUpdate your answer.(Press '`' to terminate)\n";		//input answer
	cin.getline(ans_,1000,'`');
	strcat(eans.A[ano-1].answer,"\n Edit:");
	strcat(eans.A[ano-1].answer,ans_);
   wans.open("data.pano",ios::ate);						//open file
	wans.write((char*)&eans,sizeof(eans));
	wans.close();
	endedit:;
}




void update()
{
	ofstream arrange("temp.pano");
	for(int i=0;i<queno();i++)
	{     cout<<Que[0].question;
   		arrange.write((char*)&Que[i],sizeof(Que[i]));	//write objects to file
	}
	arrange.close();
   cout<<"done";
  remove("data.pano");
rename("temp.pano","data.pano");
  filerd();
   	sortans();				//sort answers

}



void header()
{
	system("cls");
	cout<<"\n\t\t\twelcome to panorama";
	}




	void home()
{
	start:
	header();
	int qno, ano;
	cout<<"\n1) Question\n";
	if(choice1==1)
	{
		cout<<"\tA) Ask\n";
			if(choice2=='A'||choice2=='a')
			{
				addquestion();choice1=0;choice2='z';
				goto start;
			}
	}
	cout<<"2) Answer\n";
	if (choice1==2)
	{
		cout<<"\tA) Answer\n";
		if(choice2=='a'||choice2=='A')
		{
			addanswer();choice1=0;choice2='z';
			goto start;
		}
		cout<<"\tB) Edit previous answer\n";
		if(choice2=='B'||choice2=='b')
		{
			cout<<"Question number?\n";
			cin>>qno;
			cout<<"\nEnter answer number\n";
			cin>>ano;
			editanswer(qno,ano);  choice1=0;choice2='z';
			goto start;
		}
	}
	cout<<"3) Browse\n";
	if(choice1==3)
	{
		cout<<"\tA) Question and Answers\n";
		if(choice2=='a'||choice2=='A')
		{
			displayQAns(); choice1=0;choice2='z';
			goto start;
		}
		cout<<"\tB) Articles\n";
		if(choice2=='B'||choice2=='b')
		{    choice1=0;choice2='z';
			//displayarticle();
			goto start;
		}
	}
	cout<<"4) Articles\n";
	if(choice1==4)
	{
		cout<<"\tA) Add\n";
		if(choice2=='a'||choice2=='A')
		{   choice1=0;choice2='z';
			//addarticle();
			goto start;
		}
		cout<<"\tB) Edit\n";
		if(choice2=='B'||choice2=='b')
		{   choice1=0;choice2='z';
			//editarticle();
			goto start;
		}
	}
	cout<<"5) Exit\n";
	if(choice1==5)
	{
		cout<<"Are you sure(y/n)\n";
		if(choice2=='y'||choice2=='Y')
		{
		  //	update();
			exit(0);
		}
		if(choice2=='n'||choice2=='N')
		 { choice1=0;choice2='z';
       	goto start;

       }

	}
	cout<<"What's your choice?\n";
	if(choice1!=0)
	 {
		cin>>choice2;
		goto start;
	}
	else
	{
		cin>>choice1;
		goto start;

	}


}




	int ansno(int qno)
{

	ifstream rd("data.pano");
	que Q;
	for(int cur=1;cur<=qno;cur++)
	{ rd.read((char*)&Q,sizeof(Q));}
	  rd.close();

	return Q.Ans;
}




int queno()
{
	int count=0;
	ifstream rd("data.pano");
	que Q;
	while(!rd.eof())
	{


		rd.read((char*)&Q,sizeof(Q));
        count++;

   }
	rd.close();
	return count;
}

int main()
{     // displayQ(1);
    //update();
   // home();
    cout<<queno();
   // filerd();
     getch();
     return 0;
}




