/* -----------------------------------------------------------------------
   Header file for NMEA string parser
   Copyright 2006-2008 by Brian C. Lane <bcl@brianlane.com>
   All Rights Reserved
   ----------------------------------------------------------------------- */
/*! \file
    \brief Header file for nmea.c
    \author Brian C. Lane <bcl@brianlane.com>

    Definitions and structures for the NMEA sentence parser

*/
#ifndef _AIS_NMEA_H_
#define _AIS_NMEA_H_

#include "portable.h"

#define MAX_NMEA_LENGTH 255
#define MAX_NMEA_FIELDS 50
#define START 0
#define END 1
#define DONE 2

/** NMEA parser state structure
 */
typedef struct {
  unsigned char search;          //!< State of the search: START, END or DONE
  char *field[MAX_NMEA_FIELDS];  //!< Pointers to fields in the buffer
  char str[MAX_NMEA_LENGTH];     //!< Incoming NMEA 0183 string
  unsigned long str_len;         //!< Number of bytes in str
} nmea_state;

/* Prototypes */
unsigned int check_nmea_checksum(char *buffer, unsigned char *checksum);
unsigned int nmea_checksum(char *buffer, unsigned char *checksum);
char *find_nmea_start(char *buffer);
char ahextobin(char *c);
char *nmea_next_field(char *p);
unsigned int nmea_uint(char *p);
char *nmea_copy_field(char *dest, char *src, int len);

#endif
