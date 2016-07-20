#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define SUCCESS		0
#define UNSUCCESS 	1

#define MAX_NAME_LEN	2048
#define MAX_QUERY_LEN	2048
typedef struct _SqliteDb {
		char	 name[MAX_NAME_LEN];
		char	 query[MAX_QUERY_LEN];
		sqlite3* sqldb;
} SqliteDb;


int callback(void *NotUsed, int argc, char **argv, char **azColName);
int IsDbValid(SqliteDb *db);
const char* GetSqliteVersion(void);
int ConnectToDb(SqliteDb *db);
void DisconnectFromDb(SqliteDb *db);
int ExecuteSqlCommand(SqliteDb *db);
