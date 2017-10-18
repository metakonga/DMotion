#include <QDialog>
#include <QList>
#include <QPushButton>

class materialDialog : public QDialog
{
	Q_OBJECT

public:
	materialDialog(QWidget* parent = NULL);
	~materialDialog();

signals:
	void sendMaterialChanged(int);

	private slots:
	void updateButtons(bool);
	
	
private:
	QList<QPushButton*> myButtons;
};