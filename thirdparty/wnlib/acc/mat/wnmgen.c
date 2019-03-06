/**********************************************************************

wn_zero_mat(mat,len_i,len_j)

wn_identity_mat(mat,len_i)
wn_hilbert_mat(mat,len_i)

**********************************************************************/
/****************************************************************************

COPYRIGHT NOTICE:

  The source code in this directory is provided free of
  charge to anyone who wants it.  It is in the public domain
  and therefore may be used by anybody for any purpose.  It
  is provided "AS IS" with no warranty of any kind
  whatsoever.  For further details see the README files in
  the wnlib parent directory.

AUTHOR:

  Will Naylor

****************************************************************************/

#include "wnlib.h"
#include "wnvect.h"

#include "wnmat.h"



void wn_zero_mat(double **mat,int len_i,int len_j)
{
  int i;

  for(i=0;i<len_i;++i)
  {
    wn_zero_vect(mat[i],len_j);
  }
}


void wn_identity_mat(double **mat,int len)
{
  int i;

  wn_zero_mat(mat,len,len);

  for(i=0;i<len;++i)
  {
    mat[i][i] = 1.0;
  }
}


void wn_hilbert_mat(double **mat,int len)
{
  int i,j;

  for(i=0;i<len;++i)  
  for(j=0;j<len;++j)
  {
    mat[i][j] = 1.0/((double)(i+j+1));
  }
}



