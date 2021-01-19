#include <iostream>
#include "api/cvc4cpp.h"

using namespace CVC4::api;

int main()
{
    Solver slv;
    slv.setOption("produce-assertions", "true");
    slv.setOption("incremental", "true");

    // Sort bv = slv.mkBitVectorSort(8);
    Term ub = slv.mkReal(100);
    Term lb = slv.mkReal(0);
    Term cost = slv.mkConst(slv.getIntegerSort(), "cost");
    Term cost2 = slv.mkConst(slv.getIntegerSort(), "cost2");
    // Term bound = slv.mkBitVector(8, 4);
    Term upb = slv.mkTerm(Kind::GT, ub, cost);
    Term lowb = slv.mkTerm(Kind::GT, cost, lb);
    Term upb2 = slv.mkTerm(Kind::GT, ub, cost2);
    Term lowb2 = slv.mkTerm(Kind::GT, cost2, lb);
    slv.assertFormula(upb);
    slv.assertFormula(lowb);
    slv.assertFormula(upb2);
    slv.assertFormula(lowb2);
    Objective maximize = slv.makeMaxObjective(cost);
    Objective minimize = slv.makeMinObjective(cost2);
    slv.activateObjective(maximize);
    slv.activateObjective(minimize);
    std::cout << "Result is :" << slv.checkAndOpt() << std::endl;
    std::cout << "Optimized max value is: " << slv.objectiveGetValue(maximize) << std::endl;
    std::cout << "Optimized min value is: " << slv.objectiveGetValue(minimize) << std::endl;
}
