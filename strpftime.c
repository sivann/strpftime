/* date format parsing and conversion */
/* Spiros Ioannou 2008 */

#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void usage() {
     fprintf(stderr,"\nstrpftime:Parse date strings with strptime and print result with strftime\n");
     fprintf(stderr,"usage: strpftime -i <input strftime format> -o <output strptime format> -l <read that many chars on each line>\n");
     fprintf(stderr,"\t -t: truncate output to -l value (just output dates)\n");
     fprintf(stderr,"\nExamples:\n cat logfile | strpftime "
	        " -i \"%%Y-%%m-%%d %%H:%%M:%%S\" "
		    " -o \"%%d %%b %%Y %%H:%%M\""
		    " -l 20\n"
		    " -t\n"
			);
}

int main(int argc, char ** argv)
{
   struct tm tm;
   char buf[512];
   char input_format[128];
   char output_format[128];
   int length=0;
   char line[4096];
   char line_part[1024];
   int r;
   int opt;
   int want_truncate = 0 ;

   input_format[0]=0;
   output_format[0]=0;
   length=0;



   while ((opt = getopt(argc, argv, "i:o:l:t")) != -1) {
	   switch (opt) {
		   case 'i':
			   strcpy(input_format, optarg);
			   break;
		   case 'o':
			   strcpy(output_format, optarg);
			   break;
		   case 'l':
			   length=atoi(optarg);
			   break;
		   case 't':
			   want_truncate=1;
			   break;
			default:
			   usage();
			   exit(EXIT_FAILURE);
	   }
   }

   if (optind < 7) {
	   usage();
	   exit(EXIT_FAILURE);
   }
   
   while (fgets(line, sizeof(line), stdin)) {
	   bzero(line_part,sizeof(line_part));
	   strncpy(line_part,line,length);
	   if (!strptime(line_part, input_format, &tm)) {
		   fprintf(stderr,"strptime;error parsing time [%s] from [%s]\n",input_format,line_part);
		   continue;
	   }

	   r = strftime(buf, sizeof(buf), output_format, &tm);
	   if (r==0) {
		   fprintf(stderr,"strftime;error creating time from [%s]\n",output_format);
		   continue;
	   }
	   if (want_truncate) {
		   printf("%s\n",buf);
	   }
	   else {
		   printf("%s%s",buf, line+length);
	   }

   }

   exit(EXIT_SUCCESS);
}
