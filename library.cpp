#include <iostream>
#include <sstream>
#include <pqxx/pqxx>

namespace
{
    const std::string dbname = "Wtf";
    const std::string dbuser = "Wtf";
    const std::string dbpass = "Wtf";
}

int main()
{
    std::cout << "Test" << std::endl;
    
    try
    {
        std::ostringstream ss;
        ss << "dbname = " << dbname << " user = " << dbuser << " password = " << dbpass << " hostaddr = 127.0.0.1 port = 5432";
        
        pqxx::connection connection( ss.str() );
        if( connection.is_open() )
        {
            std::cout << "Opened database successfully: " << connection.dbname() << std::endl;
        }
        else
        {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }
        connection.close();
    } catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
