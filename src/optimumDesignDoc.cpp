#include "optimumDesignDoc.h"
#include "plotWindow.h"
#include "model.h"

optimumDesignDoc::optimumDesignDoc(model* _md, plotWindow* _plot)
	: md(_md)
	, plot(_plot)
	, selectedCase(NULL)
	, reactionSize(0)
{
	plot->bindOptimumDesignDoc(this);
	for (int i = 0; i < _md->ReactionMap().size(); i++)
	{
		selectList[_md->ReactionMap()[i]] = false;
	}
	reactionSize = _md->ReactionMap().size();
// 	selectList["Nozzle Trans.(FY)"] = false;
// 	selectList["Nozzle Trans.(TR)"] = false;
// 	selectList["Nozzle-Link Rev.(FX)"] = false;
// 	selectList["Nozzle-Link Rev.(FY)"] = false;
// 	selectList["Link-Cam Rev.(FX)"] = false;
// 	selectList["Link-Cam Rev.(FY)"] = false;
// 	selectList["Cam-Ground Rev.(FX)"] = false;
// 	selectList["Cam-Ground Rev.(FY)"] = false;
// 	selectList["Arc Trans.(FY)"] = false;
// 	selectList["Arc Trans.(TR)"] = false;
// 	selectList["Arc-Cam PF(FX)"] = false;
// 	selectList["Arc-Cam PF(FY)"] = false;
}

optimumDesignDoc::~optimumDesignDoc()
{
	this->clear();
}

void optimumDesignDoc::clear()
{	
	qDeleteAll(optimumCases); optimumCases.clear();
	selectedCase = NULL;
}

optimumCase* optimumDesignDoc::createOptimumCase(QString cName)
{
	optimumCase* oc = new optimumCase(cName);
	QMapIterator<reactionForceType, bool> list(selectList);
	while (list.hasNext())
	{
		list.next();
		oc->MaximumReactions()[list.key()].dir = "";
		oc->MaximumReactions()[list.key()].maximum = 0.0;
		oc->MaximumReactions()[list.key()].time = 0.0;
	}
	return oc;
}

void optimumDesignDoc::appendOptimumCase(optimumCase* oc)
{
	if (crt == ONLY_ONE)
	{
		qDeleteAll(optimumCases);
		optimumCases.clear();
		optimumCases[oc->Name()] = oc;
	}
	else
		optimumCases[oc->Name()] = oc;
}

void optimumDesignDoc::setSelectedCase(QString cName)
{
	bool isNeedUpdatePlot = false;
	if (selectedCase)
	{
		if (selectedCase->Name() != cName)
		{
			isNeedUpdatePlot = true;
		}
	}
	selectedCase = optimumCases[cName];
	if (isNeedUpdatePlot)
	{
		plot->updatePlotData();
	}
}

bool optimumDesignDoc::checkMinumumThisCase(optimumCase* oc)
{
	bool isMinimum = true;
	optimumCase *oc0 = optimumCases.begin().value();
	QMapIterator<reactionForceType, stMaxReaction> mrs(oc->MaximumReactions());
	if (crt == SMALLER_FIRST || crt == ONLY_ONE)
	{
// 		while (mrs.hasNext())
// 		{
// 			mrs.next();
// 			QString _name = mrs.key();
// 
// 			if (mrs.value().maximum > oc0->MaximumReactions()[mrs.key()].maximum)
// 				isMinimum = false;
// 			
// 			// 		if (_name == "active_driving" || _name == "ground_active_tra" || _name == "ground_passive_tra" || _name == "passive_driving")
// 			// 			continue;
// 
// 		}
		while (mrs.hasNext())
		{
			mrs.next();
			reactionForceType _name = mrs.key();
			bool sl = selectList[_name];
			if (sl)
			{
				if (mrs.value().maximum >= oc0->MaximumReactions()[mrs.key()].maximum)
					isMinimum = false;
			}
		}
	}
// 	if (isMinimum)
// 	{
// 		optimumCases[oc->Name()] = oc;
// 	}
	return isMinimum;
}

void optimumDesignDoc::removeOptimumCase(optimumCase *oc)
{
//	delete optimumCases[oc->Name()];
	optimumCases.remove(oc->Name());
}

void optimumDesignDoc::setSelectReaction(reactionForceType rft, bool b)
{
	selectList[rft] = b;
}

void optimumDesignDoc::setComparisonReactionType(comparisonReactionType _crt)
{
	crt = _crt;
}

optimumCase* optimumDesignDoc::SelectedCase()
{
	return selectedCase;
}

QMap<QString, optimumCase*>& optimumDesignDoc::OptimumCases()
{
	return optimumCases;
}

int optimumDesignDoc::ReactionListSize()
{
	return reactionSize;
}

QMap<reactionForceType, bool>& optimumDesignDoc::SelectList()
{
	return selectList;
}