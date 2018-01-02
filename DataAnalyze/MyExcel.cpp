#include "MyExcel.h"
#include <QFileDialog>
#include <QMessageBox>
//源代码编码必须是: UTF-8(BOM)    
#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  
///
/// \brief 写入一个表格内容
/// \param cells
/// \return 成功写入返回true
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
/// \brief 把列数转换为excel的字母列号
/// \param data 大于0的数
/// \return 字母列号，如1->A 26->Z 27 AA
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
/// \brief 数字转换为26字母
///
/// 1->A 26->Z
/// \param data
/// \return
///
QString MyExcel::to26AlphabetString(int data)
{
	QChar ch = data + 0x40;//A对应0x41
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
	QVariant title_value = excel.property("Caption");  //获取标题  
	
	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");


	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets  
	
	int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目  
	QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);  //Sheets(int)也可换用Worksheets(int)  
	
	QString work_sheet_name = work_sheet->property("Name").toString();  //获取工作表名称  
	strName = work_sheet_name;
	
	//简单校验下 文件是否正确
	int indexTitle = title_value.toString().indexOf(work_sheet_name);
	if (work_sheet != NULL && !work_sheet->isNull()&& -1 != indexTitle)
	{
		QAxObject *usedRange = work_sheet->querySubObject("UsedRange");
		
		//有效数据
		if (NULL != usedRange && !usedRange->isNull())
		{
			QVariant varTemp = usedRange->dynamicCall("Value");
			//转换为一个 多维 数组
			castVariant2ListListVariant(varTemp, varList);
			int indexTemp = work_sheet_name.indexOf("#001"); //001数据
			if (-1 != indexTemp) //表示为001数据
			{
				indexRet = 0;
			}
			else
			{
				indexTemp = work_sheet_name.indexOf("#002"); //002数据
				if (-1 != indexTemp)
				{
					indexRet = 1;
				}
				else
				{
					indexTemp = work_sheet_name.indexOf("功率"); //功率数据
					if (-1 != indexTemp)
					{
						indexRet = 2; //表示为功率
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
	if (index<0 || index >2) //无效参数 返回
	{
		return;
	}
		QAxObject excel("Excel.Application");
		excel.dynamicCall("SetVisible (bool Visible)", "false");//不显示窗体  
		excel.setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示  

		QAxObject *workbooks = excel.querySubObject("WorkBooks");//获取工作簿集合  
		workbooks->dynamicCall("Add");//新建一个工作簿  
		QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取当前工作簿  
		QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合  
		QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);//获取工作表集合的工作表1，即sheet1  
		QAxObject *cellX, *cellY;
		QStringList strTemp;
		QStringList  strBeginA, strBeginB;
		
		strTemp.push_back("扭矩(Nm)");
		strTemp.push_back("转速(rpm)");
		strTemp.push_back("功率(kw)");

		QAxObject *range = worksheet->querySubObject("Range(QVariant, QVariant)", "B1");

		range->dynamicCall("SetValue(const QVariant&)", QVariant(strTemp[index]));
		

		range = worksheet->querySubObject("Range(QVariant, QVariant)", "A1");
		range->dynamicCall("SetValue(const QVariant&)", QVariant("时间(s)"));
		

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
			QString X = strBeginA[ind] + QString::number(1);//设置要操作的单元格，如A1  
			QString Y = strBeginB[ind] + QString::number(1);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//获取单元格  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

			cellX->dynamicCall("SetValue(const QVariant&)"
				, QVariant("时间(s)"));//设置单元格的值  

			cellY->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strTemp[ind]));
		}
		

	
		QString X, Y;
		for (int i = 0, ind = 0; i < strTime[ind]->size() && i < strData[ind]->size(); i++)
		{
			X = strBeginA[ind] + QString::number(2 + i);//设置要操作的单元格，如A1  
			Y = strBeginB[ind] + QString::number(2 + i);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//获取单元格  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

				cellX->dynamicCall("SetValue(const QVariant&)"
					, QVariant(strTime[ind]->at(i)));//设置单元格的值  
				cellY->dynamicCall("SetValue(const QVariant&)"
					, QVariant(strData[ind]->at(i)));
				double t = strData[ind]->at(i);
		}
		for (int i = 0,ind = 1; i < strTime[ind]->size() && i < strData[ind]->size(); i++)
		{
			X = strBeginA[ind] + QString::number(2 + i);//设置要操作的单元格，如A1  
			Y = strBeginB[ind] + QString::number(2 + i);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//获取单元格  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

			cellX->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strTime[ind]->at(i)));//设置单元格的值  
			cellY->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strData[ind]->at(i)));
			double t = strData[ind]->at(i);

		}
		for (int i = 0, ind = 2; i < strTime[ind]->size() && i < strData[ind]->size(); i++)
		{
			X = strBeginA[ind] + QString::number(2 + i);//设置要操作的单元格，如A1  
			Y = strBeginB[ind] + QString::number(2 + i);
			cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);//获取单元格  
			cellY = worksheet->querySubObject("Range(QVariant, QVariant)", Y);

			cellX->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strTime[ind]->at(i)));//设置单元格的值  
			cellY->dynamicCall("SetValue(const QVariant&)"
				, QVariant(strData[ind]->at(i)));
			double t = strData[ind]->at(i);
		}

	*/
		workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(strPath));
		//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。  
		workbook->dynamicCall("Close()");//关闭工作簿  
		excel.dynamicCall("Quit()");//关闭excel  
}