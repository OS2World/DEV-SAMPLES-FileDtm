#===================================================================
#
#   filedtm.mak - File Date/Time example
#   Copyright  IBM Corporation 1998
#
#===================================================================

CFLAGS          =      -Gd- -Se -Re -Ss -Ms -Gm+
LFLAGS          =      /NOE /NOD /ALIGN:16 /EXEPACK
LINK            =      icc /B"$(LFLAGS)" $(CFLAGS) -Fe

MTLIBS          =      CPPOM30.LIB + OS2386.LIB

#-------------------------------------------------------------------

HEADERS =

#-------------------------------------------------------------------
#
#   A list of all of the object files
#
#-------------------------------------------------------------------

OBJS = filedtm.obj

ALL_IPF =

#-------------------------------------------------------------------
#   This section lists all files to be built by  make.  The
#   makefile builds the executable as well as its associated help
#   file.
#-------------------------------------------------------------------
all: filedtm.exe

#-------------------------------------------------------------------
#   Dependencies
#     This section lists all object files needed to be built for the
#     application, along with the files it is dependent upon (e.g.
#     its source and any header files).
#-------------------------------------------------------------------

filedtm.obj:   filedtm.c $(HEADERS)

filedtm.exe: $(OBJS) filedtm.def
   -$(CREATE_PATH)
   $(LINK) $@ filedtm.def $(MTLIBS) $(OBJS)

clean :
        @if exist *.obj del *.obj
        @if exist *.dll del *.dll
        @if exist *.exe del *.exe
