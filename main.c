#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "crc.h"


int main()
{
    char s[100];
    int q,ch,len;
    FILE *fp;

    while(1)
    {
        printf("\n-------------------------------------------------------------");
        printf("\n1.Enter file name\n2.Enter string\n3.Exit\n");
        scanf("%d",&q);

        switch(q)
        {
            case 1:
                    printf("Enter the file name : ");
                    scanf("%s",s);
                    fp = fopen(s,"rb");
                    if(!fp)
                    {
                        printf("\nFile not found\n");
                        break;
                    }
                    fclose(fp);

					calc_crc(s);



                    printf("\n-------------------------------------------------------------");
                    break;

            case 2:
                    while((ch=getchar()!='\n')&&(ch!=EOF)); //instead of fflush(stdin);
                    printf("\nEnter the string  : ");

                    fgets(s,sizeof(s),stdin);               //instead of gets();
                    len = strlen(s);

                    if(s[len-1]=='\n')
                        s[len-1] = '\0';

                    calc_crc_string(s);


                    printf("\n-------------------------------------------------------------"); break;

            case 3 :
                        exit(0); break;

            default : printf("\nInvalid input\n");
        }
    }
    return 0;
}
