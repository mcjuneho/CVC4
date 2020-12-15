/*********************                                                        */
/*! \file symbol_manager.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief The symbol manager
 **/

#include "cvc4_public.h"

#ifndef CVC4__EXPR__SYMBOL_MANAGER_H
#define CVC4__EXPR__SYMBOL_MANAGER_H

#include <map>
#include <memory>
#include <set>
#include <string>

#include "api/cvc4cpp.h"
#include "expr/symbol_table.h"

namespace CVC4 {

/**
 * Symbol manager, which manages:
 * (1) The symbol table used by the parser,
 * (2) Information related to the (! ... :named s) feature in SMT-LIB version 2.
 *
 * Like SymbolTable, this class currently lives in src/expr/ since it uses
 * context-dependent data structures.
 */
class CVC4_PUBLIC SymbolManager
{
 public:
  SymbolManager(api::Solver* s);
  ~SymbolManager();
  /** Get the underlying symbol table */
  SymbolTable* getSymbolTable();
  //---------------------------- named expressions
  /** Set name of term t to name
   *
   * @param t The term to name
   * @param name The given name
   * @param isAssertion Whether t is being given a name in an assertion
   * context. In particular, this is true if and only if there was an assertion
   * command of the form (assert (! t :named name)).
   * @return true if the name was set. This method may return false if t
   * already has a name.
   */
  bool setExpressionName(api::Term t,
                         const std::string& name,
                         bool isAssertion = false);
  /** Get name for term t
   *
   * @param t The term
   * @param name The argument to update with the name of t
   * @param isAssertion Whether we only wish to get the assertion name of t
   * @return true if t has a name. If so, name is updated to that name.
   * Otherwise, name is unchanged.
   */
  bool getExpressionName(api::Term t,
                         std::string& name,
                         bool isAssertion = false) const;
  /**
   * Convert list of terms to list of names. This adds to names the names of
   * all terms in ts that has names. Terms that do not have names are not
   * included.
   *
   * Notice that we do not distinguish what terms among those in ts have names.
   * If the caller of this method wants more fine-grained information about what
   * specific terms had names, then use the more fine grained interface above,
   * per term.
   *
   * @param ts The terms
   * @param names The name list
   * @param areAssertions Whether we only wish to include assertion names
   */
  void getExpressionNames(const std::vector<api::Term>& ts,
                          std::vector<std::string>& names,
                          bool areAssertions = false) const;
  //---------------------------- end named expressions
  /**
   * Get the scope level of the symbol table.
   */
  size_t scopeLevel() const;
  /**
   * Push a scope in the symbol table.
   */
  void pushScope();
  /**
   * Pop a scope in the symbol table.
   */
  void popScope();
  /**
   * Reset this symbol manager, which resets the symbol table.
   */
  void reset();

 private:
  /** The API Solver object. */
  api::Solver* d_solver;
  /**
   * The declaration scope that is "owned" by this symbol manager.
   */
  SymbolTable d_symtabAllocated;
  /** The implementation of the symbol manager */
  class Implementation;
  std::unique_ptr<Implementation> d_implementation;
};

}  // namespace CVC4

#endif /* CVC4__EXPR__SYMBOL_MANAGER_H */
