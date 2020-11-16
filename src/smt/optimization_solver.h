/*********************                                                        */
/*! \file optimization_solver.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Ying Sheng
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief The solver for interpolation queries
 **/

#include "cvc4_private.h"

#ifndef CVC4__SMT__OPTIMIZATION_SOLVER_H
#define CVC4__SMT__OPTIMIZATION_SOLVER_H

#include "expr/node.h"
#include "expr/type_node.h"
#include "smt/assertions.h"
#include "util/result.h"

namespace CVC4 {

class SmtEngine;

namespace smt {

/**
 * A solver for interpolation queries.
 *
 * This class is responsible for responding to get-interpol commands. It spawns
 * a subsolver SmtEngine for a sygus conjecture that captures the interpolation
 * query, and implements supporting utility methods such as checkInterpol.
 */
class OptimizationSolver
{
 public:
  OptimizationSolver(SmtEngine* parent);
  ~OptimizationSolver();

  bool checkOpt(Result& r);

 private:
  /** The parent SMT engine */
  SmtEngine* d_parent;
};

}  // namespace smt
}  // namespace CVC4

#endif /* CVC4__SMT__OPTIMIZATION_SOLVER_H */
