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
#include <stdlib.h>
#include <stdio.h>

#include "wnlib.h"
#include "wnargp.h"
#include "wnasrt.h"
#include "wnmemb.h"

#include "wnchtb.h"
#include "wnchtl.h"


#if 0
local void lo_old_chash_test(void)
{
  wn_chtab table;
  int pad_before;
  int num;
  int pad_after;
  int ugly_int;
  bool success;
  int i;

  wn_memset(&ugly_int, (char) 0xc5, sizeof(ugly_int));
  pad_before = pad_after = ugly_int;

  WN_GPBEGIN("no_free");

    wn_mkintchtab(&table, 16, 0.9);

    for(i=0;i<10000;++i)
    {
      success = wn_chins((ptr)(i+1),table,(ptr)i);
      wn_assert(success);
    }

    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      if (!success) {		/* new */
	printf("%d\n", i);
      }
      wn_assert(success);
      wn_assert(num == i+1);
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    wn_chverify(table);

    for(i=0;i<5000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    wn_chverify(table);

    for(i=0;i<5000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(!(success));
    }

    wn_chverify(table);

    for(i=0;i<5000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!(success));
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    for(i=5000;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i+1);
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    for(i=2500;i<7500;++i)
    {
      success = wn_chfins((ptr)i,table,(ptr)i);
      wn_assert(success);
    }

    for(i=2500;i<7500;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i);
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    for(i=0;i<2500;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!(success));
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    for(i=7500;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i+1);
    }

    wn_chverify(table);

    for(i=2500;i<10000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    wn_chverify(table);

    wn_assert(wn_chcount(table) == 0);

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!(success));
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

  WN_GPEND();
} /* lo_old_chash_test */
#endif


#if 0
local void lo_new_chash_test(void)
{
  wn_chtab table;
  int pad_before;
  int num;
  int pad_after;
  int ugly_int;
  bool success;
  int i;

  wn_memset(&ugly_int, (char) 0xa5, sizeof(ugly_int));
  pad_before = pad_after = ugly_int;

  WN_GPBEGIN("no_free");

    wn_mkintchtab(&table, 16, 0.9);

    for(i=0;i<10000;i+=10)
    {
      success = wn_chins((ptr)(i+3),table,(ptr)i);
      wn_assert(success);
    }

    wn_assert(wn_chcount(table) == 1000);
    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      if (i % 10)
      {
	wn_assert(!success);
      }
      else
      {
        wn_assert(success);
	wn_assert(num == i+3);
      }
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    wn_chverify(table);

    for(i=0;i<10000;i+=25)
    {
      num = ugly_int;
      success = wn_chdel(table,(ptr)i);
      if (i % 50)
      {
        wn_assert(!success);
      }
      else
      {
        wn_assert(success);
      }
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    wn_assert(wn_chcount(table) == 800);
    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      success = wn_chfins((ptr)(i+5),table,(ptr)i);
      wn_assert(success);
    }

    wn_assert(wn_chcount(table) == 10000);
    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i+5);
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    wn_chverify(table);

    for(i=0;i<10000;i+=3)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success == !!(i % 3));
      wn_assert(!success || num == i+5);
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    for(i=0;i<10000-1;i+=3)
    {
      success = wn_chdel(table,(ptr)(i+1));
      wn_assert(success);
    }

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success == !((i-2) % 3));
      wn_assert(!success || num == i+5);
    }

    for(i=0;i<10000-2;i+=3)
    {
      success = wn_chdel(table,(ptr)(i+2));
      wn_assert(success);
    }

    for(i=0;i<10000;++i)
    {
      num = ugly_int;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!success);
      wn_assert(ugly_int == pad_before  &&  ugly_int == pad_after);
    }

    wn_assert(wn_chcount(table) == 0);
    wn_chverify(table);

  WN_GPEND();
} /* lo_new_chash_test */
#endif /* 0 */


