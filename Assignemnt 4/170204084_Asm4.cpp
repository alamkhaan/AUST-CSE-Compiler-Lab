#include<stdio.h>
#include<string.h>
char str[10000][10000];
char a[10000],b[10000];
int isSep(char c)
{
    if(c==';' || c==',' || c=='\'')
        return 1;
    return 0;
}
int isOp(char c)
{
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='>' || c=='<' || c=='!' || c=='=')
        return 1;
    return 0;
}
int isDigit(char c)
{
    if(c>='0' && c<='9')
        return 1;
    return 0;
}
int isPar(char c)
{
    if(c==')' || c=='(')
        return 1;
    return 0;
}

int isBrc(char c)
{
    if(c=='}' || c=='{')
        return 1;
    return 0;
}

int isSepa(char* c)
{
    if(strlen(c)==1 && isSep(c[0]))
        return 1;
    return 0;
}


int isKey(char* c)
{
    printf("got = %s len %d\n",c,strlen(c));
    if(strlen(c)==3 && c[0]=='i' && c[1]=='n' && c[2]=='t')
        return 1;
    else if(strlen(c)==5 && c[0]=='f' && c[1]=='l' && c[2]=='o' && c[3]=='a' && c[4]=='t' )
        return 1;
    //else if(strlen(c)==6 && c[0]=='d' && c[1]=='o' && c[2]=='u' && c[3]=='b' && c[4]=='l' || c[5]=='e')
       //return 1;
    else if(strlen(c)==4 && c[0]=='c' && c[1]=='h' && c[2]=='a' && c[3]=='r')
        return 1;
    else if(strlen(c)==4 && c[0]=='e' && c[1]=='l' && c[2]=='s' && c[3]=='e')
        return 1;
    else if(strlen(c)==2 && c[0]=='i' && c[1]=='f')
        return 1;
    else if(strlen(c)==6 && c[0]=='r' && c[1]=='e' && c[2]=='t' && c[3]=='u' && c[4]=='r' || c[5]=='n')
       return 1;
    return 0;
}

int isOper(char* c)
{
    if(strlen(c)>2)
        return 0;
    if(strlen(c)==1)
    {
        if(isOp(c[0]))
            return 1;
        return 0;
    }
    if(isOp(c[0]) && c[1]=='=')
        return 1;
    return 0;
}

int isParen(char* c)
{
    if(strlen(c)==1 && isPar(c[0]))
        return 1;
    return 0;
}
int isBrace(char* c)
{
    if(strlen(c)==1 && isBrc(c[0]))
        return 1;
    return 0;
}

int isNum(char *lex)
{
    int i, l, s;
    i=0;
    if(isDigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    l=strlen(lex);
    if(s==1)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))  s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isDigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))  s=3;
            else
            {
                s=0;
                break;
            }
        }
    if(s==3) s=1;
    return s;
}

int isId(char* c)
{
    int i=0;
    int x = 0;
    for(i=0; i<strlen(c); i++)
    {
        if((c[i]>='a' && c[i]<='z') || (c[i]>='A' && c[i]<='Z') || c[i]=='_')
        {

            x = 1;
            // printf("x = %d\n",x);
            continue;
        }
        else if(isDigit(c[i])==1)
        {
            if(x==0)
                return 0;
        }
        else return 0;
    }
    return 1;
}

int main()
{
    int i,n,t,k,j,x=0,y=0,m;
    FILE *fp = fopen("input.txt","r");
    FILE *fp2 = fopen("intermediate ouput.txt","w");
    FILE *fp3 = fopen("error.txt","w");
    i = 1;
    // input and comment remove
    int c1 = 0, c2  = 0;
    while(fgets(str[i],500,fp))
    {
        char q;
        int sz = strlen(str[i]);
        c1 = 0;
        for(j=0; j<sz; j++)
        {

            if(j+1<sz && str[i][j]=='/' && str[i][j+1]=='/')
            {
                c1 = 1;
                str[i][j]  = ' ';
            }
            else if(j+1<sz && str[i][j]=='/' && str[i][j+1]=='*')
            {
                c2 = 1;
                str[i][j] = ' ';
            }
            else if(j+1<sz && str[i][j]=='*' && str[i][j+1]=='/')
            {
                c2 = 0;
                str[i][j]  = str[i][j+1] = ' ';
                j++;
            }
            else if(c1 || c2)
            {
                str[i][j]  = ' ';
            }

        }
        i++;
    }
    int totalsz = i;

    // add proper space
    for(k=1; k<totalsz; k++)
    {

        int flag  =0;
        int n = strlen(str[k]);
        strcpy(a,str[k]);
        j = 0;
        int sepOn = 0;
        for(i=0; i<n; i++)
        {

            if(isSep(a[i])==1)
            {
                if(a[i]=='\'')
                {
                    if(sepOn)
                    {
                        sepOn = 0;
                        b[j++]  = ' ';
                        b[j++]  = a[i];
                    }
                    else
                    {
                        b[j++]  = a[i];
                        b[j++]  = ' ';
                        sepOn = 1;
                    }
                }
                else
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                }
                b[j++]  = ' ';


            }
            else if(isOp(a[i])==1)
            {
                if(a[i+1]=='=')
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                    b[j++]  = a[i+1];
                    i++;
                    b[j++]  = ' ';
                }
                else
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                    b[j++]  = ' ';
                }
                flag  =1;
            }
            else if(isDigit(a[i])==1)
            {
                if(flag==0)
                {
                    flag = 1;
                    b[j++]  = ' ';
                }
                b[j++]  = a[i];
            }
            else if(isPar(a[i])==1)
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
                if(a[i]!=')')
                    b[j++]  = ' ';
            }
            else if(isBrc(a[i])==1)
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
                if(a[i]!='}')
                    b[j++]  = ' ';
            }
            else
            {
                flag  =1;
                b[j++]  = a[i];
            }
        }
        b[j-1]  = ' ';
        b[j] = '\0';

        strcpy(str[k],b);
        fprintf(fp3,"%s\n",str[k]);
    }


    //remove multiple whitespace

    for(k=1; k<totalsz; k++)
    {
        strcpy(a,str[k]);
        b[0]  = '\0';
        j = 0;
        for(i=0; i<strlen(a); i++)
        {
            if(a[i]==' ')
            {
                b[j++]  = ' ';
                while(i<strlen(a) && a[i]==' ')
                    i++;
                i--;
            }
            else b[j++]  =a[i];

        }
        b[j]  = '\0';
        strcpy(str[k],b);
        fprintf(fp2,"%s\n",b);
    }


    //label the tokens
    for(k=1; k<=totalsz; k++)
    {
        j = 0;
        strcpy(b,str[k]);
        for(i=0; i<strlen(b); i++)
        {
            if(b[i]==' ')
            {
                a[j++] = '\0';
                if(strlen(a)==0)
                {
                    j  =0;
                    continue;
                }
                if(isSepa(a)==1)
                {
                    printf("sep %s ",a);
                }
                else if(isKey(a)==1)
                {
                    printf("kw %s ",a);
                }
                else if(isId(a)==1)
                {
                    printf("id %s ",a);
                }
                else if(isOper(a)==1)
                {
                    printf("op %s ",a);
                }
                else if(isParen(a)==1)
                {
                    printf("par %s ",a);
                }
                else if(isBrace(a)==1)
                {
                    printf("brc %s ",a);
                }
                else if(isNum(a)==1)
                {
                    printf("num %s ",a);
                }
                else
                {
                    printf("unkn %s ",a);
                }
                j= 0;
            }
            else
            {
                a[j++]  = b[i];
            }

        }
        printf("\n");
    }





}
