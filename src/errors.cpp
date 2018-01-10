#include "errors.h"

errors::errors()
{

}

errors::~errors()
{

}

QString errors::getErrorString(int code)
{
	QString str = "";
	switch (code)
	{
	case -1: str = "Wrong size of velocity profile vector.\nCheck the size of nozzle and arc velocity profile."; break;
	case  1: str = "This case is not satisfy the condition of kinematic constraint."; break;
	}
	return str;
}