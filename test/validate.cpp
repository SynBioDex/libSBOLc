#include <iostream>
#include "libxml++/libxml++.h"

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
        // create validator from schema
        Glib::ustring schema( argv[1] );
        xmlpp::SchemaValidator validator(schema);

        // validate each file against it
        for( int n=2; n<argc; n++ )
        {
            Glib::ustring doc( argv[n] ); // convert path to unicode
            xmlpp::DomParser parser(doc); // parse document
            std::string verdict;          // whether doc validated
            try
            {
                validator.validate( parser.get_document() );
                verdict = "yes";
            }
            catch( const xmlpp::exception& )
            {
                verdict = "no";
                failures++;
            }
            std::cout << argv[n] << " conforms to " << schema << "? " << verdict << std::endl;
        }
    }
    return failures;
}
