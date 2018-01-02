#include "MyExcel.h"
#include <QFileDialog>
#include <QMessageBox>
//Դ������������: UTF-8(BOM)    
#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  
///
/// \brief д��һ���������
/// \param cells
/// \return �ɹ�д�뷵��true
/// \see readAllSheet
///
bool MyExcel::writeCurrentSheet(const QList<QList<QVariant> > &cells)
{
// 	if (cells.size() <= 0)
// 		return false;
// 	if (NULL == this->sheet || this->sheet->isNull())
// 		return false;
// 	int row = cells.size();
// 	int col = cells.at(0).size();
// 	QString rangStr;
// 	convertToColName(col, rangStr);
// 	rangStr += QString::number(row);
// 	rangStr = "A1:" + rangStr;
// 	qDebug() << rangStr;
// 	QAxObject *range = this->sheet->querySubObject("Range(const QString&)", rangStr);
// 	if (NULL == range || range->isNull())
// 	{
// 		return false;
// 	}
// 	bool succ = false;
// 	QVariant var;
// 	castListListVariant2Variant(cells, var);
// 	succ = range->setProperty("Value", var);
// 	delete range;
// 	return succ;
	return true;
}
///
/// \brief ������ת��Ϊexcel����ĸ�к�
/// \param data ����0����
/// \return ��ĸ�кţ���1->A 26->Z 27 AA
///
void MyExcel::convertToColName(int data, QString &res)
{
	Q_ASSERT(data > 0 && data < 65535);
	int tempData = data / 26;
	if (tempData > 0)
	{
		int mode = data % 26;
		convertToColName(mode, res);
		convertToColName(tempData, res);
	}
	else
	{
		res = (to26AlphabetString(data) + res);
	}
}
///
/// \brief ����ת��Ϊ26��ĸ
///
/// 1->A 26->Z
/// \param data
/// \return
///
QString MyExcel::to26AlphabetString(int data)
{
	QChar ch = data + 0x40;//A��Ӧ0x41
	return QString(ch);
}
MyExcel::MyExcel()
{
}


MyExcel::~MyExcel()
{
}
QList<QList<QVariant> > MyExcel::readAll(QString const& strPath,int & indexRet, QString & strName)
{
	indexRet = -1;
	QList<QList<QVariant> > varList;
	
	QAxObject excel("Excel.Application");
	excel.setProperty("Visible", false);
	QAxObject *work_books = excel.querySubObject("WorkBooks");
	
	work_books->dynamicCall("Open (const QString&)", strPath);
	QVariant title_value = excel.property("Caption");  //��ȡ����  
	
	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");


	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //SheetsҲ�ɻ���WorkSheets  
	
	int sheet_count = work_sheets->property("Count").toInt();  //��ȡ��������Ŀ  
	QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);  //Sheets(int)Ҳ�ɻ���Worksheets(int)  
	
	QString work_sheet_name = work_sheet->property("Name").toString();  //��ȡ����������  
	strName = work_sheet_name;
	
	//��У���� �ļ��Ƿ���ȷ
	int indexTitle = title_value.toString().indexOf(work_sheet_name);
	if (work_sheet != NULL && !work_sheet->isNull()&& -1 != indexTitle)
	{
		QAxObject *usedRange = work_sheet->querySubObject("UsedRange");
		
		//��Ч����
		if (NULL != usedRange && !usedRange->isNull())
		{
			QVariant varTemp = usedRange->dynamicCall("Value");
			//ת��Ϊһ�� ��ά ����
			castVariant2ListListVariant(varTemp, varList);
			int indexTemp = work_sheet_name.indexOf("#001"); //001����
			if (-1 != indexTemp) //��ʾΪ001����
			{
				indexRet = 0;
			}
			else
			{
				indexTemp = work_sheet_name.indexOf("#002"); //002����
				if (-1 != indexTemp)
				{
					indexRet = 1;
				}
				else
				{
					indexTemp = work_sheet_name.indexOf("����"); //��������
					if (-1 != indexTemp)
					{
						indexRet = 2; //��ʾΪ����
					}
				}
					
			}
			
// 			delete usedRange;
// 			delete work_sheet;
// 			delete work_sheets;
// 			delete work_book;
// 			delete work_books;
			excel.dynamicCall("Quit()");
		}
	}
	return varList;
}

void MyExcel::castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
	QVariantList varRows = var.toList();
	if (varRows.isEmpty())
	{
		return;
	}
	const int rowCount = varRows.size();
	QVariantList rowData;
	for (int i = 0; i < rowCount; ++i)
	{
		rowData = varRows[i].toList();
		res.push_back(rowData);
	}
}


