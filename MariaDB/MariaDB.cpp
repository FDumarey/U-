#include <Core/Core.h>
#include <MySql/MySql.h>
#include <iostream>

using namespace Upp;
using namespace std;

#define SCHEMADIALECT <MySql/MySqlSchema.h> //using the MySQL schema definitions
#define MODEL <MariaDB/schema.sch> //your schema file within MyApps
#include <Sql/sch_header.h>
#include <Sql/sch_source.h>
#include <Sql/sch_schema.h>

CONSOLE_APP_MAIN
{
	char input;
	cout << "Demo application on MariaDB database\n";
	cin >> input;
	
	MySqlSession session;
	if(session.Connect("root", "password", "test", "synology", 3307)) //user, password, database name, host, port
	{
		cout << "Connected to database\n";
		cin >> input;
		
		SQL = session; //SQL is a global variable, ok if you work with one database in project
		
		SqlSchema sch(MY_SQL); //defines a MySQL schema
		All_Tables(sch); //generate SQL scripts for the table design
		
		// create table if needed
		SqlPerformScript(sch.Upgrade()); //updates the schema if needed
		SqlPerformScript(sch.Attributes()); //update the attributes if needed
		SQL.ClearError();
		
		try
		{
			int i;
			for(i=0;i<100;i++)
			{
				SQL & Insert(TEST_TABLE)(VALUE, Uuid::Create().ToString()); //Insert some data & operator = exception handling in code
			}
			Sql sql; //Define a SQL object
			sql * Select(ID, VALUE).From(TEST_TABLE).OrderBy(Descending(ID)).Limit(5); //Selects dat * operator = manual checking for errors
			while(sql.Fetch())
				Cout() << AsString(sql[0]) << ":" << AsString(sql[VALUE]) << "\n"; //if SqlId are defined (or underscores in schema definition) AsString returns value
		}
		catch(SqlExc &ex)
		{
			Cerr() << "ERROR: " << ex << "\n";
			SetExitCode(1);
		}
		
	}
	else
	{
		Cerr() << "ERROR: Unable to connect to the database\n";
		SetExitCode(1);
	}
	
	cout << "End of application\n";
}
