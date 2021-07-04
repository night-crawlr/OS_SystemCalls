#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
char buff[1000000];
void fin(char *n,int *arr)
{
    int x;
    x=(*n)-48;
    arr[8]=x%2;
    x=x/2;
    arr[7]=x%2;
    x=x/2;
    arr[6]=x%2;
    x=(*(n-1))-48;
    arr[5]=x%2;
    x=x/2;
    arr[4]=x%2;
    x=x/2;
    arr[3]=x%2;
    x=(*(n-2))-48;
    arr[2]=x%2;
    x=x/2;
    arr[1]=x%2;
    x=x/2;
    arr[0]=x%2;
}
void check_reverse(int fd1, int fd2,char* new_f,char* old_f,int flag)
{
    if(fd1 < 0 | fd2 < 0 | flag)
    {
        write(1,"Two files are not present to check whether they are reverse or not\n",68);
        return;
    }
    struct stat s1,s2;
    stat(new_f,&s1);
    stat(old_f,&s2);
    if(s1.st_size != s2.st_size)
    {
        write(1,"Whether file contents are reversed in newfile: No\n",51);
        return;
    }
    long long int sb_size=s1.st_size;
    long long int mul,rem;
    mul=sb_size/1000000;
    rem=sb_size%1000000;
    lseek(fd1,0,SEEK_END);
    for(long long int b=1;b<=mul;b++)
    {
        char buf1[1000000];
        char buf2[1000000];
        lseek(fd1,-1000000,SEEK_CUR);
        read(fd1,buf1,1000000);
        lseek(fd1,-10000000,SEEK_CUR);
        read(fd2,buf2,1000000);
        for(long long int a=0;a<1000000;a++)
        {
            if(buf1[a]!=buf2[1000000-1-a])
            {
                char* st;
                st="Whether file contents are reversed in newfile: No\n";
                write(1,st,51);                
                return;
            }
        }
    }
    char buf1[1000000];
    char buf2[1000000];
    lseek(fd1,0,SEEK_SET);
    read(fd1,buf1,rem);
    read(fd2,buf2,rem);
    for(long long int b=0;b<rem;b++)
    {
        if(buf1[b]!=buf2[rem-1-b])
        {
            char* st;
            st="Whether file contents are reversed in newfile: No\n";
            write(1,st,51);
            return;
        }        
    }
    char* st;
    st="Whether file contents are reversed in newfile: Yes\n";
    write(1,st,52);
    return;
}
int main(int argc, char * argv[])
{
    // checking directory is present or not directory ie argv[3]
    struct stat s,s1,s2;
    int d_p,d_p1,d_p2;
    d_p=stat(argv[3],&s);
    if(d_p == 0)
    {
        d_p=S_ISDIR(s.st_mode);
        d_p=d_p-1;
    }
    if(d_p == 0 )
    {
        char * buf;
        buf="Directory is created: Yes\n";
        write(1,buf,27);
    }
    else
    {
        char * buf;
        buf="Directory is created: No\n";
        write(1,buf,26);        
    }
    int fd1,fd2;
    fd1=open(argv[1],O_RDONLY,0644);//checking if new file is present or not
    fd2=open(argv[2],O_RDONLY,0644);//checking if old file is present or not
    d_p1=stat(argv[1],&s1);d_p1=S_ISDIR(s1.st_mode);
    d_p2=stat(argv[2],&s2);d_p2=S_ISDIR(s2.st_mode);    
    if(fd1  < 0)
    {
        perror("new file");

    }
    if(fd2 < 0)
    {
        perror("old file");
    }

    check_reverse(fd1,fd2,argv[1],argv[2],(d_p1|d_p2));
    char p1[50]="";
    char p2[50]="";
    char p[50]="";
    sprintf(p, "%o", s.st_mode); //permissions of directory in p
    sprintf(p1, "%o", s1.st_mode);//permissions of new file in p1    
    sprintf(p2, "%o", s2.st_mode);//permissions of old file in p2
    // printing permissions for arguments
    char*n1;n1=p1;
    char*n2;n2=p2;
    char*n;n=p;
    for(int z=0;z<8;z++)
    {
        if(*(p1+z) != '\0')
        {
            n1=p1+z;
        }
        if(*(p2+z) != '\0')
        {
            n2=p2+z;
        }
        if(*(p+z) != '\0')
        {
            n=p+z;
        }
    }
    //printf("%s %s %s\n",p1,p2,p);
    //printf("%c %c %c\n",*n1,*n2,*n);
    int arr[9];fin(n,arr);
    int arr1[9];fin(n1,arr1);
    int arr2[9];fin(n2,arr2);
    for(int a=1;a<=3;a++)
    {
        if(a==1 && fd1 < 0)
        {
            write(1,"The permissions doesn't exist since there is no newfile\n",57);
            continue;
        }
        if(a==2 && fd2 < 0)
        {
            write(1,"The permissions doesn't exist since there is no oldfile\n",57);
            continue;
        }
        if(a==3 && d_p < 0)
        {
            write(1,"The permissions doesn't exist since there is no directory\n",59);
            continue;
        }
        for(int b=1;b<=3;b++)
        {
            for(int c=1;c<=3;c++)
            {
                char U[50]="";
                char R[50]="";
                char n[50]="";
                if(b==1)
                {
                    U[0]='U';U[1]='s';U[2]='e';U[3]='r';U[4]='\0';
                }
                if(b==2)
                {
                    U[0]='G';U[1]='r';U[2]='o';U[3]='u';U[4]='p';U[5]='\0';                    
                }
                if(b==3)
                {
                    U[0]='O';U[1]='t';U[2]='h';U[3]='e';U[4]='r';U[5]='s';U[6]='\0';                    
                }
                if(c==3)
                {
                    R[0]='e';R[1]='x';R[2]='e';R[3]='c';R[4]='u';R[5]='t';R[6]='e';R[7]='\0';
                }
                if(c==2)
                {
                    R[0]='w';R[1]='r';R[2]='i';R[3]='t';R[4]='e';R[5]='\0';
                }
                if(c==1)
                {
                    R[0]='r';R[1]='e';R[2]='a';R[3]='d';R[4]='\0';R[5]='\0';
                }
                if(a==1)
                {
                    n[0]='n';n[1]='e';n[2]='w';n[3]='f';n[4]='i';n[5]='l';n[6]='e';n[7]='\0';
                } 
                if(a==2)
                {
                    n[0]='o';n[1]='l';n[2]='d';n[3]='f';n[4]='i';n[5]='l';n[6]='e';n[7]='\0';
                }
                if(a==3)
                {
                    n[0]='d';n[1]='i';n[2]='r';n[3]='e';n[4]='c';n[5]='t';n[6]='o';n[7]='r';n[8]='y';n[9]='\0';
                }
                write(1,U,7);
                write(1," has ",6);         
                write(1,R,8);
                write(1," permission on ",16);
                write(1,n,10);
                if(a==1)
                {
                    if(arr1[ 3*(b-1) + c-1]==1)
                    {
                        write(1,": Yes\n",7);
                    }
                    else
                    {
                        write(1,": No\n",6);
                    }
                }
                if(a==2)
                {
                    if(arr2[ 3*(b-1) + c-1]==1)
                    {
                        write(1,": Yes\n",7);
                    }
                    else
                    {
                        write(1,": No\n",6);
                    }
                }
                if(a==3)
                {
                    if(arr[ 3*(b-1) + c-1]==1)
                    {
                        write(1,": Yes\n",7);
                    }
                    else
                    {
                        write(1,": No\n",6);
                    }
                }                               
            }
        }
    }
}