void MyExcel::writeAll(QString const& strPath, QVector<double>** const& strTime
	, QVector<double>** const& strData, int const& index)
{
	if (index<0 || index >2) //��Ч���� ����
	{
		return;
	}
		QAxObject excel("Excel.Application");
		excel.dynamicCall("SetVisible (bool Visible)", "false");//����ʾ����  
		excel.setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ  

		QAxObject *workbooks = excel.querySubObject("WorkBooks");//��ȡ����������  
		workbooks->dynamicCall("Add");//�½�һ��������  
		QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//��ȡ��ǰ������  
		QAxObject *worksheets = workbook->querySubObject("Sheets");//��ȡ��������  
		QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);//��ȡ�������ϵĹ�����1����sheet1  
		QAxObject *cellX, *cellY;
		QStringList strTemp;
		QStringList  strBeginA, strBeginB;
		
		strTemp.push_back("Ť��(Nm)");
		strTemp.push_back("ת��(rpm)");
		strTemp.push_back("����(kw)");

		QAxObject *range = worksheet->querySubObject("Range(QVariant, QVariant)", "B1");

		range->dynamicCall("SetValue(const QVariant&)", QVariant(strTemp[index]));
		

		range = worksheet->querySubObject("Range(QVariant, QVariant)", "A1");
		range->dynamicCall("SetValue(const QVariant&)", QVariant("ʱ��(s)"));
		

		QList<QVariant> a1,a2, a3;
		QList<QVariant> d;
		int sizet = 100;
		for (int ind = 0; ind < strTime[index]->size() && strData[index];++ind)
		{
			QList<QVariant> a;
			a.append(strTime[index]->at(ind));
			a.append(strData[index]->at(ind));
			d.append(QVariant(a));
		}
		
		
		

		  range = worksheet->querySubObject("Range(QVariant, QVariant)", QString("A2:B%1").arg(strTime[index]->size()+1));
	
		 range->dynamicCall("SetValue(const QVariant&)", QVariant(d));

		

		/*
		

		strBeginA.push_back("A");
		strBeginA.push_back("D");
		strBeginA.push_back("G");
		strBeginB.push_back("B");
		strBeginB.push_back("E");
		strBeginB.push_back("H");
		

		for (int ind = 0; ind < index; ++ind)
		{
			QString X = strBeginA[ind] + QString::number(1);//����Ҫ�����ĵ�Ԫ����A1  
			QString Y = strBeginB[ind] + QString::number(1);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//��ȡ��Ԫ��  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

			cellX->dynamicCall("SetValue(const QVariant&)"
				, QVariant("ʱ��(s)"));//���õ�Ԫ���ֵ  

			cellY->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strTemp[ind]));
		}
		

	
		QString X, Y;
		for (int i = 0, ind = 0; i < strTime[ind]->size() && i < strData[ind]->size(); i++)
		{
			X = strBeginA[ind] + QString::number(2 + i);//����Ҫ�����ĵ�Ԫ����A1  
			Y = strBeginB[ind] + QString::number(2 + i);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//��ȡ��Ԫ��  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

				cellX->dynamicCall("SetValue(const QVariant&)"
					, QVariant(strTime[ind]->at(i)));//���õ�Ԫ���ֵ  
				cellY->dynamicCall("SetValue(const QVariant&)"
					, QVariant(strData[ind]->at(i)));
				double t = strData[ind]->at(i);
		}
		for (int i = 0,ind = 1; i < strTime[ind]->size() && i < strData[ind]->size(); i++)
		{
			X = strBeginA[ind] + QString::number(2 + i);//����Ҫ�����ĵ�Ԫ����A1  
			Y = strBeginB[ind] + QString::number(2 + i);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//��ȡ��Ԫ��  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

			cellX->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strTime[ind]->at(i)));//���õ�Ԫ���ֵ  
			cellY->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strData[ind]->at(i)));
			double t = strData[ind]->at(i);

		}
		for (int i = 0, ind = 2; i < strTime[ind]->size() && i < strData[ind]->size(); i++)
		{
			X = strBeginA[ind] + QString::number(2 + i);//����Ҫ�����ĵ�Ԫ����A1  
			Y = strBeginB[ind] + QString::number(2 + i);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//��ȡ��Ԫ��  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

			cellX->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strTime[ind]->at(i)));//���õ�Ԫ���ֵ  
			cellY->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strData[ind]->at(i)));
			double t = strData[ind]->at(i);
		}

	*/
		workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(strPath));
		//������filepath��ע��һ��Ҫ��QDir::toNativeSeparators��·���е�"/"ת��Ϊ"\"����Ȼһ�����治�ˡ�  
		workbook->dynamicCall("Close()");//�رչ�����  
		excel.dynamicCall("Quit()");//�ر�excel  
}