//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// parser.cpp
//
// Identification: src/parser/parser.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

/*-------------------------------------------------------------------------
 *
 * parser.cpp
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 *
 *
 *-------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

#include "parser/parser.h"

#include "parser/sql_parser.h"
#include "parser/sql_scanner.h"
#include "common/exception.h"

namespace peloton {
namespace parser {

Parser::Parser(){

}

Parser::~Parser(){

}

SQLStatementList* Parser::ParseSQLString(const char* text) {
  SQLStatementList* result;
  yyscan_t scanner;
  YY_BUFFER_STATE state;

  if (yylex_init(&scanner)) {
    // couldn't initialize
    throw ParserException("Parser :: Error when initializing lexer!\n");
    return NULL;
  }

  state = yy_scan_string(text, scanner);

  if (parser_parse(&result, scanner)) {
    // Returns an error stmt object
    yy_delete_buffer(state, scanner);
    yylex_destroy(scanner);
    return result;
  }

  yy_delete_buffer(state, scanner);
  yylex_destroy(scanner);
  return result;
}

SQLStatementList* Parser::ParseSQLString(const std::string& text) {
  return ParseSQLString(text.c_str());
}

static Parser &Parser::GetInstance(){
  static Parser parser;
  return parser;
}

std::unique_ptr<parser::SQLStatement> Parser::BuildParseTree(const std::string& query_string){
  std::unique_ptr<parser::SQLStatement> res;
  auto stmt  = Parser::ParseSQLString(query_string);

  LOG_INFO("Statements Size -------------> %d" ,stmt->GetStatements().size());
  SQLStatement* first_stmt = nullptr;

  for(auto s : stmt->GetStatements()){
    first_stmt = s;
    break;
  }

  //auto first_stmt = stmt->GetStatement(0);

  std::unique_ptr<parser::SQLStatement> res1(std::move(first_stmt));
  res = std::move(res1);
  return res;
}



}  // End parser namespace
}  // End peloton namespace
