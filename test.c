#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "sqlitelib.h"


int TestExecCommand(const char *query, unsigned int size)
{
	
	SqliteDb* db = NULL;
	int rc;
	char dbname[] = "test.db";

	db = (SqliteDb*) malloc(sizeof(SqliteDb));
	if (db == NULL) {
		fprintf(stderr, "NO memory allocated!");
		exit(-1);
	}
	
	strncpy(db->name,  dbname, sizeof(dbname));
	strncpy(db->query, query,  size);
	
	rc =  ExecuteSqlCommand(db);
	if(rc == -UNSUCCESS){
		fprintf(stderr, "Cannot execute query %s \n", db->query);
		return -UNSUCCESS;
	}

	return SUCCESS;
}

void TestHelp(char *query, unsigned int size,  char *testName)
{
	int rc;
	char *ourQuery = NULL;

	ourQuery = (char*) malloc(size);
	if (ourQuery == NULL) {
		fprintf(stderr, "%s is FAILED  NOMEM\n", testName);
		return;
	}

 
	strncpy(ourQuery, query, size);

	rc = TestExecCommand(ourQuery, size);
	if (rc) {
		fprintf(stderr, "%s is FAILED \n", testName);
	} else {
		fprintf(stderr, "%s is SUCCESSFULLY finished \n", testName);
	}

	free(ourQuery);
}

void TestCreateTable(void)
{
	char query[] ="CREATE TABLE COMPANY("  \
		      "ID INT PRIMARY KEY     NOT NULL," \
		      "NAME           TEXT    NOT NULL," \
		      "AGE            INT     NOT NULL," \
		      "ADDRESS        CHAR(50)," \
		      "SALARY         REAL );"; 

	TestHelp(query, sizeof(query), "TestCreateTable");
}


void TestInsertTable(void)
{
	char query[] = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
                	"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
          		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";	 

	TestHelp(query, sizeof(query), "TestInsertTable");
}


void TestSelectTable(void)
{
	char query[] = "SELECT * from COMPANY";

	TestHelp(query, sizeof(query), "TestSelectTable");
}


void TestUpdateTable(void)
{
	char query[] = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
			         "SELECT * from COMPANY";

	TestHelp(query, sizeof(query), "TestUpdateTable");
}

void TestDeleteTable(void)
{
	char query[] ="DELETE from COMPANY where ID=2; " \
		               "SELECT * from COMPANY";

	TestHelp(query, sizeof(query), "TestDeleteTable");
}

void TestConnectDb(void)
{
	SqliteDb* db = NULL;
	int rc;
	char dbname[] = "test.db";
	db = (SqliteDb*) malloc(sizeof(SqliteDb));
	if (db == NULL) {
		fprintf(stderr, "NO memory allocated!");
		exit(-1);
	}
	
	strncpy(db->name, dbname, sizeof(dbname));

	rc = ConnectToDb(db);
	if(rc) {
		fprintf(stderr, "NOT connected !");
		exit(-1);
	}

	free(db);
}

void RunTests(void)
{
	TestConnectDb();
	TestCreateTable();
	TestSelectTable();
	TestInsertTable();
	TestUpdateTable();
	TestDeleteTable();
}

int main(void)
{
	RunTests();
    return 0;
}
