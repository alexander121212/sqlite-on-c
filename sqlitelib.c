#include "sqlitelib.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

int IsDbValid(SqliteDb *db)
{
	if (db == NULL) {
		fprintf(stderr, "DB is null! \n");
		return -UNSUCCESS;
	}
	if (!db->name) {
		fprintf(stderr, "DB NAME is null\n");
		return -UNSUCCESS;
	}

	return SUCCESS;
}

const char* GetSqliteVersion(void)
{
	return sqlite3_libversion();
}

int ConnectToDb(SqliteDb *db)
{
	int rc = 0;


	if(IsDbValid(db)){
		return -UNSUCCESS;
	}

	rc = sqlite3_open(db->name, &db->sqldb);
	if (rc) {
		fprintf(stderr, "Can't open db: %s \n", db->name);
		return -UNSUCCESS;
	} 

	return SUCCESS;
}

void DisconnectFromDb(SqliteDb *db)
{
	sqlite3_close(db->sqldb);
}

int ExecuteSqlCommand(SqliteDb *db)
{
	int rc, result;
	char	*zErrMsg = 0;

	if(IsDbValid(db) == -UNSUCCESS){
		return -UNSUCCESS;
	}

	result = ConnectToDb(db);	
	if (result == -UNSUCCESS) {
		return -UNSUCCESS;
	}

	if (db->query == NULL) {
		fprintf(stderr, "Query is empty: %s\n", zErrMsg);
		return -UNSUCCESS;		
	}

	rc = sqlite3_exec(db->sqldb, db->query, callback, 0, &zErrMsg);
	if(rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	        sqlite3_free(zErrMsg);
		DisconnectFromDb(db);
		return -UNSUCCESS;
	}

	DisconnectFromDb(db);

	return SUCCESS;
}

