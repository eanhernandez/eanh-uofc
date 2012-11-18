/*

Ean Hernandez - username: eanh - cspp51081 - lab 3 - 10-20-2010

estat.c, a program that does some of what stat does.

*/

#define _GNU_SOURCE
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

char* getPerm(char n);
void printSymlink(char** s);
void printTimeData(time_t t,long ns, char e);

int main(int argc, char* args[])
{
   struct stat s;
   lstat(args[1],&s);
   //char buffer[256];

   // prints file line
   printf("  file: `%s'", args[1]);
   // handles extra details for symlinks
   if (S_ISLNK(s.st_mode)){ printSymlink(args); } printf("\n");

   // prints size, blocks, io blocks
   printf("  size: %ld          ", (long) s.st_size);
   printf("blocks: %lld          ", (long long) s.st_blocks);
   printf("io block: %ld      ", (long) s.st_blksize);

   // this finds out what file type we are dealing with, prints it,
   // and then takes the opportunity to set ft with this data so
   // we can correctly display it later
   char ft ='?';              
   if (S_ISDIR(s.st_mode)) {printf("directory\n"); ft='d';}
   if (S_ISLNK(s.st_mode)) {printf("symbolic link\n"); ft='l';}
   if (S_ISREG(s.st_mode)) {printf("regular file\n"); ft='-';}

   // prints device, inode, links line
   printf("device: %xh/%dd       ",(int)s.st_dev,(int)s.st_dev);
   printf("Inode: %ld      ", (long) s.st_ino);
   printf("links: %ld\n", (long) s.st_nlink);

   // stores mode in the string Perm so that we can work with it
   char *Perms; asprintf(&Perms, "%lo", (unsigned long)s.st_mode);
   // prints last 4 characters of the mode for the access field
   printf("access: (%c%c%c%c/",
      Perms[strlen(Perms)-4], 
      Perms[strlen(Perms)-3], 
      Perms[strlen(Perms)-2], 
      Perms[strlen(Perms)-1]
      );

   // prints file type (l,d,-)
   printf("%c",ft);           
   // uses the last 3 chars of the mode to get wrx representation
   printf("%s",getPerm(Perms[strlen(Perms)-3]));
   printf("%s",getPerm(Perms[strlen(Perms)-2]));
   printf("%s",getPerm(Perms[strlen(Perms)-1]));
   printf(")   ");

   // print the owners username
   struct passwd* userInfo;
   userInfo = getpwuid (s.st_uid);
   printf("uid: (%d   /   %s)",(int) s.st_uid, userInfo->pw_name);

   // print the owners group
   struct group * groupInfo;   
   groupInfo = getgrgid (s.st_gid);
   printf("    gid: (%ld  /  %s)", (long) s.st_gid,groupInfo->gr_name); printf("\n");

   // prints the access, modify and change times, formatted
   printTimeData(s.st_atime,s.st_atim.tv_nsec, 'a');
   printTimeData(s.st_mtime,s.st_mtim.tv_nsec, 'm');
   printTimeData(s.st_ctime,s.st_ctim.tv_nsec, 'c');

   exit(0);
}

// this function takes a numeric char representing a particular position 
// of the mode and returns the appropriate alphanumeric permissions
char* getPerm(char n)
{
   if (48==(int)n) { return "---";}
   if (49==(int)n) { return "--x";}
   if (50==(int)n) { return "-w-";}
   if (51==(int)n) { return "-wx";}
   if (52==(int)n) { return "r--";}
   if (53==(int)n) { return "r-x";}
   if (54==(int)n) { return "rw-";}
   if (55==(int)n) { return "rwx";}
   return "!!!";  // error case
}

// this function looks up the file pointed to by the symlink named s[1]
// and prints an arrow and the file's name for the symlink case
void printSymlink(char** s)
{
   struct stat s2;
   char buffer2[25];
   stat(s[1],&s2);
   printf(" --> ");
   readlink(s[1], buffer2, 25);
   printf("`%s'",buffer2);
}

// this function takes in a time_t and long representing an access/modify/change
// time and a char representing the event (a/m/c) and prints it the same way that 
// stat does
void printTimeData(time_t t,long ns, char e)
{
   char buffer[256];
   switch (e)
   {
      case 'a' : printf("access: "); break;
      case 'm' : printf("modify: "); break;
      case 'c' : printf("change: "); break;
      default  : printf("??????: "); break;
   }

   strftime (buffer, 256,"%Y-%m-%d %H:%M:%S.", localtime(&t)); printf(buffer);
   printf("%09ld",ns);
   strftime(buffer, 256," %z",localtime(&t));printf(buffer);
   printf("\n");
}

