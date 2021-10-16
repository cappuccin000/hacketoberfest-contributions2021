#include<stdio.h>
#include<conio.h> 
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
// This code implements the function of Lexical Analyser using C programming language
struct TOKEN{
    char token_name[20], attri_val[20];
}temp1,temp2;

struct SYM_TAB{
    char lex[20],token_name[20];
}ST[100];

int state,stcount,i,j;
char c, lex[20],num[20];
FILE *fp1;

void fail(){
    switch(state){
        case 0: 
            state=10; 
            break;
        case 10: 
            state=13;
            break;
        case 13:  
            state=0; 
            break;
    }
}

struct TOKEN getNextToken()
{
    while(1) 
    {
        switch(state){
            case 0:
                c=fgetc(fp1);
                if (c==EOF)
                {
                    printf("\n\nSYMBOL TABLE\n");
                    for(i=0;i<stcount;i++)
                    {
                        printf("\n%s\t%s ",ST[i].lex, ST[i].token_name); 
                    }
                    exit(0);
                }
                if(isspace(c)) 
                    state=0;
                else if(c=='<') 
                    state=1;
                else if(c=='!') 
                    state=4;
                else if(c=='=') 
                    state=6;
                else if(c=='>') 
                    state=7;
                else 
                    fail();
                break;

            case 1:
                c=fgetc(fp1);
                if(c=='=') 
                    state=2; 
                else 
                    state=3;
                break;

            case 2:
                strcpy(temp1.token_name,"relop");
                strcpy(temp1.attri_val,"LE");
                return (temp1);

            case 3:
                fseek(fp1,-1,1);
                strcpy(temp1.token_name,"relop");
                strcpy (temp1.attri_val, "LT"); 
                return(temp1); 

            case 4:
                c=fgetc(fp1);
                if(c=='=') 
                    state=5; 
                break;

            case 5:
                strcpy(temp1.token_name,"relop");
                strcpy(temp1.attri_val, "NE");
                return(temp1);

            case 6:
                strcpy(temp1.token_name,"relop"); 
                strcpy(temp1.attri_val,"EQ");
                return (temp1);

            case 7:
                c=fgetc(fp1);
                if(c=='=') 
                    state=8;
                else    
                    state=9;
                break;

            case 8:
                strcpy(temp1.token_name,"relop");
                strcpy(temp1.attri_val, "GE"); 
                return (temp1);

            case 9:
                fseek(fp1,-1,1);
                strcpy(temp1.token_name,"relop");
                strcpy(temp1.attri_val,"GT");
                return(temp1);

            case 10:
                if(isalpha(c))
                {
                    i=0;
                    lex[i]=c;
                    state=11;
                }
                else 
                    fail();
                break;

            case 11:
                c=fgetc(fp1);
                if(isalnum(c))
                {
                    i++;
                    lex[i]=c;
                    state=11;
                }
                else
                {
                    i++;
                    lex[i]='\0';
                    state=12;
                }
                break;

            case 12:
                fseek(fp1,-1,1);
                i=0;
                while(i<stcount){
                    if (strcmp(lex,ST[i].lex)==0) 
                    {
                        if(strcmp(ST[i].token_name, "Keyword")==0)
                        {
                            strcpy(temp1.token_name, ST[i].lex); 
                            strcpy(temp1.attri_val,ST[i].token_name);
                        }
                        else if(strcmp(ST[i].token_name,"id")==0)
                        {
                            strcpy(temp1.token_name,ST[i].token_name);
                            strcpy(temp1.attri_val,lex);
                        }
                        return(temp1);  
                    }
                    i++;
                }
                if(i==stcount)
                {
                    strcpy(ST[stcount].lex,lex); 
                    strcpy(ST[stcount].token_name,"id");
                    strcpy(temp1.token_name, ST[stcount].token_name); 
                    strcpy(temp1.attri_val,lex);
                    stcount++;
                    return(temp1);
                }
                break;

            case 13:
                if(isdigit(c))
                {
                    j=0;
                    num[j]=c;
                    state=14;
                    j++;
                }
                else fail();
                break;

            case 14:
                c=fgetc(fp1);
                if(isdigit(c))
                {
                    num[j]=c;
                    j++;
                    state=14;
                }
                else if(c=='.')
                {
                    num[j]=c;
                    j++;
                    state=15;
                }
                else state=17;
                break;

            case 15:
                c=fgetc(fp1);
                if(isdigit(c))
                {
                    num[j]=c;
                    j++;
                    state=16;
                }
                break;

            case 16:
                c=fgetc(fp1);
                if(isdigit(c))
                {
                    num[j]=c;
                    j++;
                    state=16;
                }
                else state=17;

            case 17:
                fseek(fp1,-1,1);
                num[j]='\0';
                strcpy(temp1.token_name,"Number");
                strcpy(temp1.attri_val,num);
                return(temp1);
          }
 
    }   
};
int main()
{
    strcpy(ST[0].lex,"int"); 
    strcpy(ST[0].token_name,"Keyword");
    strcpy(ST[1].lex,"char"); 
    strcpy(ST[1].token_name,"Keyword");
    strcpy(ST[2].lex,"if"); 
    strcpy(ST[2].token_name,"Keyword");
    strcpy(ST[3].lex,"else"); 
    strcpy(ST[3].token_name,"Keyword");

    stcount=4;
    fp1=fopen("input.txt","r");
    printf("\nTOKENS");
    while(!feof(fp1))
    {
        state=0;
        temp2=getNextToken();
        printf("\n %s\t%s ",temp2.token_name,temp2.attri_val);
    }
    fclose(fp1);
    return 0;

    
}
