#include <iostream>
#include "api/cvc4cpp.h"

using namespace CVC4::api;

int main()
{
    Solver slv;
    slv.setOption("produce-assertions", "true");
    slv.setOption("incremental", "true");

    //Sort bv = slv.mkBitVectorSort(8);
    Term ub = slv.mkReal(100);
    Term lb = slv.mkReal(0);
    Term cost = slv.mkConst( slv.getIntegerSort(), "cost");
    //Term bound = slv.mkBitVector(8, 4);
    Term upb = slv.mkTerm(Kind::GT, ub, cost);
    Term lowb = slv.mkTerm(Kind::GT, cost, lb);
    slv.assertFormula(upb);
    slv.assertFormula(lowb);
    Objective o = slv.makeMaxObjective(cost);
    slv.activateObjective(o);
    std::cout<< "Result is :" << slv.checkAndOpt() << std::endl;
    std::cout<< "Optimized value is: " << slv.objectiveGetValue(o) << std::endl;
}