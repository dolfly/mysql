/* Copyright (C) 2003 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <common.h>
#define SQL_MAXIMUM_MESSAGE_LENGTH 200

using namespace std;

SQLHDBC     hdbc;
SQLHSTMT    hstmt;
SQLHENV     henv;
SQLHDESC    hdesc;
SQLRETURN   retcode, SQLSTATEs;

SQLCHAR Sqlstate[5];

SQLINTEGER    NativeError;
SQLSMALLINT   i, MsgLen;
SQLCHAR   Msg[SQL_MAXIMUM_MESSAGE_LENGTH];
       
void SQLMoreResults_DisplayError(SQLSMALLINT HandleType, SQLHSTMT InputHandle);

int SQLMoreResultsTest()
{

  /* hstmt */
  retcode = SQLMoreResults(hstmt);

  if (retcode == SQL_INVALID_HANDLE)
  ndbout << "Handle Type is SQL_HANDLE_STMT, but string SQL_INVALID_HANDLE still appeared. Please check programm" << endl;

  if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
  SQLMoreResults_DisplayError(SQL_HANDLE_STMT, hstmt);

  /* henv */
  retcode = SQLMoreResults(henv);

  if (retcode == SQL_SUCCESS_WITH_INFO || retcode == SQL_SUCCESS)
  ndbout << "Handle Type is SQL_HANDLE_ENV, but string SQL_SUCCESS_WITH_INFO still appeared. Please check programm" << endl;
  //  SQLMoreResults_DisplayError(SQL_HANDLE_ENV, henv);

  /* hdbc */
  retcode = SQLMoreResults(hdbc);

  if (retcode == SQL_SUCCESS_WITH_INFO || retcode == SQL_SUCCESS)
  ndbout << "Handle Type is SQL_HANDLE_DBC, but string SQL_SUCCESS_WITH_INFO still appeared. Please check programm" << endl;
  //  SQLMoreResults_DisplayError(SQL_HANDLE_DBC, hdbc);

  /* hdesc */
  retcode = SQLMoreResults(hdesc);

  if (retcode == SQL_SUCCESS_WITH_INFO || retcode == SQL_SUCCESS)
  ndbout << "Handle Type is SQL_HANDLE_DESC, but string SQL_SUCCESS_WITH_INFO still appeared. Please check programm" << endl;
  //  SQLMoreResults_DisplayError(SQL_HANDLE_DESC, hdesc);

  return 0;

 }


void SQLMoreResults_DisplayError(SQLSMALLINT HandleType, SQLHSTMT InputHandle)
{
     i = 1;
     while ((SQLSTATEs = SQLGetDiagRec(HandleType, InputHandle, i, 
             Sqlstate, &NativeError, Msg, sizeof(Msg), 
             &MsgLen)) != SQL_NO_DATA)                   {

     ndbout << "the HandleType is:" << HandleType << endl;
     ndbout << "the InputHandle is :" << InputHandle << endl;
     ndbout << "the output state is:" << (char *)Sqlstate << endl; 

     i ++;
                                                         }

}



