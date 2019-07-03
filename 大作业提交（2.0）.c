#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#define trans(a) ((a)<='Z'&&(a)>='A')?(a)+'z'-'Z':(a) 
typedef struct node
{
	char r[50];
	struct node *next;
}lit;
int hash(char e[])
{
	unsigned int n,i=0;
	for(i=0,n=0;e[i]!='\0'&&e[i]!='\r'&&e[i]!='\n';i++)
	{
		n=e[i]+n*131; 
	}
	return n%9000005;
}
typedef struct node1
{
	int num;
	char s[50];
	int po[2000];
	struct node1 *n;
}dit;
int Comp(const void*p1,const void*p2)
{
dit *c=(dit*)p1;
dit *d=(dit*)p2;
if(c->num!=d->num) return d->num - c->num;
else 
return strcmp(c->s,d->s);
}
dit word[25000],t,*origin1[9000005]={NULL},temp,*p1=NULL,*q1=NULL;
lit *p=NULL,*origin[9000005]={NULL},*q=NULL;
int po=0;
char te[9000000]; 
int main()
{
	int k=0,i,j,temp1,num=0,fla=0,k1,point=0,fp=0,len,fp1=0;
	char c,line[50];
	FILE *fp2;
	fp=open("dictionary.txt",O_RDONLY);
	read(fp,te,6000000);
	len=strlen(te);
	i=0;
	while(i<len)
	{
		k=0;
		if(!(te[i]>='a'&&te[i]<='z'))
		{
			i++;
			continue;
		}
		while(te[i]>='a'&&te[i]<='z')
		{
			line[k++]=te[i++];
		}
		i++;
		line[k]='\0';
		p=origin[hash(line)];
		q=p;
		while(p!=NULL)
		{
			q=p;
			p=p->next;
		}
		if(q!=NULL)
		{
			p=(lit*)malloc(sizeof(lit));
			q->next=p;
		}
		else
		{
			origin[hash(line)]=(lit*)malloc(sizeof(lit));
			p=origin[hash(line)];
		}
		strcpy(p->r,line);
		p->next=NULL;
	}
	k=0;
	fp1=open("article.txt",O_RDONLY);
	read(fp1,te,8000000);
	len=strlen(te);
	i=0;//开始判断 
	while(i<len)
	{ 
			c=trans(te[i]);
			if(c>'z'||c<'a')
			{
				po++;
				i++;
				continue;
			}
			k1=0;
			while(c<='z'&&c>='a')
			{
				po++;
				t.s[k1++]=c;
				if(++i<len)
				{
					c=trans(te[i]);
				}
				else
				{
					point=1;
					break;
				}
			}
			i++;
			t.s[k1]='\0';
			po++;
			p=origin[hash(t.s)];
			fla=1;
			while(p!=NULL)
			{
				if(strcmp(t.s,p->r)==0)
				{
					fla=0;
					break;
				}
				p=p->next; 
			}
			if(fla==1)//判断不合法单词 
			{
				t.num=1;
				t.po[0]=po-1-k1;
				p1=origin1[hash(t.s)];
				q1=origin1[hash(t.s)];
				while(p1!=NULL)
				{
					if(strcmp(p1->s,t.s)==0)
					{
						break;
					}
					q1=p1;
					p1=p1->n;
				}
				if(p1==NULL)
				{
					word[k]=t;
					if(q1==NULL)
					{
						origin1[hash(t.s)]=&word[k++];
						q1=origin1[hash(t.s)];
					}
					else
					{
						q1->n=&word[k++];
						q1=q1->n;
					}
					q1->n=NULL;
				}
				else 
				{
					p1->num++;
					p1->po[p1->num-1]=t.po[0];
				}
			}
			if(point==1)
			break;
	}
	//开始最后的排序
	qsort(word,k,sizeof(word[0]),Comp);
 	fp2=fopen("misspelling.txt","w");	
	for(i=0;i<k;i++)
	{
		fprintf(fp2,"%s %d",word[i].s,word[i].num);
		for(j=0;j<word[i].num-1;j++)
		fprintf(fp2," %d",word[i].po[j]);
		fprintf(fp2," %d",word[i].po[j]);
		fprintf(fp2,"\n");
	}
	fclose(fp2);
	return 0;
} 
