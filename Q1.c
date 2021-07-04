#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
char buff[1000000];
void reverse(long long int sb_size,int fd1,int fd2,char * file_2);
void percentage(long long int sb_size,long long int sb2_size)
{
    char s1[50]="";
    char s2[50]="";
    s2[0]='\r';
    float per;
    per=sb2_size*100;
    per=per/(float)sb_size;
    sprintf(s1,"%0.2f",per);
    s2[1]=s1[0];
    s2[2]=s1[1];
    s2[3]=s1[2];
    s2[4]=s1[3];
    s2[5]=s1[4];
    s2[6]=s1[5];
    write(1,s2,6);
}
int main(int argc, char * argv[])
{
    //argv[1] has input file location in string format
    long long int size_arg,i=0;
    size_arg=strlen(argv[1]);
    for(i=(size_arg-1);i>=0;i--)
    {
        if( argv[1][i] == '/' )
        {
            break;
        }
    }
    char* file_1;long long int s_1;
    file_1=&argv[1][i+1]; //file_1 has input file string
    s_1=size_arg-1-i;  // its size
    char file_2[s_1+12]; //file_2 has output file relative location string
    file_2[0]='A';
    file_2[1]='s';
    file_2[2]='s';
    file_2[3]='i';
    file_2[4]='g';
    file_2[5]='n';
    file_2[6]='m';
    file_2[7]='e';
    file_2[8]='n';
    file_2[9]='t';
    file_2[10]='/';


    //finding the real file name if absolute path was given as argument
    for(long long int j=0;j<(s_1);j++)
    {
        file_2[j+11]=file_1[j];
    }
    file_2[s_1+11]='\0';
    //printf("%s\n",argv[1]);
    //printf("%s\n",file_1);
    //printf("%s\n",file_2);

    
    //finding size of input file using stat syscall
    struct stat sb;
    stat(argv[1],&sb);
    //printf("%ld\n",sb.st_size);

    //reversing

    //step 1 open th both files
    int fd1,fd2;
    fd1=open(argv[1],O_RDONLY);
    if(fd1<0)
    {
        perror("system error:");
        return 0;
    }
    if(S_ISDIR(sb.st_mode))
    {
        write(1,"This is a directory \n",22);
        return 0;
    }
    //make a directory named "Assignment" 
    mkdir("Assignment",0777);    
    fd2=open(file_2,O_RDWR,0644);
    if(fd2 > 0)
    {
        unlink(file_2);
    }
    fd2=open(file_2,O_CREAT | O_RDWR,0644);

    
    //reverse
    reverse(sb.st_size,fd1,fd2,file_2);
    close(fd2);
    close(fd1);
    //permissions for input file and asssignment directory
    chmod("Assignment",S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    chmod(file_2,S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    
}

void reverse(long long int sb_size,int fd1,int fd2,char * file_2)
{
    long long int mul,rem;
    mul=sb_size/1000000;
    rem=sb_size%1000000;
    lseek(fd1,0,SEEK_END);
    for(long long int b=1;b<=mul;b++)
    {
        lseek(fd1,-1000000,SEEK_CUR);
        read(fd1,buff,1000000);
        for(long long int c=0;c<=((1000000-1)/2);c++)
        {
            char temp;
            temp=buff[1000000-1-c];
            buff[1000000-1-c]=buff[c];
            buff[c]=temp;
        }
        lseek(fd1,-1000000,SEEK_CUR);
        write(fd2,buff,1000000);
        struct stat sb2;
        stat(file_2,&sb2);
        percentage(sb_size,sb2.st_size);
    }
    lseek(fd1,0,SEEK_SET);
    read(fd1,buff,rem);
    for(long long int a=0;a<=((rem-1)/2);a++)
    {
        char temp;
        temp=buff[a];
        buff[a]=buff[rem-1-a];
        buff[rem-1-a]=temp;
    }
    write(fd2,buff,rem);
    struct stat sb3;
    stat(file_2,&sb3);
    percentage(sb_size,sb3.st_size);
    return;
}

    