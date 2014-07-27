/* date format parsing and conversion */
/* Spiros Ioannou 2008 */
/* Version 0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char ** argv)
{
   struct tm tm;
   char buf[512];


   if (argc!=4) {
     fprintf(stderr,"\nSpiros Ioannou 2008\n");
     fprintf(stderr,"\nstrpftime:Parse date strings with strptime and print result with strftime\n");
     fprintf(stderr,"usage: strpftime <input date string> <input strftime format> <output strptime format>\n");
     fprintf(stderr,"\nExamples:\nstrpftime \"2001-11-12 18:31:01\" "
	            " \"%%Y-%%m-%%d %%H:%%M:%%S\" "
		    " \"%%d %%b %%Y %%H:%%M\"\n");
     fprintf(stderr,"\nConvert HTTP Last-Modified to unix epoch:\nstrpftime "
	 "\"Sat, 20 Nov 2004 20:16:24 GMT\" "
	 "\"%%a, %%d %%b %%Y %%H:%%M:%%S %%z\" "
	 "\"%%s\"\n\n");
     exit(1);
   }

   strptime(argv[1],argv[2] , &tm);
   strftime(buf, sizeof(buf), argv[3], &tm);
   puts(buf);
   exit(EXIT_SUCCESS);
}
