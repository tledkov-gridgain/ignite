/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ignite/impl/binary/binary_common.h>

#include "ignite/odbc/type_traits.h"
#include "ignite/odbc/connection.h"
#include "ignite/odbc/message.h"
#include "ignite/odbc/query/foreign_keys_query.h"

namespace ignite
{
    namespace odbc
    {
        namespace query
        {
            ForeignKeysQuery::ForeignKeysQuery(diagnostic::Diagnosable& diag, Connection& connection,
                const std::string& primaryCatalog, const std::string& primarySchema,
                const std::string& primaryTable, const std::string& foreignCatalog,
                const std::string& foreignSchema, const std::string& foreignTable) :
                Query(diag),
                connection(connection),
                primaryCatalog(primaryCatalog),
                primarySchema(primarySchema),
                primaryTable(primaryTable),
                foreignCatalog(foreignCatalog),
                foreignSchema(foreignSchema),
                foreignTable(foreignTable),
                executed(false),
                columnsMeta()
            {
                using namespace ignite::impl::binary;
                using meta::ColumnMeta;

                columnsMeta.reserve(14);

                const std::string sch("");
                const std::string tbl("");

                columnsMeta.push_back(ColumnMeta(sch, tbl, "PKTABLE_CAT",   SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "PKTABLE_SCHEM", SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "PKTABLE_NAME",  SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "PKCOLUMN_NAME", SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "FKTABLE_CAT",   SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "FKTABLE_SCHEM", SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "FKTABLE_NAME",  SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "FKCOLUMN_NAME", SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "KEY_SEQ",       SqlTypeName::smallintType, IGNITE_TYPE_SHORT));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "UPDATE_RULE",   SqlTypeName::smallintType, IGNITE_TYPE_SHORT));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "DELETE_RULE",   SqlTypeName::smallintType, IGNITE_TYPE_SHORT));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "FK_NAME",       SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "PK_NAME",       SqlTypeName::varcharType,  IGNITE_TYPE_STRING));
                columnsMeta.push_back(ColumnMeta(sch, tbl, "DEFERRABILITY", SqlTypeName::smallintType, IGNITE_TYPE_SHORT));
            }

            ForeignKeysQuery::~ForeignKeysQuery()
            {
                // No-op.
            }

            SqlResult ForeignKeysQuery::Execute()
            {
                executed = true;

                return SQL_RESULT_SUCCESS;
            }

            const meta::ColumnMetaVector & ForeignKeysQuery::GetMeta() const
            {
                return columnsMeta;
            }

            SqlResult ForeignKeysQuery::FetchNextRow(app::ColumnBindingMap & columnBindings)
            {
                if (!executed)
                    return SQL_RESULT_ERROR;

                return SQL_RESULT_NO_DATA;
            }

            SqlResult ForeignKeysQuery::Close()
            {
                executed = false;

                return SQL_RESULT_SUCCESS;
            }

            bool ForeignKeysQuery::DataAvailable() const
            {
                return false;
            }
            int64_t ForeignKeysQuery::AffectedRows() const
            {
                return 0;
            }
        }
    }
}

