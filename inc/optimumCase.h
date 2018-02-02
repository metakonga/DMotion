#ifndef OPTIMUMCASE_H
#define OPTIMUMCASE_H

#include <QString>
#include <QMap>
#include <QVector>
#include "dmotion_types.h"
#include "model.h"


class optimumCase
{
public:
	optimumCase(QString _name);
	~optimumCase();

	void appendBodyResults(model* md, double ct, VECD& q, VECD& qd, VECD& qdd);
	void appendReactionResults(model* md, double ct);
	void appendHardPointResult(model* md, double ct);
	void appendCamProfileResult(pointFollower* pf, double ct);
	void setResultCount(unsigned int nc);
	unsigned int ResultCount();
	double MaxAreaRange();
	void setProfileMaxDistance(double mdist);
	void saveCase(QFile& stream, unsigned int idx);

	double profileMaxDistance();
	stMaxReaction& maxReactionStructure(reactionForceType _type);
	QMap<reactionForceType, stMaxReaction>& MaximumReactions();
	QMap<QString, QVector<resultDataType>>& BodyResults();
	QMap<QString, QVector<jointResultDataType>>& ReactionResults();
	QMap<QString, QVector<vecd3>>& HardPointsResults();
	QVector<QPointF>& CamProfileResults();
	QVector<QPointF>& LastCamProfileResults();
	QString Name();


private:
	unsigned int count;
	double maxArea;
	double maxDistance;
	QString name;
	QMap<QString, QVector<resultDataType>> bodyResults;
	QMap<QString, QVector<jointResultDataType>> reactionResults;
	QMap<QString, QVector<vecd3>> hardPointResults;
	QVector<QPointF> camProfileResults;
	QVector<QPointF> lastCamProfileResults;
	QMap<reactionForceType, stMaxReaction> maximumReaction;
};

#endif