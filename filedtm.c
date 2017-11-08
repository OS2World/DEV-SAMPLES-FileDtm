/*  filedtm.c

    This code segment illustrates the file system "Date Last Accessed",
    "Creation Date", and "Date Last Written".

    The "Date Last Accessed" value can be useful for locating stale or
    unused files, especially on large LAN file storage systems where
    additional disk space may be needed.

*/

/* (c) Copyright IBM Corp. 1998  All rights reserved.

This sample program is owned by International Business Machines
Corporation or one of its subsidiaries ("IBM") and is copyrighted
and licensed, not sold.

You may copy, modify, and distribute this sample program in any
form without payment to IBM,  for any purpose including developing,
using, marketing or distributing programs that include or are
derivative works of the sample program.

The sample program is provided to you on an "AS IS" basis, without
warranty of any kind.  IBM HEREBY  EXPRESSLY DISCLAIMS ALL
WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE.

Some jurisdictions do not allow for the exclusion or limitation of
implied warranties, so the above limitations or exclusions may not
apply to you.  IBM shall not be liable for any damages you suffer
as a result of using, modifying or distributing the sample program
or its derivatives.

Each copy of any portion of this sample program or any derivative
work,  must include a the above copyright notice and disclaimer of
warranty.
*/


#define INCL_DOSFILEMGR   /* File Manager values */
#define INCL_DOSERRORS    /* Error values */
#include <os2.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int main(argc, argv, envp)
   int argc;
   char *argv[];
   char *envp[];
  {
    APIRET  rc         = NO_ERROR; /* Return code */
    FILESTATUS PBuff;
    char       FilePath[256];

    if (argc == 2)
        {
        strcpy( FilePath, argv[1]);
        }
    else
        {
        printf("Syntax: filedtm <filepathname>\n");
        return 2;
        }

    rc = DosQueryPathInfo( FilePath,
                           FIL_STANDARD,
                           &PBuff,
                           sizeof PBuff);

    if (NO_ERROR == rc)
        {
        printf(
            "Filename:          %s\n", FilePath);
        /* Note that Creation Date is 0, if file is on a FAT drive */
        printf(
            "Creation Date    = %04u-%02u-%02u %02u:%02u:%02u\n",
            PBuff.fdateCreation.year+1980,
            PBuff.fdateCreation.month,
            PBuff.fdateCreation.day,
            PBuff.ftimeCreation.hours,
            PBuff.ftimeCreation.minutes,
            PBuff.ftimeCreation.twosecs);
        /* Note that Last Access Date is 0, if file is on a FAT drive */
        printf(
            "Last Access Date = %04u-%02u-%02u %02u:%02u:%02u\n",
            PBuff.fdateLastAccess.year+1980,
            PBuff.fdateLastAccess.month,
            PBuff.fdateLastAccess.day,
            PBuff.ftimeLastAccess.hours,
            PBuff.ftimeLastAccess.minutes,
            PBuff.ftimeLastAccess.twosecs);
        printf(
            "Last Write Date  = %04u-%02u-%02u %02u:%02u:%02u\n",
            PBuff.fdateLastWrite.year+1980,
            PBuff.fdateLastWrite.month,
            PBuff.fdateLastWrite.day,
            PBuff.ftimeLastWrite.hours,
            PBuff.ftimeLastWrite.minutes,
            PBuff.ftimeLastWrite.twosecs);
        }
    else
        {
        switch (rc)
          {
            case ERROR_FILE_NOT_FOUND:
                    printf("File Not Found: %s\n", FilePath);
                    break;
            case ERROR_PATH_NOT_FOUND:
                    printf("Invalid Path: %s\n", FilePath);
                    break;
            case ERROR_SHARING_VIOLATION:
                    printf("Sharing Violation: %s\n", FilePath);
                    break;
            default:
                    printf("File Error %u: %s\n", rc, FilePath);
                    break;
          }
        }

    return NO_ERROR;

 }