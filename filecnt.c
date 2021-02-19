/***************************************************************************
 *		filecnt		Bridgette Bryant	 PA2	           *
 *					                                   *
 *	This program will be given a path of a directory and outputs	   *
 *	the total number of directories in the given directory, the 	   *
 *	total number of files in the given directory, and the total	   *
 *	number of bytes occupied by all files in the directory.		   *
 *					                                   *
 *	It is created to work along another program called filedisp.	   *
 *	Supports relative pathing, converts them to absolute paths.	   *
 *						                           *
 *	It will utilize recusion to travers the given directory. If 	   *
 *	an entry is a directory is not accessible or is a link to 	   *
 *	another location, then it will skip that entry.			   *
 ***************************************************************************/

/* Some needed libraries: */
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>

/* Defining my functions */
void filecnt(char[501], long int *, long int *,long int *);
int isValidDir(char[501]);
void version();
void help();

/* The driver function */
int main(int argc, char**argv )
{
	/* Some variables */
	long int byteCount = 0;	/* The counted number of bytes */
	long int dirCount = 0;	/* The counted number of directories */
	long int fileCount = 0;	/* The counted number of files */
	char dirName[501];	/* The directory name given by the user */

	int numDirGiven = 0;	// Just in case the user gets tricky and gives multiple directories. */
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
		else if(numDirGiven < 1)
		{
			++numDirGiven;
			/* If the given directory is valid and absolute */
			if(isValidDir(argv[i]) == 0)
			{
				/* Copy the name to dirName and then send it to the filecnt function */
				strcpy(dirName, argv[i]);
				filecnt(dirName, &fileCount, &dirCount, &byteCount);
				/* Print out the results */
				(void)printf("The total number of directories in directory %s\t is: %d\n", dirName, dirCount);
				(void)printf("The total number of files in directory %s\t is: %d\n", dirName, fileCount);
				(void)printf("The total number of bytes occupied by all files in directory %s\t is: %d\n", dirName, byteCount);

			} /* If the given directory is valid and relative */
			else if(isValidDir(argv[i]) == 1)
			{
				strcpy(dirName, argv[i]); /* Set the argument as the directory path */
				char absPath[501]; /* To be used as our absPath */
				char *ptr; /* Used as a pointer */
				ptr = realpath(dirName, absPath); /* Converts the dirName's relative path to the absPath */
				(void)printf("absPath: %s\n", absPath);
				/* Call the count function for the new created path */
				filecnt(absPath, &fileCount, &dirCount, &byteCount);
				/* Print out the results */
				(void)printf("The total number of directories in directory %s\t is: %d\n", dirName, dirCount);
				(void)printf("The total number of files in directory %s\t is: %d\n", dirName, fileCount);
				(void)printf("The total number of bytes occupied by all files in directory  %s\t is: %d\n", dirName, byteCount);
				return (0);
			} /* If the given directory is invalid */
			else
			{
				(void)printf("Invalid input: %s\n", argv[i]);
				return (0);
			}
		}
	}

 	   /* Exit */
 	   return (0);
}

