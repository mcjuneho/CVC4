/*********************                                                        */
/*! \file interpolation_solver.cpp
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

#include "smt/optimization_solver.h"

#include "options/smt_options.h"
#include "smt/smt_engine.h"
#include "theory/quantifiers/quantifiers_attributes.h"
#include "theory/smt_engine_subsolver.h"

using namespace CVC4::theory;

namespace CVC4 {
namespace smt {

OptimizationSolver::OptimizationSolver(SmtEngine* parent) : d_parent(parent)
{
}

OptimizationSolver::~OptimizationSolver() {}

bool OptimizationSolver::checkOpt(Result& r){
    std::vector<Node> axioms = d_parent->getExpandedAssertions();
    std::unique_ptr<SmtEngine> optChecker;
    initializeSubsolver(optChecker);

    optChecker->setOption("incremental", "true");
    optChecker->setOption("produce-models", "true");

    for (const Node& e : axioms){
        optChecker->assertFormula(e);
    }
    
    //while()
    /*for (Objective o: d_activatedObjectives){
        optChecker->makeTerm()
    }*/
    r = optChecker->checkSat();

    return true;

}

void OptimizationSolver::activateObj(const Node& obj, const int& type, const int& result){
    Objective o = Objective(obj, (ObjectiveType)type, (OptResult)result);
    d_activatedObjectives.push_back(o);
}

OptimizationSolver::Objective::Objective(Node obj, ObjectiveType type, OptResult result)
    : d_type(type), d_result(OPT_UNKNOWN), d_node(obj)
{
}

}  // namespace smt
}  // namespace CVC4
