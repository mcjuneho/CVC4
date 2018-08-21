/*********************                                                        */
/*! \file ite_removal.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Tim King, Paul Meng
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2017 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Remove ITEs from the assertions
 **
 ** [[ Add lengthier description here ]]
 ** \todo document this file
 **/

#include "cvc4_private.h"

#ifndef __CVC4__PREPROCESSING__PASSES__ITE_REMOVAL_H
#define __CVC4__PREPROCESSING__PASSES__ITE_REMOVAL_H

#include <unordered_set>
#include <vector>

#include "preprocessing/preprocessing_pass.h"
#include "preprocessing/preprocessing_pass_context.h"

namespace CVC4 {
namespace preprocessing {
namespace passes {

class IteRemoval : public PreprocessingPass
{
 public:
  IteRemoval(PreprocessingPassContext* preprocContext);

 protected:
  PreprocessingPassResult applyInternal(AssertionPipeline* assertions) override;
};

}  // namespace passes
}  // namespace preprocessing
}  // namespace CVC4

#endif  // __CVC4__PREPROCESSING__PASSES__ITE_REMOVAL_H