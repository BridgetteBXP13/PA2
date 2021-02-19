/***************************************************************************
 *		filedisp	Bridgette Bryant	 PA2	           *
 *					                                   *
 *	This program will recieve text (3 lines) from standard		   *
 *	input, then it will have one of 3 options:		 	   *
 *	-d, displays the input line that has the word "directories"	   *
 *	-f, displays the input line that has the word "files"		   *
 *	-b, displays the input line that has the word "bytes"		   *
 *					                                   *
 *	It is created to work along another program called filecnt.	   *
 *						                           *
 *	It will utilize the pipe techniques and be used as a filter. 	   *
 ***************************************************************************/

/* Some needed libraries: */
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

/* Defining my functions */
void version();
void help();

/* The driver function */
int main(int argc, char**argv )
{
	/* Some Variables */
	char line1[1000];
	char line2[1000];
	char line3[1000];
	char choice[2];	/* The choice given by the user */

	/* Get the lines */
	(void)fgets(line1, sizeof(line1), stdin);
	(void)fgets(line2, sizeof(line2), stdin);
	(void)fgets(line3, sizeof(line3), stdin);

	/* Print out the lines, for debugging */
	/*(void)printf("%s\n", line1);
	(void)printf("%s\n", line2);
	(void)printf("%s\n", line3);*/

	int numOpt = 0;	// Just in case the user gets tricky and gives multiple options. */
	/* First we check that the given amount of arguments is 2-4, one for ./main,
		 and 1 path, otherwise exit, or --help/--version */
	if(argc < 2 || argc > 4)
	{
		printf("Invalid amount of arguments! Must be between 2 and 4, see --help\n");
	}
	/* In case the user used --version or --help */
	for(int i = 1; i < argc; ++i)
	{
		if((strncmp(argv[i], "--version", 9) == 0) || (strncmp(argv[i], "-v", 2) == 0))
		{
			version();
		}
		else if((strncmp(argv[i], "--help", 6) == 0) || (strncmp(argv[i], "-h", 2) == 0))
		{
			help();
		}
		else if(numOpt < 1)
		{	/* If they choose the -d option */
			if(strncmp(argv[i], "-d", 2) == 0)
			{
			 	/* If line1 has the "directories" string */
				if(strstr(line1, "directories") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line1);
				} /* If line2 has the "directories" string */
				else if(strstr(line2, "directories") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line2);
				} /* If line3 has the "directories" string */
				else if(strstr(line3, "directories") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line3);
				}
				/* Exit */
				return (0);
			} /* If they choose the -f option */
			else if(strncmp(argv[i], "-f", 2) == 0)
			{
				/* If line1 has the "files" string */
				if(strstr(line1, "files") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line1);
				} /* If line2 has the "files" string */
				else if(strstr(line2, "files") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line2);
				} /* If line3 has the "files" string */
				else if(strstr(line3, "files") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line3);
				}
				/* Exit */
				return (0);
			} /* If they choose the -b option */
			else if(strncmp(argv[i], "-b", 2) == 0)
			{
				/* If the line1 has the "bytes" string */
				if(strstr(line1, "bytes") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line1);
				} /* If the line2 has the "bytes" string */
				else if(strstr(line2, "bytes") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line2);
				} /* If the line3 has the "bytes" string */
				else if(strstr(line3, "bytes") != NULL)
				{
					/* Print out that line */
					(void)printf("%s\n", line3);
				}
				/* Exit */
				return (0);
			} /* If they choose an invalid option */
			else
			{
				(void)printf("Invalid option: %s", argv[i]);
			}
		}
	}

 	   /* Exit */
 	   return  (0);
}



/* Displays the version of the program */
void version()
{
	(void)printf("version:\tfileisp\t1.0.0\tBridgette Bryant\t2/25/2020\n");
}

/* Displays information to help users */
void help()
{
	(void)printf("    ************************************************************************\n");
	(void)printf("    ********************        filedisp        ****************************\n");
	(void)printf("    *    You may have arguments in any order, however you can only         *\n");
 	(void)printf("    *    use at most all 4 (including the ./fileisp).                      *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    *    The proper format:                                                *\n");
	(void)printf("    *   <souceOfInputFiles> | ./fileisp -<option> --version --help         *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    *    --help or -h     : Shows you information about filecnt            *\n");
	(void)printf("    *    --version or -v  : Shows you the current version of filecnt       *\n");
	(void)printf("    *    -d               : Will display the input line which has the      *\n");
	(void)printf("    *                       word \"directories\"                             *\n");
	(void)printf("    *    -f               : Will display the input line which has the      *\n");
	(void)printf("    *                       word \"files\"                                   *\n");
	(void)printf("    *    -b               : Will display the input line which has the      *\n");
	(void)printf("    *                       word \"bytes\"                                   *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    ************        NO WARRANTY USE AT YOUR OWN RISK!       ************\n");
	(void)printf("    ************************************************************************\n");
}

