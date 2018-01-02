#pragma once
#include <QVariant>
#include <ActiveQt/QAxObject>
class MyExcel
{
public:
	MyExcel();
	~MyExcel();
	QList<QList<QVariant> > readAll(QString const&, int & indexRet,QString & strName);
	void writeAll(QString const& strPath, QVector<double>** const& strTime
		, QVector<double>** const& strData, int const& index);
	void castVariant2ListListVariant(const QVariant &var
		, QList<QList<QVariant> > &res);
	bool writeCurrentSheet(const QList<QList<QVariant> > &cells);
	void convertToColName(int data, QString &res);
	QString to26AlphabetString(int data);
};

