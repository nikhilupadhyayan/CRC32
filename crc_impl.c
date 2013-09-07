#include<stdio.h>
#include"crc.h"
#define POLY 0x82608EDB

int i;
int j;
unsigned long long poly;
unsigned long long msb;

void calc_crc(char *name)
{
    msb=0x80000000;
    msb=msb<<32;
    FILE *fptr = fopen(name,"r");
	poly=POLY;
	 poly=poly<<32;
	i=0;

	  unsigned long long rem=0;
	  unsigned int c;


	c=fgetc(fptr);



	for(i=0;i<4;++i)//initially filling the most sgnificant 4 bytes of rem.
	{
		if(c!=EOF)//;c!=EOF
		{
			c=c<<24;
			rem=rem|c;
			c=fgetc(fptr);
		}
		rem=rem<<8;

	}

	fill_byte4(fptr,&c,&rem);
    fclose(fptr);

}
void fill_byte4(FILE* fptr,unsigned int *c_ptr, unsigned long long *rem_ptr )
{

 	 if(*c_ptr!=EOF)//initial filling of fifth bit.
         {

		*c_ptr=*c_ptr<<24;
                *rem_ptr=*rem_ptr|*c_ptr;
              	*c_ptr=fgetc(fptr);
		xor_shift(fptr,c_ptr,rem_ptr);

	}
	else
	{

		final_xor_shift(c_ptr,rem_ptr);
        	get_crc(rem_ptr);
	}
}

void xor_shift(FILE *fptr, unsigned int *c_ptr, unsigned long long *rem_ptr)
{

	int count=8;
	while(count>0)
	{
		//if(*rem_ptr>=pow(2,63))
			if(*rem_ptr&msb)
			*rem_ptr=*rem_ptr^poly;

		*rem_ptr=*rem_ptr<<1;
		count--;
	}

		fill_byte4(fptr,c_ptr,rem_ptr);


}


void final_xor_shift(unsigned int *c_ptr,unsigned long long *rem_ptr)
{
	int count=32;
        while(count>0)
        {
                //if(*rem_ptr>=pow(2,63))
                  if(*rem_ptr&msb)
                        *rem_ptr=*rem_ptr^poly;

                *rem_ptr=*rem_ptr<<1;
                count--;

        }

}

void get_crc( unsigned long long *rem_ptr)
{
	int crc=*rem_ptr>>32;

	printf("\nCRC32 : %08X\n\n",crc);
}

void calc_crc_string(char *string)
{
	 j=0;
     msb=0x80000000;
    msb=msb<<32;
	 unsigned long long rem=0;
	unsigned int c=0;
	poly=POLY;
	poly=poly<<32;
	c=string[j++];
	//printf("%c",c);

	for(i=0;i<4;++i)//initially filling the most sgnificant 4 bytes of rem.
        {
                if(c!='\0')
                {
                        c=c<<24;
                        rem=rem|c;
                        c=string[j++];
                }
                rem=rem<<8;

        }
//	printf("%d\n",j);
	fill_byte4_string(string,&c,&rem);

}

void fill_byte4_string(char *string,unsigned int *c_ptr,unsigned long long *rem_ptr )
{

         if(*c_ptr!='\0')//initial filling of fifth bit.
         {

                *c_ptr=*c_ptr<<24;
                *rem_ptr=*rem_ptr|*c_ptr;
                *c_ptr=string[j++];
		xor_shift_string(string,c_ptr,rem_ptr);

        }
        else
        {

                final_xor_shift(c_ptr,rem_ptr);
                get_crc(rem_ptr);
        }
}

void xor_shift_string(char *string,unsigned int *c_ptr,unsigned long long *rem_ptr)
{
        int count=8;
        while(count>0)
        {
                //if(*rem_ptr>=pow(2,63))
                  if(*rem_ptr&msb)
                        *rem_ptr=*rem_ptr^poly;

                *rem_ptr=*rem_ptr<<1;
                --count;
        }

                fill_byte4_string(string,c_ptr,rem_ptr);


}


