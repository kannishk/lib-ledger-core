// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from database.djinni

#ifndef DJINNI_GENERATED_DATABASESTATEMENT_HPP
#define DJINNI_GENERATED_DATABASESTATEMENT_HPP

#include <cstdint>
#include <memory>
#include <string>
#ifndef LIBCORE_EXPORT
    #if defined(_MSC_VER) && _MSC_VER <= 1900
       #include <libcore_export.h>
    #else
       #define LIBCORE_EXPORT
    #endif
#endif

namespace ledger { namespace core { namespace api {

class DatabaseBlob;
class DatabaseColumn;
class DatabaseResultSet;

/**
 * A wrapper object around prepared SQL statements. lib-ledger-core will use placeholders when it needs to pass
 * parameters to a query. It will then  bind each parameter at a given position to a given value.
 */
class DatabaseStatement {
public:
    virtual ~DatabaseStatement() {}

    /**
     * Bind the designated parameter to the given 16bit integer value.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindShort(int32_t pos, int16_t value) = 0;

    /**
     * Bind the designated parameter to the given 32bit integer value.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindInt(int32_t pos, int32_t value) = 0;

    /**
     * Bind the designated parameter to the given 64bit integer value.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindLong(int32_t pos, int64_t value) = 0;

    /**
     * Bind the designated parameter to the given 32bit floating point number value.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindFloat(int32_t pos, float value) = 0;

    /**
     * Bind the designated parameter to the given 64bit floating point number value.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindDouble(int32_t pos, double value) = 0;

    /**
     * Bind the designated parameter to the given string.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindString(int32_t pos, const std::string & value) = 0;

    /**
     * Bind the designated parameter to the given BLOB.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindBlob(int32_t pos, const std::shared_ptr<DatabaseBlob> & value) = 0;

    /**
     * Bind the designated parameter to the NULL value in SQL.
     * @param pos The position of the parameter in the query
     * @param value The value to bind
     */
    virtual void bindNull(int32_t pos) = 0;

    /**
     * Describe the metadata attached to the designated column (e.g. data type, column name...)
     * @return Column metadata descriptor
     */
    virtual std::shared_ptr<DatabaseColumn> describeColumn(int32_t colNum) = 0;

    /**
     * Get the number of column that will be available into the result row (e.g. "SELECT name, age FROM USERS"
     * would return 2).
     * @return The number of the columns available in the result
     */
    virtual int32_t getColumnCount() = 0;

    /**
     * Execute the statement with the past bound values.
     * @return The result of the execution of the statement on the database.
     */
    virtual std::shared_ptr<DatabaseResultSet> execute() = 0;

    /** Reset all bindings. This call is used before reusing a statement instance in order to repeat it multiple time. */
    virtual void reset() = 0;

    /** Close the statement and release all allocated resources. The statement shouldn't be used after this call. */
    virtual void close() = 0;
};

} } }  // namespace ledger::core::api
#endif //DJINNI_GENERATED_DATABASESTATEMENT_HPP