local void lo_old_long_chash_test(void)
{
  wn_chtab table;
  long int num, ugly_long;
  bool success;
  int i;

  wn_memset(&ugly_long, (char) 0xb7, sizeof(ugly_long));

  WN_GPBEGIN("no_free");

    wn_mklongchtab(&table, 16, 0.9);

    for(i=0;i<10000;++i)
    {
      success = wn_chins((ptr)(i+1),table,(ptr)i);
      wn_assert(success);
    }

    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      if (!success) {		/* new */
	printf("%d\n", i);
      }
      wn_assert(success);
      wn_assert(num == i+1);
    }

    wn_chverify(table);

    for(i=0;i<5000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    wn_chverify(table);

    for(i=0;i<5000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(!(success));
    }

    wn_chverify(table);

    for(i=0;i<5000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!(success));
    }

    for(i=5000;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i+1);
    }

    for(i=2500;i<7500;++i)
    {
      success = wn_chfins((ptr)i,table,(ptr)i);
      wn_assert(success);
    }

    for(i=2500;i<7500;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i);
    }

    for(i=0;i<2500;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!(success));
    }

    for(i=7500;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i+1);
    }

    wn_chverify(table);

    for(i=2500;i<10000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    wn_chverify(table);

    wn_assert(wn_chcount(table) == 0);

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!(success));
    }

  WN_GPEND();
} /* lo_old_chash_test */


local void lo_new_long_chash_test(void)
{
  wn_chtab table;
  long int num, ugly_long;
  bool success;
  int i;

  wn_memset(&ugly_long, (char) 0xd2, sizeof(ugly_long));

  WN_GPBEGIN("no_free");

    wn_mklongchtab(&table, 16, 0.9);

    for(i=0;i<10000;i+=10)
    {
      success = wn_chins((ptr)(i+3),table,(ptr)i);
      wn_assert(success);
    }

    wn_assert(wn_chcount(table) == 1000);
    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      if (i % 10)
      {
	wn_assert(!success);
      }
      else
      {
        wn_assert(success);
	wn_assert(num == i+3);
      }
    }

    wn_chverify(table);

    for(i=0;i<10000;i+=25)
    {
      success = wn_chdel(table,(ptr)i);
      if (i % 50)
      {
        wn_assert(!success);
      }
      else
      {
        wn_assert(success);
      }
    }

    wn_assert(wn_chcount(table) == 800);
    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      success = wn_chfins((ptr)(i+5),table,(ptr)i);
      wn_assert(success);
    }

    wn_assert(wn_chcount(table) == 10000);
    wn_chverify(table);

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success);
      wn_assert(num == i+5);
    }

    wn_chverify(table);

    for(i=0;i<10000;i+=3)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success == !!(i % 3));
      wn_assert(!success || num == i+5);
    }

    for(i=0;i<10000-1;i+=3)
    {
      success = wn_chdel(table,(ptr)(i+1));
      wn_assert(success);
    }

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(success == !((i-2) % 3));
      wn_assert(!success || num == i+5);
    }

    for(i=0;i<10000-2;i+=3)
    {
      success = wn_chdel(table,(ptr)(i+2));
      wn_assert(success);
    }

    for(i=0;i<10000;++i)
    {
      num = ugly_long;
      success = wn_chget((ptr *)&num,table,(ptr)i);
      wn_assert(!success);
    }

    wn_assert(wn_chcount(table) == 0);
    wn_chverify(table);

  WN_GPEND();
} /* lo_new_chash_test */


