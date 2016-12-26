#include<fstream>
#include"io.cpp"
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"search.cpp"
#include"article.cpp"

using namespace std;

void addquestion();
void addanswer();
void home();
void filerd();
void update();
int ansno(int);
int queno();
void sortans();
void displayQ(int );
char voter;
static char choice1='0';
static char choice2;

void addanswer()
{
	int choose,cur;
	char tans[1000];
	que Q;
	que temp;
	ifstream rd;
	ofstream add;

	for(int i=1;i<=queno();i++)	//to display all questions
	 {
		 displayQ(i);
	 }

	cout<<"\nChoose a question number.\n";
	cin>>choose;

	if(choose>queno())
	{
		cout<<"\nQuestion does not exist.\n";
		goto end;
	}

	system("cls");
	displayQ(choose);				//display chosen question
	cout<<"\nWrite your answer.\n";
	cin.getline(tans,10000,'`');
	tans[0]=' ';		//input answer
	rd.open("data.txt");
	add.open("temp2.txt",ios::trunc);

	for(int i=1;i<choose;i++)
	{
		rd.read((char*)&temp,sizeof(temp)) ;
		add.write((char*)&temp,sizeof(temp));
	}

	rd.read((char*)&temp,sizeof(temp));
	strcpy(temp.A[ansno(choose)].answer,tans);
	temp.Ans++;
	add.write((char*)&temp,sizeof(temp));

	while(1)
	{
		rd.read((char*)&temp,sizeof(temp)) ;
		if(rd.eof())
			break;
		add.write((char*)&temp,sizeof(temp));
	}

	rd.close();
	add.close();
	remove("data.txt");
	rename("temp2.txt","data.txt");
	end:;
	cout<<"done";
}



void sortans()
{
    filerd();
	int ch=(queno()-1);

	for(int j=0;j<=ch;j++)								//object of question whose answers are to b sorted
	{
		for(int i=0;i<=((Que[j].Ans)-2);i++)
		{
			for(int k=0;k<=i;k++)
			{
				if(Que[j].A[k].up<=Que[j].A[k+1].up)
				{
					ans temp;
					strcpy(temp.answer,Que[j].A[k].answer); temp.up=Que[j].A[k].up; temp.dw=Que[j].A[k].dw;
					strcpy(Que[j].A[k].answer,Que[j].A[k+1].answer); Que[j].A[k].up=Que[j].A[k+1].up; Que[j].A[k].dw=Que[j].A[k+1].dw;
					strcpy(Que[j].A[k+1].answer,temp.answer); Que[j].A[k+1].up=temp.up; Que[j].A[k+1].dw=temp.dw;
				}
			}
		}

	}

	ofstream arrange("temp.txt");
	for(int i=0;i<queno();i++)
		{
			arrange.write((char*)&Que[i],sizeof(Que[i]));	//write objects to file
		}
	arrange.close();
	remove("data.txt");
	rename("temp.txt","data.txt");
}

void displayQAns()
{   int z=1,Ansno;
    char ch='n',vote;

    while(ch=='n'||ch=='N'||ch=='p'||ch=='P'||ch=='V'||ch=='v')
    {
		system("cls");

        if(z>queno())
			{
				cout<<"\nWant to read more???\nAdd more questions....Be Curious.\n ";
				getch();
				goto enddisplay;
			}

		filerd();

		cout<<endl<<"Q."<<z<<Que[z-1].question<<endl;

		for(int i=0;i<ansno(z);i++)        	//display question of queno i
			{
				cout<<endl<<(i+1)<<". ";
				cout<<Que[z-1].A[i].answer;
				cout<<"\n\t"<<"Uvotes = ";
				cout<<Que[z-1].A[i].up;
				cout<<"\t\t"<<"Dvotes = ";
				cout<<Que[z-1].A[i].dw;
			}

		cout<<"\n\nPress 'v' to vote"<<endl;
		cout<<"\nTo view next question press \"n\" and to view previous question press \"p\" \n";
		cout<<"Or any other key to exit\n";
        ch=getche();

        if(ch=='n'||ch=='N')
			{
				z++;
			}
        else if(ch=='p'||ch=='P')
            z--;
        else if(ch=='v'||ch=='V')
		{
			cout<<"\nTo vote an answer, input answer number.\n";
			cin>>Ansno;
			system("cls");
			cout<<Que[z-1].question;
			cout<<endl<<Que[z-1].A[Ansno-1].answer;
			cout<<"\nU/D\n";
			cin>>vote;

			if(vote=='U'||vote=='u')
				Que[z-1].A[Ansno-1].up++;
			else if (vote=='d'||vote=='D')
				Que[z-1].A[Ansno-1].dw++;
			else
				cout<<"\nIncompatible Language!\n";

            cout<<"Your vote has been recorded.";
			update();
		}

        if(z==0)
            z++;
    }

	enddisplay:;
}




