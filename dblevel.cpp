#define BOOST_SPIRIT_THREADSAFE

#include "dblevel.h"
#include <boost/property_tree/json_parser.hpp>

void DbLevel::Initialize( const std::string &configPath )
{
    ParseConfig( configPath );
    std::string dbPath = config_.get<std::string>( "db_path" );

    leveldb::DB *db = nullptr;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open( options, dbPath.c_str(), &db );
    if ( !status.ok() )
        throw std::logic_error( status.ToString() );

    db_.reset( db );
}

void DbLevel::Shutdown()
{
    db_.reset();
    config_.clear();
}

void DbLevel::Put( const std::string &key, const std::string &value )
{
    leveldb::Status status = db_->Put( leveldb::WriteOptions(), key, value );
    if ( !status.ok() )
        throw std::logic_error( status.ToString() );
}

void DbLevel::Delete( const std::string &key )
{
    leveldb::Status status = db_->Delete( leveldb::WriteOptions(), key );
    if ( !status.ok() )
        throw std::logic_error( status.ToString() );
}

void DbLevel::GetAll( GetCallback callback )
{
    std::unique_ptr< leveldb::Iterator > it( db_->NewIterator( leveldb::ReadOptions() ) );
    for( it->SeekToFirst(); it->Valid(); it->Next() )
    {
        callback( it->key().ToString(), it->value().ToString() );
    }

    if ( !it->status().ok() )
        throw std::logic_error( it->status().ToString() );
}

void DbLevel::ParseConfig( const std::string &configPath )
{
    std::ifstream file( configPath.c_str() );
    if ( !file.is_open() )
        throw std::logic_error( "DbLevel::ParseConfig: couldn't open " + configPath );

    boost::property_tree::read_json( file, config_ );
}

common::IHistory *CreateHistory( int interfaceVersion )
{
    return interfaceVersion == common::HISTORY_VERSION ?
        new DbLevel : nullptr;
}

void DestroyHistory( const common::IHistory *history )
{
    delete history;
}
