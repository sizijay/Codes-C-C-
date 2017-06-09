#include<stdio.h>
#include<string.h>

void search(char *pat,char *txt)
{
	int M=strlen(pat);
	int N=strlen(txt);

	for(int i=0;i<=N-M;i++)
	{
		int j=0;
		while(j<=M)
		{
			if(txt[i+j]==pat[j])
				j++;
			/*if(j==M)
				printf("pattern found at index %d \n",i);*/
			else
				break;
		}
		if(j==M)
				printf("pattern found at index %d \n",i);
	}
}

 int main(int argc, char const *argv[])
{
	char pat[]="AABA";
	char txt[]="AABAACAADAABAAABAA";

	search(pat,txt);
	return 0;
}