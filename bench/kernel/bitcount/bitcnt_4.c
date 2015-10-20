/*

  This program is part of the TACLeBench benchmark suite.
  Version V 1.x

  Name: bitcnt_4.c

  Author: unknown

  Function: st is a statistics program.
    This program computes for two arrays of numbers the sum, the mean,
    the variance, and standard deviation. It then determines the
    correlation coefficient between the two arrays.

  Source: MRTC
          http://www.mrtc.mdh.se/projects/wcet/wcet_bench/st/st.c

  Changes: a brief summary of major functional changes (not formatting)

  License: general open-source

*/


#include "bitops.h"   /* from Snippets */

static char bitcount_bits[256];

/*
**  Count bits in each nybble
**
**  Note: Only the first 16 table entries are used, the rest could be
**        omitted.
*/

void bitcount_init4( void )
{
  int i = 0;
  char bitcount_bits_tmp[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
  };

  for ( i = 0; i < 256; i++ )
    bitcount_bits[i] = bitcount_bits_tmp[i];
}

int bitcount_ntbl_bitcnt( unsigned long x )
{
  int cnt = bitcount_bits[( int )( x & 0x0000000FL )];

  if ( 0L != ( x >>= 4 ) )
    cnt += bitcount_ntbl_bitcnt( x );

  return cnt;
}

/*
**  Count bits in each byte
*/

int bitcount_btbl_bitcnt( unsigned long x )
{
  int cnt = bitcount_bits[ ( ( char * ) & x )[0] & 0xFF ];

  if ( 0L != ( x >>= 8 ) )
    cnt += bitcount_btbl_bitcnt( x );
  return cnt;
}