void editanswer(int qno,int ano)
{
	que eans,temp;
    char ans_[1000];
    ofstream add;
	ifstream edit("data.txt"),rd;

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
	rd.open("data.txt");
	add.open("temp2.txt",ios::trunc);

	for(int i=1;i<qno;i++)
	{
		rd.read((char*)&temp,sizeof(temp)) ;
		add.write((char*)&temp,sizeof(temp));

	}

	rd.read((char*)&temp,sizeof(temp));
	add.write((char*)&eans,sizeof(eans));

	while(1)
	{
		rd.read((char*)&temp,sizeof(temp)) ;
		if(rd.eof())
			break;
		add.write((char*)&temp,sizeof(temp));
	}

	rd.close();
	add.close();
	remove("data.txt");
	rename("temp2.txt","data.txt");
	end:;
	cout<<"done";
	endedit:;
}




void update()
{
	ofstream arrange("temp.txt");
	for(int i=0;i<queno();i++)
		{
			arrange.write((char*)&Que[i],sizeof(Que[i]));	//write objects to file
		}
	arrange.close();
	cout<<"done";
	remove("data.txt");
	rename("temp.txt","data.txt");
	filerd();
   	sortans();				//sort answers

}



void header()
{
	system("cls");
	cout<<"\n\t\t\tWELCOME TO PANORAMA\n\n";
}




void home()
{
	start:
	header();
	int qno, ano;
	cout<<"\n 1) Question\n";

	if(choice1=='1')
	{
		cout<<"\tA) Ask\n";
			if(choice2=='A'||choice2=='a')
			{
				addquestion();choice1='0';choice2='z';
				goto start;
			}
	}

	cout<<" 2) Answer\n";

	if (choice1=='2')
	{
		cout<<"\tA) Answer\n";
		if(choice2=='a'||choice2=='A')
		{
			addanswer();choice1='0';choice2='z';
			goto start;
		}
		cout<<"\tB) Edit previous answer\n";
		if(choice2=='B'||choice2=='b')
		{
			cout<<"Question number?\n";
			cin>>qno;
			cout<<"\nEnter answer number\n";
			cin>>ano;
			editanswer(qno,ano);  choice1='0';choice2='z';
			goto start;
		}
	}

	cout<<" 3) Browse\n";

	if(choice1=='3')
	{
		cout<<"\tA) Question and Answers\n";
		if(choice2=='a'||choice2=='A')
		{
			displayQAns(); choice1='0';choice2='z';
			goto start;
		}
		cout<<"\tB) Articles\n";
        if(choice2=='B'||choice2=='b')
		{    choice1='0';choice2='z';
			displayarticle();
			goto start;
		}
		cout<<"\tC) Search\n";
		if(choice2=='C'||choice2=='c')
		{    choice1='0';choice2='z';
			search();
			goto start;
		}
	}

	cout<<" 4) Articles\n";

	if(choice1=='4')
	{
		cout<<"\tA) Add\n";
		if(choice2=='a'||choice2=='A')
		{   choice1='0';choice2='z';
			addarticle();
			goto start;
		}

		cout<<"\tB) Edit\n";

		if(choice2=='B'||choice2=='b')
		{   choice1='0';choice2='z';
			displayarticle();
			goto start;
		}
	}

	cout<<" 5) Exit\n";

	if(choice1=='5')
	{
		cout<<"Are you sure(y/n)\n";
		if(choice2=='y'||choice2=='Y')
		{
		  	update();
			exit(0);
		}
		if(choice2=='n'||choice2=='N')
			{
				choice1='0';choice2='z';
				goto start;
			}

	}

	cout<<"\n\n What's your choice?\n";

	if(choice1!='0')
	{
		choice2=getche();
		goto start;
	}
	else
	{
		cin>>choice1;
		while(choice1<'1'||choice1>'5')
        {
            cout<<"\nInvalid Input\nEnter again\n";
            cin>>choice1;
        }
		goto start;
	}
}

int ansno(int qno)
{
	ifstream rd("data.txt");
	que Q;

	for(int cur=1;cur<=qno;cur++)
		{
			rd.read((char*)&Q,sizeof(Q));
		}

	rd.close();
	return Q.Ans;
}

int main()
	{
		filerd();
		home();
		getch();
		return 0;
	}
