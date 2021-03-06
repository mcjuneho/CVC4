/*********************                                                        */
/*! \file theory_preprocessor.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds, Morgan Deters, Dejan Jovanovic
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief The theory preprocessor.
 **/

#include "cvc4_private.h"

#ifndef CVC4__THEORY__THEORY_PREPROCESSOR_H
#define CVC4__THEORY__THEORY_PREPROCESSOR_H

#include <unordered_map>

#include "context/cdhashmap.h"
#include "context/context.h"
#include "expr/lazy_proof.h"
#include "expr/node.h"
#include "expr/tconv_seq_proof_generator.h"
#include "expr/term_conversion_proof_generator.h"
#include "smt/term_formula_removal.h"
#include "theory/trust_node.h"

namespace CVC4 {

class LogicInfo;
class TheoryEngine;
class RemoveTermFormulas;

namespace theory {

/**
 * The preprocessor used in TheoryEngine.
 */
class TheoryPreprocessor
{
  typedef context::CDHashMap<Node, Node, NodeHashFunction> NodeMap;

 public:
  /** Constructs a theory preprocessor */
  TheoryPreprocessor(TheoryEngine& engine,
                     context::UserContext* userContext,
                     ProofNodeManager* pnm = nullptr);
  /** Destroys a theory preprocessor */
  ~TheoryPreprocessor();
  /**
   * Preprocesses the given assertion node. It returns a TrustNode of kind
   * TrustNodeKind::REWRITE indicating the preprocessed form of node. It stores
   * additional lemmas in newLemmas, which are trust nodes of kind
   * TrustNodeKind::LEMMA. These correspond to e.g. lemmas corresponding to ITE
   * removal. For each lemma in newLemmas, we add the corresponding skolem that
   * the lemma defines.
   *
   * @param node The assertion to preprocess,
   * @param newLemmas The lemmas to add to the set of assertions,
   * @param newSkolems The skolems that newLemmas correspond to,
   * @return The (REWRITE) trust node corresponding to rewritten node via
   * preprocessing.
   */
  TrustNode preprocess(TNode node,
                       std::vector<TrustNode>& newLemmas,
                       std::vector<Node>& newSkolems);
  /**
   * Same as above, but transforms the proof of node into a proof of the
   * preprocessed node and returns the LEMMA trust node.
   *
   * @param node The assertion to preprocess,
   * @param newLemmas The lemmas to add to the set of assertions,
   * @param newSkolems The skolems that newLemmas correspond to,
   * @return The (LEMMA) trust node corresponding to the proof of the rewritten
   * form of the proven field of node.
   */
  TrustNode preprocessLemma(TrustNode node,
                            std::vector<TrustNode>& newLemmas,
                            std::vector<Node>& newSkolems);

  /** Get the term formula removal utility */
  RemoveTermFormulas& getRemoveTermFormulas();

 private:
  /**
   * Runs theory specific preprocessing (Theory::ppRewrite) on the non-Boolean
   * parts of the node.
   */
  TrustNode theoryPreprocess(TNode node);
  /**
   * Internal helper for preprocess, which also optionally preprocesses the
   * new lemmas generated until a fixed point is reached based on argument
   * procLemmas.
   */
  TrustNode preprocessInternal(TNode node,
                               std::vector<TrustNode>& newLemmas,
                               std::vector<Node>& newSkolems,
                               bool procLemmas);
  /**
   * Internal helper for preprocessLemma, which also optionally preprocesses the
   * new lemmas generated until a fixed point is reached based on argument
   * procLemmas.
   */
  TrustNode preprocessLemmaInternal(TrustNode node,
                                    std::vector<TrustNode>& newLemmas,
                                    std::vector<Node>& newSkolems,
                                    bool procLemmas);
  /** Reference to owning theory engine */
  TheoryEngine& d_engine;
  /** Logic info of theory engine */
  const LogicInfo& d_logicInfo;
  /** Cache for theory-preprocessing of assertions */
  NodeMap d_ppCache;
  /** The term formula remover */
  RemoveTermFormulas d_tfr;
  /** The term context, which computes hash values for term contexts. */
  InQuantTermContext d_iqtc;
  /**
   * A term conversion proof generator storing preprocessing and rewriting
   * steps.
   */
  std::unique_ptr<TConvProofGenerator> d_tpg;
  /**
   * A term conversion sequence generator, which applies theory preprocessing,
   * term formula removal, and rewriting in sequence.
   */
  std::unique_ptr<TConvSeqProofGenerator> d_tspg;
  /**
   * A term conversion proof generator storing rewriting steps, which is used
   * for calls to preprocess when doTheoryPreprocess is false. We store
   * (top-level) rewrite steps only. Notice this is intentionally separate
   * from d_tpg, which interleaves both preprocessing and rewriting.
   */
  std::unique_ptr<TConvProofGenerator> d_tpgRew;
  /** A lazy proof, for additional lemmas. */
  std::unique_ptr<LazyCDProof> d_lp;
  /** Helper for theoryPreprocess */
  Node ppTheoryRewrite(TNode term);
  /**
   * Rewrite with proof, which stores a REWRITE step in d_tpg if necessary
   * and returns the rewritten form of term.
   */
  Node rewriteWithProof(Node term);
  /**
   * Preprocess with proof, which calls the appropriate ppRewrite method,
   * stores the corresponding rewrite step in d_tpg if necessary and returns
   * the preprocessed and rewritten form of term. It should be the case that
   * term is already in rewritten form.
   */
  Node preprocessWithProof(Node term);
  /** Proofs enabled */
  bool isProofEnabled() const;
};

}  // namespace theory
}  // namespace CVC4

#endif /* CVC4__THEORY__THEORY_PREPROCESSOR_H */
