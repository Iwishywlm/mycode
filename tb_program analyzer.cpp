#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	FILE *fp;
    char buf1[101][21];
    char buf2[101][21];
    char buf3[101][21];
    char change[100],temp[20];
    static int number[100],output[100];
    int len,count=0,num=0,letter=0,j=0,k=0,h=0,a=0,i=0,F=0,count2=0;
    int order[2][100];
    char *p;

	if((fp=fopen("Input.txt","r"))==NULL){   /*��ֻ���������ļ�*/ /*Input�ļ������Իس���ո��β*/
		printf("OPEN ERROR");
		exit(0);
	}
	while(fgets(buf1[h],21,fp)!=NULL){   /*�������ļ����з���һ����ά����*/
		len=strlen(buf1[h]);
		buf1[h][len-1]='\0';
		strcpy(buf3[h],buf1[h]);    /*��������ȫ������������������һ�����Ա�����*/
		p=strtok(buf1[h]," ");    /*�����кŵ���ȡ����������˳�����һ����ά����*/
		strncpy(temp,p,4);
		for(j=0;j<strlen(temp);j++){
			num=num*10+temp[j]-'0';
		}
		order[0][h]=h;
		order[1][h]=num;
		num=0;
		h++;
	}
	a=0;
	for(i=0;i<h-1;i++){    /*���кŴ�С��������*/
		for(j=i+1;j<h;j++){
			if(order[1][i]>order[1][j]){
				num=order[1][i];
				a=order[0][i];
				order[1][i]=order[1][j];
				order[0][i]=order[0][j];
				order[1][j]=num;
				order[0][j]=a;
			}
		}
	}
	for(i=0;i<h;i++){    /*��������TB�������鰴�кŴ�С˳�����е���һ�µ�����buf2��*/
		a=order[0][i];
		strcpy(buf2[i],buf3[a]);
	}
	a=0;
	
	for(i=0;i<h;i++){    /*��ȥbuf2��ÿ�е��кź�ȫ���ո�*/
		p=strtok(buf2[i]," ");
		p=strtok(NULL," ");
		strcpy(temp,p);
		p=strtok(NULL," ");
		while(p!=NULL){
			strcat(temp,p);
			p=strtok(NULL," ");
			}
		strcpy(buf3[i],temp);
	}
	
	for(i=0;i<h;i++){    /*��������*/
		if(count>4000){    /*�������������ѭ�������-1*/
			F=-1;
			break;
		}
		if(buf3[i][0]=='E'&&buf3[i][1]=='N'&&buf3[i][2]=='D'){    /*����END����������*/
			count++;
			break;
		}
		else if(buf3[i][0]=='I'&&buf3[i][1]=='F'){
			if(letter==0){    /*ȷ������������漰�ı�����Ӧǰ����ֹ����ĸ������������³��ֵı�����ֵΪ0�����뱣�������������*/
				change[0]=buf3[i][2];
				number[0]=0;
				letter++;
				k=0;
			}
			else{
				for(j=0;j<letter;j++){
					if(change[j]==buf3[i][2]){
						break;
					}
				}
				k=j;
				if(j==letter){
					change[j]=buf3[i][2];
					letter++;
				}
			}
			j=4;
			a=0;
			while(buf3[i][j]>='0'&&buf3[i][j]<='9'){    /*����������λ��*/
				a++;
				j++;
			}
			num=0;    /*����������ֵ*/
			for(j=4;j<a+4;j++){
				num=num*10+buf3[i][j]-'0';
			}
			if(buf3[i][j]!='G'){    /*��Ϊ�Ƿ���������-1*/
			    F=-1;
			    break;
			}
			a=0;
			j+=2;
			if(num==number[k]){    /*������������ֵ��ȣ�����ת��GO����д���к�*/
				num=0;
				while(buf3[i][j]>='0'&&buf3[i][j]<='9'){
					num=num*10+buf3[i][j]-'0';
					j++;
				}
			    if(buf3[i][j]!='\0'){
			    	F=-1;
			    	break;
				}
			    for(j=0;j<h;j++){
				if(order[1][j]==num){
					i=j-1;
					break;
				}
		    	}
		    	count++;
		    	continue;
			}
			else{    /*����������кŷ�������*/
				count++;
			}			
		}
		else if(buf3[i][0]=='G'&&buf3[i][1]=='O'){
			num=0;
			j=2;
			while(buf3[i][j]>='0'&&buf3[i][j]<='9'){
				num=num*10+buf3[i][j]-'0';
				j++;
			}
			if(buf3[i][j]!='\0'){    /*��Ϊ�Ƿ���������-1*/
			   	F=-1;
			   	break;
			}
			for(j=0;j<h;j++){    /*�ڱ����кŵ��������ҵ���Ӧ�в���ת*/
				if(order[1][j]==num){
					i=j-1;
					break;
				}
			}
			count++;
			continue;
		}
		else{
			if(letter==0){
				change[0]=buf3[i][0];
				letter++;
				k=0;
			}
			else{
				for(j=0;j<letter;j++){
					if(change[j]==buf3[i][0]){
						break;
					}
				}
				k=j;
				if(j==letter){
					change[j]=buf3[i][0];
					letter++;
				}
			}
			
			if(buf3[i][1]=='?'){
			    output[count2]=number[k];
			    count2++;
				count++;
			}
			else if(buf3[i][1]=='!'){
				printf("Please input %c = ",change[k]);
				scanf("%d",&number[k]);
				count++;
			}
			else if(buf3[i][1]=='+'){
			    num=0;
			    j=2;
			    while(buf3[i][j]>='0'&&buf3[i][j]<='9'){
					num=num*10+buf3[i][j]-'0';
					j++;
				}
			    if(buf3[i][j]!='\0'){    /*��Ϊ�Ƿ���������-1*/
			    	F=-1;
			    	break;
				}
				number[k]+=num;
				count++;
			}
			else if(buf3[i][1]=='-'){
			    num=0;
			    j=2;
			    while(buf3[i][j]>='0'&&buf3[i][j]<='9'){
					num=num*10+buf3[i][j]-'0';
					j++;
				}
			    if(buf3[i][j]!='\0'){    /*��Ϊ�Ƿ���������-1*/
			    	F=-1;
			    	break;
				}
				number[k]-=num;
				count++;
			}
			else{    /*�Ƿ���䣬���-1*/
				F=-1;
				break;
			} 
			}
		}
	if((fp=fopen("Output.txt","w"))==NULL){
		printf("SAVE ERROR");
		exit(0);
	}
	if(F==-1){    /*���зǷ����������-1*/
		fprintf(fp,"%d\n",F);
	}
	else{    /*�������������򱣴�TB����������*/ 
		for(i=0;i<count2;i++)
		    fprintf(fp,"%d\n",output[i]);
	}
	if(fclose(fp)){
		printf("CLOSE ERROR");
		exit(0);
	}	
	return 0;
}
