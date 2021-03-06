//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// table_metric.cpp
//
// Identification: src/statistics/table_metric.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "statistics/table_metric.h"
#include "catalog/catalog.h"
#include "storage/data_table.h"

namespace peloton {
namespace stats {

TableMetric::TableMetric(MetricType type, oid_t database_id, oid_t table_id)
    : AbstractMetric(type), database_id_(database_id), table_id_(table_id) {
  auto table =
      catalog::Catalog::GetInstance()->GetTableWithOid(database_id, table_id);
  if (table == nullptr) {
    table_name_ = "";
  } else {
    table_name_ = table->GetName();
    for (auto& ch : table_name_) ch = toupper(ch);
  }
}

void TableMetric::Aggregate(AbstractMetric& source) {
  assert(source.GetType() == TABLE_METRIC);

  TableMetric& table_metric = static_cast<TableMetric&>(source);
  table_access_.Aggregate(table_metric.GetTableAccess());
}

}  // namespace stats
}  // namespace peloton
