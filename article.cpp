#include<fstream>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

class article
{
	public:
	char content[1000];

}art;

using namespace std;

void editarticle(int);

void addarticle()
{
	char art1[1000];
	ofstream afile("artdata.txt",ios::app);
	cout<<"\nWrite your article\n";
	cin.getline(art1,1000,'`');
	strcpy(art.content,art1);
	afile.write((char*)&art,sizeof(art));
	afile.close();
	cout<<"\nThank You!\n";
	getch();
}

void displayarticle()
{
	int z=1;
    char ch='n';
    bool chkeof=false;
    ifstream disp;
    article temp;

    while(ch=='n'||ch=='N'||ch=='p'||ch=='P'||ch=='e'||ch=='E')
		{
			system("cls");
			disp.open("artdata.txt");
			disp.seekg(0,ios::beg);

			for(int i=1;i<=z;i++)
				{
					if(disp.eof())
						{
							chkeof=true;
						}

					disp.read((char*)&temp,sizeof(temp));
				}

			disp.close();
			if(chkeof==true)
				{
					cout<<"\nArticles end here. \n";
					getch();
					goto artend;
				}

			cout<<"\n"<<temp.content<<"\n\n";
			cout<<"\nTo view next article press \"n\" and to view previous article press \"p\" \n";
			cout<<"\nTo edit article press \"E\"\n";
			ch=getche();

			if(ch=='n'||ch=='N')
				z++;
			else if(ch=='p'||ch=='P')
				z--;
			else if(ch=='e'||ch=='E')
				editarticle(z);
			if(z==0)
				z++;
		}
    artend:;
}

void editarticle(int z)
{
    article art1,temp;
    char str[1000];
    ofstream add;
    cout<<"\nEdit the article.\n";
    cin.getline(str,1000,'`');
    ifstream edit("artdata.txt"),rd;

	for(int i=1;i<=z;i++)
		{
			edit.read((char*)&art1,sizeof(art1));
			if(edit.eof())
				{
					cout<<"\nArticle not found.\n";
					goto endedit;
				}
		}

	edit.close();
	strcat(art1.content,"\nEdit\n");
	strcat(art1.content,str);
	cout<<"\Your edited article is";
	cout<<"\n"<<art1.content<<endl;

	rd.open("artdata.txt");
	add.open("temp2.txt",ios::trunc);

	for(int i=1;i<z;i++)
		{
			rd.read((char*)&temp,sizeof(temp)) ;
			add.write((char*)&temp,sizeof(temp));
		}

	rd.read((char*)&temp,sizeof(temp));
	add.write((char*)&art1,sizeof(art1));
	while(1)
	{
		rd.read((char*)&temp,sizeof(temp)) ;
		if(rd.eof())
			break;

		add.write((char*)&temp,sizeof(temp));
	}

	rd.close();
	add.close();
	remove("artdata.txt");
	rename("temp2.txt","artdata.txt");
	end:;
	cout<<"\nDone";
	endedit:;
}
