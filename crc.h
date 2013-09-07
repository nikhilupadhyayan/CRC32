#ifndef CRC_H
#define CRC_H

void calc_crc(char *);
void calc_crc_string(char *);

void fill_byte4(FILE*,unsigned int *,unsigned long long *);
void fill_byte4_string(char *,unsigned int *,unsigned long long *);

void xor_shift(FILE*,unsigned int *,unsigned long long *);
void xor_shift_string(char *,unsigned int *,unsigned long long *);

void final_xor_shift(  unsigned int *,unsigned long long *);
void get_crc(unsigned long long * );

#endif
