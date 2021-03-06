//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// limit_plan.h
//
// Identification: src/include/planner/limit_plan.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "abstract_plan.h"
#include "common/types.h"

namespace peloton {
namespace planner {

/**
 * @brief	Limit (with Offset) plan node.
 * IMPORTANT: now only works on logical_tile and returns with the same schema as
 * the input.
 */
class LimitPlan : public AbstractPlan {
 public:
  LimitPlan(const LimitPlan &) = delete;
  LimitPlan &operator=(const LimitPlan &) = delete;
  LimitPlan(LimitPlan &&) = delete;
  LimitPlan &operator=(LimitPlan &&) = delete;

  LimitPlan(size_t limit, size_t offset) : limit_(limit), offset_(offset) {}

  // Accessors
  size_t GetLimit() const { return limit_; }

  size_t GetOffset() const { return offset_; }

  inline PlanNodeType GetPlanNodeType() const { return PLAN_NODE_TYPE_LIMIT; }

  const std::string GetInfo() const { return "Limit"; }

  void SetParameterValues(UNUSED_ATTRIBUTE std::vector<common::Value *>* values) { };

  std::unique_ptr<AbstractPlan> Copy() const {
    return std::unique_ptr<AbstractPlan>(new LimitPlan(limit_, offset_));
  }

 private:
  const size_t limit_;   // as LIMIT in SQL standard
  const size_t offset_;  // as OFFSET in SQL standard
};

} /* namespace planner */
} /* namespace peloton */
