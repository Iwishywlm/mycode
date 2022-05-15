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

	if((fp=fopen("Input.txt","r"))==NULL){   /*以只读打开输入文件*/ /*Input文件必须以回车或空格结尾*/
		printf("OPEN ERROR");
		exit(0);
	}
	while(fgets(buf1[h],21,fp)!=NULL){   /*将输入文件逐行放入一个二维数组*/
		len=strlen(buf1[h]);
		buf1[h][len-1]='\0';
		strcpy(buf3[h],buf1[h]);    /*将导入完全的数组整个拷贝到另一数组以备后用*/
		p=strtok(buf1[h]," ");    /*将各行号单独取出并按输入顺序放入一个二维数组*/
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
	for(i=0;i<h-1;i++){    /*将行号从小到大排序*/
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
	for(i=0;i<h;i++){    /*将含完整TB语句的数组按行号大小顺序排列到另一新的数组buf2中*/
		a=order[0][i];
		strcpy(buf2[i],buf3[a]);
	}
	a=0;
	
	for(i=0;i<h;i++){    /*除去buf2中每行的行号和全部空格*/
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
	
	for(i=0;i<h;i++){    /*分析程序*/
		if(count>4000){    /*如果程序陷入死循环则输出-1*/
			F=-1;
			break;
		}
		if(buf3[i][0]=='E'&&buf3[i][1]=='N'&&buf3[i][2]=='D'){    /*遇到END语句结束程序*/
			count++;
			break;
		}
		else if(buf3[i][0]=='I'&&buf3[i][1]=='F'){
			if(letter==0){    /*确认条件语句中涉及的变量对应前面出现过的哪个变量，如是新出现的变量则赋值为0并放入保存变量的数组中*/
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
			while(buf3[i][j]>='0'&&buf3[i][j]<='9'){    /*计算整数的位数*/
				a++;
				j++;
			}
			num=0;    /*计算整数的值*/
			for(j=4;j<a+4;j++){
				num=num*10+buf3[i][j]-'0';
			}
			if(buf3[i][j]!='G'){    /*若为非法语句则输出-1*/
			    F=-1;
			    break;
			}
			a=0;
			j+=2;
			if(num==number[k]){    /*如果整数与变量值相等，则跳转到GO后所写的行号*/
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
			else{    /*否则继续按行号分析程序*/
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
			if(buf3[i][j]!='\0'){    /*若为非法语句则输出-1*/
			   	F=-1;
			   	break;
			}
			for(j=0;j<h;j++){    /*在保存行号的数组中找到相应行并跳转*/
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
			    if(buf3[i][j]!='\0'){    /*若为非法语句则输出-1*/
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
			    if(buf3[i][j]!='\0'){    /*若为非法语句则输出-1*/
			    	F=-1;
			    	break;
				}
				number[k]-=num;
				count++;
			}
			else{    /*非法语句，输出-1*/
				F=-1;
				break;
			} 
			}
		}
	if((fp=fopen("Output.txt","w"))==NULL){
		printf("SAVE ERROR");
		exit(0);
	}
	if(F==-1){    /*若有非法输入则输出-1*/
		fprintf(fp,"%d\n",F);
	}
	else{    /*程序正常结束则保存TB程序输出结果*/ 
		for(i=0;i<count2;i++)
		    fprintf(fp,"%d\n",output[i]);
	}
	if(fclose(fp)){
		printf("CLOSE ERROR");
		exit(0);
	}	
	return 0;
}
