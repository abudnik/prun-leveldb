#include <memory>
#include <boost/property_tree/ptree.hpp>
#include "history.h"
#include "leveldb/db.h"


class DbLevel : public common::IHistory
{
    typedef std::unique_ptr< leveldb::DB > DbPtr;

public:
    virtual void Initialize( const std::string &configPath );
    virtual void Shutdown();

    virtual void Put( const std::string &key, const std::string &value );
    virtual void Delete( const std::string &key );

    typedef void (*GetCallback)( const std::string &key, const std::string &value );
    virtual void GetAll( GetCallback callback );

private:
    void ParseConfig( const std::string &configPath );

private:
    DbPtr db_;
    boost::property_tree::ptree config_;
};