/* Recursively travels through the directory and counts the files/directories */
void filecnt(char givenDir[501], long int * numFile, long int * numDir, long int * numBytes)
{
	char curDir[501];	/* Used for recursion */
	/* Print out the given userInput */
	/*(void)printf("Given Path:\t%s\n", givenDir);*/

	struct dirent *dp;	/* To be used to open the directory */
	DIR *dir = opendir(givenDir); /* Opens the directory */
	FILE *fp = fopen(givenDir, "r"); /* Opens the file (if it is not a directory) */

	/* If it is a valid directory, increment the number of directories */
	if(dir)
	{
		(*numDir)++;
		/*(void)printf("I found a directory!\n");*/
	} /* Check if it is a file */
	else if(fp != NULL)
	{
		/* Increment the number of files */
		(*numFile)++;
		/*(void)printf("I found a file!\n");*/

		/* Get the size of the file */
		fseek(fp, 0L, SEEK_END); /* Get to the end */
		(*numBytes) += ftell(fp); /* Add the amount to the current number of bytes */
		/* Close the file and return to end this recursion branch */
		fclose(fp);
		return;
	}

	/* While we have not reached the end of the directory */
	while ((dp = readdir(dir)) != NULL)
	{
		/* If the name is not '.' or '..' */
		if ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..")))
		{
			/* Copy the current given directory to the created current */
			strcpy(curDir, givenDir);
			/* Concatenate a '/' */
			strcat(curDir, "/");
			/* Concatenate the current directory name */
			strcat(curDir, dp->d_name);

			/* Call the next file count for the new directory path */
			filecnt(curDir, numFile, numDir, numBytes);
		}
	}

	/*(void)printf("numFile: %d\n", *numFile);
	(void)printf("numDir: %d\n", *numDir);
	(void)printf("numBytes: %d\n", *numBytes);*/

	/* Close the file */
	fclose(fp);
	/* Close the directory */
	closedir(dir);

	return;
}

/* Returns -1 if it is an invalid path, 0 if it is an absolute path,
	 and 1 if it is an relative path */
int isValidDir(char path[501])
{
	bool flag = true;	/* Used as a flag when exiting the for loops to determine */
				/* If it made it through the for loop or broke out */
	/* If it only has alphabetical letters and '\' then it is an absolute path */
	for(int i = 0; i < 501; ++i)
	{
		/* If we have reached the end of the string */
		if(path[i] == '\0')
		{
			break;
		}
		/* If we have reached an invalid character for it to be an absolute path */
		if(!(isalpha(path[i]) || path[i] == '/'))
		{
			/* Set flag */
			flag = false;
			/* Break out of for loop */
			break;
		}
	}

	/* If we went through the for loop to verify that it is an absolute path */
	if(flag)
	{
		/* Return 0, it is an absolute path */
		return (0);
	}	/* Otherwise */
	else
	{
		/* Reset the flag */
		flag = true;
	}

	int numSpaces = 0;	// The number of spaces in the given path
	/* Check if the path is a relative path */
	for(int i = 0; i < 501; ++i)
	{
		/* If we have not reached the end of the string */
		if(path[i] != '\0')
		{
			/* Get out of the loop */
			break;
		}
		/* Make sure there are not invalid characters */
		if(!(path[i] != '/' || path[i] != ' ' || isalpha(path[i])))
		{
			/* Break the loop and set the flag */
			flag = false;
			break;
		}
		/* If it is a space */
		if(path[i] == ' ')
		{
			++numSpaces; /* Increment the number of spaces */
		}
	}
	/* Check if we made it through the loop without any invalid chars or invalid num of spaces*/
	if(flag && numSpaces < 2)
	{
		/* Return 1 */
		return (1);
	}

	/* Otherwise it is an invalid path */
	return (-1);
}

/* Displays the version of the program */
void version()
{
	(void)printf("version:\tfilecnt\t1.0.0\tBridgette Bryant\t2/25/2020\n");
}

/* Displays information to help users */
void help()
{
	(void)printf("    ************************************************************************\n");
	(void)printf("    ********************        filecnt        *****************************\n");
	(void)printf("    *    You may have arguments in any order, however you can only         *\n");
 	(void)printf("    *    use at most all 4 (including the ./filecnt).                      *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    *    The proper format:                                                *\n");
	(void)printf("    *    ./filecnt <directory_path> --version --help                       *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    *    --help or -h     : Shows you information about filecnt            *\n");
	(void)printf("    *    --version or -v  : Shows you the current version of filecnt       *\n");
	(void)printf("    *    <directory_path> : Enter your path to be used by the program.     *\n");
	(void)printf("    *                       It will display the number of directories,     *\n");
	(void)printf("    *                       files, and bytes in the given directory path.  *\n");
	(void)printf("    *                                                                      *\n");
	(void)printf("    ************        NO WARRANTY USE AT YOUR OWN RISK!       ************\n");
	(void)printf("    ************************************************************************\n");
}

