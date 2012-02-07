#include <iostream>
#include "libxml++/libxml++.h"

int validate(std::string schemafilepath, std::string docfilepath)
{
    // convert to unicode
    Glib::ustring schema( schemafilepath );
    Glib::ustring doc( docfilepath );

    xmlpp::DomParser parser(doc);
    xmlpp::SchemaValidator validator(schema);
    
    try
    {
        validator.validate( parser.get_document() );
        return 0;
    }
    catch( const xmlpp::exception& )
    {
        return 1;
    }
}

int main(int argc, char* argv[])
{
    int failures = 0;
    if( argc < 3 )
    {
        // print usage
        std::cout << "usage: \"" << argv[0] << " schema.xsd doc1.xml [doc2.xml ...]" << std::endl;
        return 1;
    }
    else
    {
        // validate each file
        for( int n=2; n<argc; n++ )
        {
            std::string verdict;
            if( validate(argv[1], argv[n])==0 )
            {
                verdict = "yes";
            }
            else
            {
                verdict = "no";
                failures++;
            }
            std::cout << argv[n] << " conforms to " << argv[1] << "? " << verdict << std::endl;
        }
    }
    return failures;
}
