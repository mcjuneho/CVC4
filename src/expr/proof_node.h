/*********************                                                        */
/*! \file proof_node.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Strings proof utility
 **/

#include "cvc4_private.h"

#ifndef CVC4__EXPR__PROOF_NODE_H
#define CVC4__EXPR__PROOF_NODE_H

#include <vector>

#include "expr/node.h"
#include "expr/proof_step.h"

namespace CVC4 {

class ProofChecker;

/** A node in a proof 
 * 
 * A ProofNode represents a single step in a proof. It contains:
 * - d_id, an identifier indicating the type of inference,
 * - d_children, the child ProofNode objects indicating its premises,
 * - d_args, additional arguments used to determine the conclusion,
 * - d_proven, cache of the formula that this ProofNode proves.
 * 
 * Overall, a ProofNode and its children form a directed acyclic graph.
 */
class ProofNode
{
  friend class ProofChecker;
 public:
  ProofNode(ProofStep id,
            const std::vector<std::shared_ptr<ProofNode>>& children,
            const std::vector<Node>& args);
  ~ProofNode() {}
  /** get id */
  ProofStep getId() const;
  /** get what this node proves, or the null node if this is an invalid proof */
  Node getResult() const;
  /** get assumptions */
  void getAssumptions(std::vector<Node>& assump);
  /** print debug */
  void printDebug(std::ostream& os) const;
 private:
  /** The proof step */
  ProofStep d_id;
  /** The children of this node */
  std::vector<std::shared_ptr<ProofNode>> d_children;
  /** arguments of this node */
  std::vector<Node> d_args;
  /** The cache of the fact that has been proven, modifiable by ProofChecker */
  Node d_proven;
};

}  // namespace CVC4

#endif /* CVC4__EXPR__PROOF_NODE_H */