local void lo_read_dict(void)
{
  FILE *fp;
  char buffer[1000];
  wn_chtab table;
  long int num;
  int sts, pre_valid_count;
  const char *filename;

  WN_GPBEGIN("no_free");

    wn_mkstrchtab(&table, 10, 0.9);

    filename = getenv("WN_HASH_DICT");
    if (!filename) {
#     if defined(linux) || defined(__linux__)
	filename = "/usr/share/dict/words";
#     else 
	filename = "/usr/dict/words";
#     endif
    }	

    fp = fopen(filename, "r");
    if(fp == NULL)
    {
      printf("warning: cannot find dictionary file <%s>,\n",filename);
      printf("    skipping chash dictionary test\n",filename);
      printf("    If you know where a dictionary is, you can use it by\n");
      printf("    setting environment variable $WN_HASH_DICT to it.\n");
      goto finish;
    }

    while (TRUE)
    {
      sts = fscanf(fp, "%s", buffer);
      if (1 != sts)
      {
	break;
      }

      pre_valid_count = wn_chcount(table);
      sts = wn_chins((ptr)0, table, (ptr) buffer);
      wn_assert(sts  &&  wn_chcount(table) == pre_valid_count+1);
    }

    fclose(fp);

    if(wn_chcount(table) <= 20000)
    {
      printf("warning: dictionary contains less than 20000 words.\n");
    }

    wn_chverify(table);

    wn_assert(wn_chget((ptr *)&num, table, (ptr) "here"));
    wn_assert(wn_chget((ptr *)&num, table, (ptr) "there"));
    wn_assert(wn_chget((ptr *)&num, table, (ptr) "and"));
    wn_assert(wn_chget((ptr *)&num, table, (ptr) "everywhere"));
    wn_assert(!wn_chget((ptr *)&num, table, (ptr) "missspelled"));
    wn_assert(!wn_chget((ptr *)&num, table, (ptr) "wwwords"));

finish:
  WN_GPEND();
} /* lo_read_dict */


local void lo_test_shrink(void)
{
  wn_chtab table;
  int i;
  bool success;

  WN_GPBEGIN("no_free");

    wn_mklongchtab(&table, 16, 0.9);

    for(i=0;i<10000;++i)
    {
      success = wn_chins((ptr)(i+3),table,(ptr)i);
      wn_assert(success);
    }

    wn_assert(wn_chcount(table) == 10000);
    wn_chverify(table);

    for(i=16;i<10000;++i)
    {
      success = wn_chdel(table,(ptr)i);
      wn_assert(success);
    }

    wn_assert(10000-16 == table->deleted_entries);
    wn_assert(wn_chcount(table) == 16);
    wn_chverify(table);

    wn_purge_and_resize_table(table, 20);

    wn_assert(32 == table->length);
    wn_assert(0 == table->deleted_entries);
    wn_assert(wn_chcount(table) == 16);
    wn_chverify(table);

    wn_purge_and_resize_table(table, 32);

    wn_assert(32 == table->length);
    wn_assert(0 == table->deleted_entries);
    wn_assert(wn_chcount(table) == 16);
    wn_chverify(table);
  WN_GPEND();
} /* lo_test_shrink */


int main(int argc,char *argv[])
{
  bool ints_bad = FALSE;
  static wn_arg_format arg_format_array[] =
  {
    WN_KEY_BOOL(&wn_chtab_checks_for_duplicates, "d"),	/* checking for
    **			duplicates is O(n^2), takes a LONG time. */
    WN_ARG_TERMINATE
  };

  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  WN_GPBEGIN("no_free");

    wn_parse_args(argc,argv,arg_format_array);

    printf("testing chash... set -d for duplicate checking (very slow)\n");

    /* hash table keys won't work if this is not true */
    wn_assert(sizeof(long int) <= sizeof(ptr));

    /*     "wn_chget(&ll, .." where ll is a long will not work right if this
    ** is not true */
    wn_assert(sizeof(long int) == sizeof(ptr));

    lo_old_long_chash_test();
    lo_new_long_chash_test();
    lo_read_dict();
    lo_test_shrink();

    if (sizeof(int) != sizeof(ptr))
    {
      fprintf(stderr,
      /**/ "    sizeof(int) != sizeof(ptr), don't expect test code\n"
      /**/ "    for int hash tables to work, set env var $WN_TEST_CHASH_INTS\n"
      /**/ "    to run hash int tests\n"
      /**/ "        Note wn_mkintchtab() works, but just by calling\n"
      /**/ "    wn_mklongchtab() and the data values it stores are longs,\n"
      /**/ "    not ints\n");
      ints_bad = TRUE;
    }

#   if 0
      if (!ints_bad  ||  getenv("WN_TEST_CHASH_INTS")) {
	lo_old_chash_test();
	lo_new_chash_test();
      }
#   endif /* 0 */

    printf("  ok!!!!!!\n");

    wn_assert(0 == wn_group_mem_used(wn_curgp()));
  WN_GPEND();

  return 0;
} /* main */
