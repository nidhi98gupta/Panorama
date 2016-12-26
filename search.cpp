int strsearch(char*,int);

que obj;
int length=0,strln=0;
char word[20];
bool chk=false;

void search()
{
		cout<<"\nEnter the word you want to search.\n";
		cin>>word;
		length=strlen(word);

		ifstream search("data.txt");

		 while(1)
		 {
			if(search.eof())
			{
			    if(chk==false)
                {
                        cout<<"\nWord not found.\n";
                        goto endsrch;
                }
                else
                    goto endsrch;
			}

            search.read((char*)&obj,sizeof(obj));

            if(search.eof())
			{
			    if(chk==false)
                {
                        cout<<"\nWord not found.\n";
                        goto endsrch;
                }
                else
                    goto endsrch;
			}

				strln=strlen(obj.question);
				if(strsearch(obj.question,strln))				//to check question
				{
                    chk=true;
					cout<<obj.question;
					for(int i=0;i<obj.Ans;i++)        	//display answer of searched question
					{	cout<<endl<<(i+1)<<". ";
						cout<<obj.A[i].answer;
						cout<<"\n"<<"Uvotes = ";
						cout<<obj.A[i].up;
						cout<<"\t\t"<<"Dvotes = ";
						cout<<obj.A[i].dw<<endl;
					}
				}
				else
				{
				    chk=true;
				    for(int i=0;i<obj.Ans;i++)
			     	{	int len=strlen(obj.A[i].answer);
                    if(strsearch(obj.A[i].answer,len))			//search answers
					{		cout<<obj.question;
					 for(int i=0;i<obj.Ans;i++)        	//display answer of searched question
					   {	cout<<endl<<(i+1)<<". ";
						cout<<obj.A[i].answer;
						cout<<"\n"<<"Uvotes = ";
						cout<<obj.A[i].up;
						cout<<"\t\t"<<"Dvotes = ";
						cout<<obj.A[i].dw<<endl;
				    	}
					}

				   }
				}
				cout<<"\n";
	     }
endsrch:;
getch();
}

int strsearch(char str[],int strln)
{
    int index=0;
	char temp[20];
	for( int i=0;i<(strln-length+1);i++)
	{   index=0;
		 for(int j=i;j<(length+i);j++)
			{ temp[index]=str[j];
			  index++;
			  temp[length]='\0';
			}
		if(strcmp(word,temp)==0)
				return 1;
	}
		return 0;
}


