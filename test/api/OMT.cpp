#include <iostream>
#include "api/cvc4cpp.h"

using namespace CVC4::api;

int main()
{
    Solver slv;
    slv.setOption("produce-assertions", "true");
    slv.setOption("incremental", "true");

    Sort bv = slv.mkBitVectorSort(8);
    Term cost = slv.mkConst(bv, "cost");
    Term bound = slv.mkBitVector(8, 4);
    Term equal = slv.mkTerm(Kind::EQUAL, cost, bound);
    slv.assertFormula(equal);
    Objective o = slv.makeMaxObjective(cost);
    slv.activateObjective(o);
    std::cout<< slv.checkAndOpt() << std::endl;
}