#ifndef ERRORS_H
#define ERRORS_H

#include <QString>

class errors
{
public:
	errors();
	~errors();

	static QString getErrorString(int code);
};

#endif