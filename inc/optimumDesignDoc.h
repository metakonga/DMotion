#ifndef OPTIMUMDESIGNDOC
#define OPTIMUMDESIGNDOC

#include "optimumCase.h"

class model;
class plotWindow;

class optimumDesignDoc
{
public:
	optimumDesignDoc(model* _md, plotWindow* _plot);
	~optimumDesignDoc();

	void clear();

	optimumCase* createOptimumCase(QString cName);
	void appendOptimumCase(optimumCase* oc);
	void setSelectedCase(QString cName);
	bool checkMinumumThisCase(optimumCase* oc);
	void removeOptimumCase(optimumCase *oc);
	void setSelectReaction(reactionForceType rft, bool b);
	void setComparisonReactionType(comparisonReactionType _crt);
	optimumCase* SelectedCase();
	QMap<reactionForceType, bool>& SelectList();
	QMap<QString, optimumCase*>& OptimumCases();

	int ReactionListSize();

private:
	int reactionSize;
	comparisonReactionType crt;
	model* md;
	plotWindow* plot;
	optimumCase* selectedCase;
	QMap<reactionForceType, bool> selectList;
	QMap<QString, optimumCase*> optimumCases;
};

#endif