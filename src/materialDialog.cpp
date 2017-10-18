#include "materialDialog.h"
#include <QSignalMapper>
#include <Graphic3d_NameOfMaterial.hxx>
#include <QVBoxLayout>
//#include <QPushButton>

materialDialog::materialDialog(QWidget* parent)
	: QDialog(parent)
{
	setModal(true);
	QPushButton* b;
	QVBoxLayout* vbl = new QVBoxLayout(this);
	vbl->setMargin(8);

	QSignalMapper *sm = new QSignalMapper(this);
	connect(sm, SIGNAL(mapped(int)), this, SIGNAL(sendMaterialChanged(int)));

	b = new QPushButton(QObject::tr("PLASTER"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_PLASTER);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("BRASS"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_BRASS);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("BRONZE"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_BRONZE);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("COPPER"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_COPPER);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("GOLD"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_GOLD);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("PEWTER"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_PEWTER);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("PLASTIC"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_PLASTIC);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("SILVER"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_SILVER);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("STEEL"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_STEEL);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("STONE"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_STONE);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("SHINY PLASTIC"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_SHINY_PLASTIC);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("SATIN"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_SATIN);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("METALIZED"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_METALIZED);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("NEON GNC"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_NEON_GNC);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("CHROME"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_CHROME);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("ALUMINIUM"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_ALUMINIUM);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);

	b = new QPushButton(QObject::tr("OBSIDIAN"), this);
	sm->setMapping(b, (int)Graphic3d_NOM_OBSIDIAN);
	connect(b, SIGNAL(clicked()), sm, SLOT(map()));
	b->setCheckable(true);
	connect(b, SIGNAL(toggled(bool)), this, SLOT(updateButtons(bool)));
	myButtons.append(b);
	vbl->addWidget(b);
}

materialDialog::~materialDialog()
{

}

void materialDialog::updateButtons(bool isOn)
{
	if (!isOn)
		return;

	QPushButton*sentBy = (QPushButton*)sender();

	for (int i = 0; i < myButtons.size(); i++)
	{
		QPushButton* b = myButtons.at(i);
		if (b != sentBy) {
			b->setEnabled(true);
			b->setChecked(false);
		}
		else {
			b->setEnabled(false);
		}
	}
}

