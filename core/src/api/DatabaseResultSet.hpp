// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from database.djinni

#ifndef DJINNI_GENERATED_DATABASERESULTSET_HPP
#define DJINNI_GENERATED_DATABASERESULTSET_HPP

#include <cstdint>
#include <memory>
#ifndef LIBCORE_EXPORT
    #if defined(_MSC_VER) && _MSC_VER <= 1900
       #include <libcore_export.h>
    #else
       #define LIBCORE_EXPORT
    #endif
#endif

namespace ledger { namespace core { namespace api {

class DatabaseError;
class DatabaseResultRow;

/** ResultSet is a cursor over a query result. It allows user to iterate through query rows. */
class DatabaseResultSet {
public:
    virtual ~DatabaseResultSet() {}

    /**
     * Retrieve the current row pointed by the DatabaseResultSet. Return null if there is no row to retrieve.
     * @return The current row
     */
    virtual std::shared_ptr<DatabaseResultRow> getRow() = 0;

    /** Get the number of rows updated by the query (UPDATE, INSERT, DELETE...) */
    virtual int32_t getUpdateCount() = 0;

    /**
     * Get the number of row retrieved
     * @return The number of rows retrieved by the query
     */
    virtual int32_t getRowNumber() = 0;

    /**
     * Returns the number of remaining rows to get before the end of the result set.
     * @return The number of rows remaining rows to get before the end of the result set.
     */
    virtual int32_t available() = 0;

    /**
     * Returns true if the result set has at least one remaining row to get.
     * @return true if the result set has at least one remaining row to get, false otherwise.
     */
    virtual bool hasNext() = 0;

    /**
     * Move the result set to the next available result. This method may fail if there is now further row to fetch.
     * @return Return a result set pointing to the next row.
     */
    virtual std::shared_ptr<DatabaseResultSet> next() = 0;

    /** Close the result set. */
    virtual void close() = 0;

    /** Get the last error that occured on the database. */
    virtual std::shared_ptr<DatabaseError> getError() = 0;
};

} } }  // namespace ledger::core::api
#endif //DJINNI_GENERATED_DATABASERESULTSET_HPP
