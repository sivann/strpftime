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
     fprintf(stderr,"usage: strpftime -i <input strftime format> -o <output strptime format> [-l <chars> | -f <fields>]\n");
     fprintf(stderr,"\t -i: input format (check man strftime)\n");
     fprintf(stderr,"\t -o: output format (check man strptime)\n");
     fprintf(stderr,"\t -l: input format length in bytes. Must be exact\n");
     fprintf(stderr,"\t -f: input format length in fields, space separated. May be used instead of -l\n");
     fprintf(stderr,"\t -F: skip fields from start of line\n");
     fprintf(stderr,"\t -t: truncate output to -l value (just output dates)\n");;
     fprintf(stderr,"\t -r: repeat original date on output\n");
     fprintf(stderr,"\t -d: show some debugging info\n");
     fprintf(stderr,"\nExamples:\n cat logfile | strpftime "
	        " -i \"%%Y-%%m-%%d %%H:%%M:%%S\" "
		    " -o \"%%d %%b %%Y %%H:%%M\""
		    " -l 20"
		    " -t\n"
			);
}

int main(int argc, char ** argv)
{
   struct tm tm;
   struct tm * tm1;
   time_t tm_epoch;
   char buf[512];
   char input_format[128];
   char output_format[128];
   int length=0;
   int fields=0;
   int want_repeat_date=0;
   int skip_fields=0;
   int input_length=0;
   char line[4096];
   char line_part[1024];
   int r;
   int opt;
   int want_truncate = 0 ;
   int debug=0;

   input_format[0]=0;
   output_format[0]=0;



   while ((opt = getopt(argc, argv, "dri:o:l:tf:")) != -1) {
	   switch (opt) {
		   case 'd':
			   debug=1;
			   break;
		   case 'i':
			   strcpy(input_format, optarg);
			   break;
		   case 'o':
			   strcpy(output_format, optarg);
			   break;
		   case 'l':
			   length=atoi(optarg);
			   break;
		   case 'f':
			   fields=atoi(optarg);
			   break;
		   case 'F':
			   skip_fields=atoi(optarg);
			   break;
		   case 't':
			   want_truncate=1;
			   break;
		   case 'r':
			   want_repeat_date=1;
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

   if (length && fields) {
	   usage();
	   fprintf(stderr,"\nPlease specify on of -f or -l\n");
	   exit(EXIT_FAILURE);
   }

   if (!length && !fields) {
	   usage();
	   fprintf(stderr,"\nPlease specify one  of -f or -l\n");
	   exit(EXIT_FAILURE);
   }
   
   while (fgets(line, sizeof(line), stdin)) {
	   char *p;
	   bzero(line_part, sizeof(line_part));
	   p=&line[0];

	   if (skip_fields) {
		   int fi;
		   while (*p==' ') p++; //skip leading space
		   for (fi =0; fi<skip_fields;fi++) {
			   while (*p!=' ' && *p) p++; //skip field
			   while (*p==' ') p++; //skip spaces
		   }
	   }

	   if (length) {
		   strncpy(line_part, p, MIN(length,sizeof(line_part)));
		   input_length=length;
	   }
	   else { //fields
		   int ns;
		   int fi;
		   int spaces_skipped=0;

		   p=&line[0];
		   while (*p==' ') {
			   p++; //skip leading space
			   spaces_skipped++;
		   }
		   for (fi =0; fi<fields;fi++) {
			   ns = sscanf(p,"%s",buf);   //read field
			   if (!ns)
				   break;
			   strcat(line_part,buf); //append
			   p+=strlen(buf);

			   if (*p && fi<(fields-1)) { //append next space if exists
				   strncat(line_part,p,1);
				   p++;
			   }

			   if (fi<(fields-1)) //skip spaces if not last field
				   while (*p==' ') {
					   p++; //skip spaces
					   spaces_skipped++;
				   }
		   }
		   input_length=strlen(line_part)+spaces_skipped;;
	   }

	   if (debug)
		   fprintf(stderr,"INPUT_LINE_PART:[%s], input length:%d\n",line_part,input_length);

	   //initialize tm with local time for missing fields
	   time(&tm_epoch);
	   tm1=localtime(&tm_epoch);
	   memcpy(&tm,tm1,sizeof(struct tm));



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
	   else if (want_repeat_date) {
		   printf("%s%s",buf, line);
	   }
	   else {
		   printf("%s%s",buf, line+input_length);
	   }

   }

   exit(EXIT_SUCCESS);
}
