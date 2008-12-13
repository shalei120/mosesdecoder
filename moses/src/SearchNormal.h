
#pragma once

#include <vector>
#include "Search.h"
#include "HypothesisStackNormal.h"
#include "TranslationOptionCollection.h"
#include "ReorderingConstraint.h"
#include "Timer.h"

namespace Moses
{

class InputType;
class TranslationOptionCollection;

class SearchNormal: public Search
{
protected:
		const InputType &m_source;
		std::vector < HypothesisStack* > m_hypoStackColl; /**< stacks to store hypotheses (partial translations) */ 
	// no of elements = no of words in source + 1
	TargetPhrase m_initialTargetPhrase; /**< used to seed 1st hypo */
	clock_t m_start; /**< starting time, used for logging */
	size_t interrupted_flag;
	HypothesisStackNormal* actual_hypoStack; /**actual (full expanded) stack of hypotheses*/ 
	const TranslationOptionCollection &m_transOptColl; /**< pre-computed list of translation options for the phrases in this sentence */
	ReorderingConstraint *m_reorderingConstraint; /**< positions in input sentence over which no reordering is allowed */


	// functions for creating hypotheses
	void ProcessOneHypothesis(const Hypothesis &hypothesis);
	void ExpandAllHypotheses(const Hypothesis &hypothesis,const TranslationOptionList &transOptList);
	void ExpandHypothesis(const Hypothesis &hypothesis,const TranslationOption &transOpt);

public:
	SearchNormal(const InputType &source, const TranslationOptionCollection &transOptColl);
	~SearchNormal();

	void ProcessSentence();

	void OutputHypoStackSize();
	void OutputHypoStack(int stack);

	virtual const std::vector < HypothesisStack* >& GetHypothesisStacks() const;
	virtual const Hypothesis *GetBestHypothesis() const;
};

}

