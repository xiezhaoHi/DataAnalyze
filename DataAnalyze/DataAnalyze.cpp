﻿#include "DataAnalyze.h"
#include <QFileDialog>
#include <QElapsedTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>
#include <QTextEdit>
#include <qmath.h>

void DataAnalyze::on_action_open_triggered()
{
// 	QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
// 	if (xlsFile.isEmpty())
// 		return;
// 	QElapsedTimer timer;
// 	timer.start();
// 	if (m_xls.isNull())
// 		m_xls.reset(new ExcelBase);
// 	m_xls->open(xlsFile);
// 	qDebug() << "open cost:" << timer.elapsed() << "ms"; timer.restart();
// 	m_xls->setCurrentSheet(1);
// 	m_xls->readAll(m_datas);
// 	qDebug() << "read data cost:" << timer.elapsed() << "ms"; timer.restart();
// 	QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());
// 	if (md)
// 	{
// 		md->updateData();
// 	}
// 	qDebug() << "show data cost:" << timer.elapsed() << "ms"; timer.restart();
}
DataAnalyze::DataAnalyze(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	//打开文件 开始分析
	QAction*  openAction = new QAction(tr("&Open..."), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, &QAction::triggered, this, &DataAnalyze::on_open_click);

	//启动旧的外部程序
	QAction*  runAction = new QAction(("Run Old DataAnalyze"), this);
	runAction->setStatusTip(tr("Run an exe!"));
	connect(runAction, &QAction::triggered, this, &DataAnalyze::on_run_old);

	//导出文件
	QAction*  exportOne = new QAction(("导出001(扭矩数值)"), this);
	exportOne->setStatusTip(("export a file!"));
	connect(exportOne, &QAction::triggered, this, &DataAnalyze::on_export_one);

	//导出文件
	QAction*  exportTwo = new QAction(("导出002(转速)"), this);
	exportTwo->setStatusTip(("export a file!"));
	connect(exportTwo, &QAction::triggered, this, &DataAnalyze::on_export_two);


	//导出文件
	QAction*  exportThree = new QAction(("导出功率"), this);
	exportThree->setStatusTip(("export a file!"));
	connect(exportThree, &QAction::triggered, this, &DataAnalyze::on_export_three);


	menuBar()->addMenu(tr("&File"))->addAction(openAction);
	menuBar()->addMenu("&Run...")->addAction(runAction);
	QMenu* exportM =menuBar()->addMenu("&export...");
	exportM->addAction(exportOne);
	exportM->addAction(exportTwo);
	exportM->addAction(exportThree);

	QLabel* pLabelST = new QLabel("选择图:");
	QComboBox* pCombox = new QComboBox;
	pCombox->addItem("001(扭矩数值)");
	pCombox->addItem("002(转速)");
	pCombox->addItem("功率");
	//pCombox->addItem("全选");
	m_chooseIndex = pCombox;
	QLabel* pLabel = new QLabel("平滑系数:");
	QLineEdit* pEdit = new QLineEdit;
	m_editText = pEdit;
	QValidator *validator = new QIntValidator(1, 10000);
	pEdit->setValidator(validator);

	QPushButton* pButton = new QPushButton("开始平滑_方式1");
	QPushButton* pButton2 = new QPushButton("开始平滑_方式2");
	connect(pButton, &QPushButton::clicked, this, &DataAnalyze::on_start_click);
	connect(pButton2, &QPushButton::clicked, this, &DataAnalyze::on_start2_click);



	//计算 惯量值
	QLabel* pLabelChoose = new QLabel;
	QLabel* pLabelXB = new QLabel("起点X(s):");
	QLabel* pLabelXE = new QLabel("终点X(s):");
	QLabel* pLabelMC = new QLabel("摩擦转矩(Nm):");

	QLineEdit* pEditXB = new QLineEdit; //选择x轴 起始位置
	QLineEdit* pEditXE = new QLineEdit; //选择x轴 终止位置
	QLabel*	   pLabelYB = new QLabel; //y轴 起始位置
	QLabel*	   pLabelYE = new QLabel; //y轴 终止位置
	QLineEdit* pEditMC = new QLineEdit; //摩擦转矩
	m_pEditXB = pEditXB;
	m_pEditXE = pEditXE;
	m_pLabelYB = pLabelYB;
	m_pLabelYE = pLabelYE;
	m_pEditMC = pEditMC;
	QPushButton* pButtonJSOne = new QPushButton("算法1(功率加转速计算)");
	QPushButton* pButtonJSTwo = new QPushButton("算法2(扭矩加转速计算)");
	connect(pButtonJSOne, &QPushButton::clicked, this, &DataAnalyze::on_js_click_one);
	connect(pButtonJSTwo, &QPushButton::clicked, this, &DataAnalyze::on_js_click_two);

	//计算平均惯量
	m_avgGLOne = new QLineEdit;
	m_avgGLTwo = new QLineEdit;
	m_avgGLAll = new QLineEdit; //文件 平均惯量
	QLabel*	pAvgGLOne = new QLabel("算法1(平均惯量kg.m²):");
	QLabel*	pAvgGLTwo = new QLabel("算法2(平均惯量kg.m²):");
	QLabel*	pAvgGLAll = new QLabel("总平均惯量(kg.m²):");

	QPushButton* pButtonDrOne = new QPushButton("导入算法1计算所得惯量值");
	QPushButton* pButtonDrTwo = new QPushButton("导入算法2计算所得惯量值");
	QPushButton* pButtonDcAvg = new QPushButton("导出平均惯量");
	connect(pButtonDrOne, &QPushButton::clicked, this, &DataAnalyze::on_dr_click_one);
	connect(pButtonDrTwo, &QPushButton::clicked, this, &DataAnalyze::on_dr_click_two);
	connect(pButtonDcAvg, &QPushButton::clicked, this, &DataAnalyze::on_dc_click_two);
	
	int iHeight = 30; //固定高度
	int iWidth = 150; //固定宽
	pLabel->setFixedHeight(iHeight);
	pEdit->setFixedHeight(iHeight);
	pButton->setFixedHeight(iHeight);
	pCombox->setFixedHeight(iHeight);
	pLabelST->setFixedHeight(iHeight);
	pButton2->setFixedHeight(iHeight);
	pLabelXB->setFixedHeight(iHeight);
	pLabelXE->setFixedHeight(iHeight);
	pEditXB->setFixedHeight(iHeight);
	pEditXE->setFixedHeight(iHeight);
	pButtonJSOne->setFixedHeight(iHeight);
	pButtonJSTwo->setFixedHeight(iHeight);
	pEditMC->setFixedHeight(iHeight);
	pLabelYB->setFixedHeight(iHeight);
	pLabelYE->setFixedHeight(iHeight);
	m_avgGLOne->setFixedHeight(iHeight);
	m_avgGLTwo->setFixedHeight(iHeight);
	pAvgGLOne->setFixedHeight(iHeight);
	pAvgGLTwo->setFixedHeight(iHeight);
	pAvgGLAll->setFixedHeight(iHeight);
	m_avgGLAll->setFixedHeight(iHeight);
	pButtonDrOne->setFixedHeight(iHeight);
	pButtonDrTwo->setFixedHeight(iHeight);
	pButtonDcAvg->setFixedHeight(iHeight);

	pCombox->setFixedWidth(iWidth);
	pEdit->setFixedWidth(iWidth);
	pEditXB->setFixedWidth(iWidth);
	pEditXE->setFixedWidth(iWidth);
	pEditMC->setFixedWidth(iWidth);
	m_avgGLOne->setFixedWidth(iWidth);
	m_avgGLTwo->setFixedWidth(iWidth);

	QTableView* pTableOne = new QTableView; //算法1计算的结果 显示
	QTableView* pTableTwo = new QTableView; //算法2...
	QTableView* pAvgTable = new QTableView; //保存平均值

	m_table_one = pTableOne;
	m_table_two = pTableTwo;
	int tabelWidth = 150;
	m_table_modelOne = new QStandardItemModel();
	m_table_modelTwo = new QStandardItemModel();
	m_avgTable_model = new QStandardItemModel;
	m_table_modelOne->setHorizontalHeaderItem(0,
		new QStandardItem(("惯量_算法1(kg.m²)")));
	m_table_modelOne->setHorizontalHeaderItem(1,
		new QStandardItem(("范围(s) (rpm)")));

	pTableOne->setModel(m_table_modelOne);
	pTableOne->setColumnWidth(0, tabelWidth);
	pTableOne->setColumnWidth(1, tabelWidth);
	pTableOne->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	connect(pTableOne, &QTableView::doubleClicked, this, &DataAnalyze::table_delete_one);
	connect(pTableTwo, &QTableView::doubleClicked, this, &DataAnalyze::table_delete_two);
	connect(pAvgTable, &QTableView::doubleClicked, this, &DataAnalyze::table_delete_avg);


	m_table_modelTwo->setHorizontalHeaderItem(0,
		new QStandardItem(("惯量_算法2(kg.m²)")));
	m_table_modelTwo->setHorizontalHeaderItem(1,
		new QStandardItem(("范围(s) (rpm)")));
	pTableTwo->setModel(m_table_modelTwo);
	pTableTwo->setColumnWidth(0, tabelWidth);
	pTableTwo->setColumnWidth(1, tabelWidth);
	pTableTwo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	

	m_avgTable_model->setHorizontalHeaderItem(0,
		new QStandardItem(("文件")));
	m_avgTable_model->setHorizontalHeaderItem(1,
		new QStandardItem(("惯量(kg.m²)")));


	pAvgTable->setModel(m_avgTable_model);
	pAvgTable->setColumnWidth(0, tabelWidth);
	pAvgTable->setColumnWidth(1, tabelWidth);
	pAvgTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


	
	QWidget* pCenter = new QWidget; //中间 窗口 部件
	pCenter->setMinimumSize(800, 600);
	
	
	for (int index = INDEX_ONE;index <INDEX_MAX;++index)
	{
		m_plots[index] = new QCustomPlot;
		m_plots[index]->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
		m_plots[index]->yAxis->setRange(-500, 500);	
		m_title[index] = new QLabel;
		m_title[index]->setFixedHeight(30);
		m_title[index]->setFixedWidth(100);
		//check box  原图显示 和 平滑图显示
		m_checkBox[index] = new MyCheck;

		//存储 数据
		m_timeX[index] = new QVector<double>;
		m_dataY[index] = new QVector<double>;
		m_dataY_res[index] = new QVector<double>;
		m_timeX_res[index] = new QVector<double>;
		m_timeX_res2[index] = new QVector<double>;
		m_dataY_res2[index] = new QVector<double>;
		m_flag[index] = 0;
		m_choosePos[index] = new MyPoint(-1,-1);
		//鼠标移动 显示相应的 图形 数据
		m_showLabel[index] = new QLabel;
		//m_showLabel[index]->setAttribute(Qt::WA_TranslucentBackground, false);
		m_showLabel[index]->setAttribute(Qt::WA_AlwaysStackOnTop, false);
		
	}
	m_dataDW[INDEX_ONE] = new QString("Nm");
	//坐标轴名称显示
	m_plots[INDEX_ONE]->yAxis->setLabel("扭矩(Nm)");
	m_plots[INDEX_ONE]->xAxis->setLabel("时间(s)");
	

	m_dataDW[INDEX_TWO] = new QString("rpm");
	m_plots[INDEX_TWO]->yAxis->setLabel("转速(rpm)");
	m_plots[INDEX_TWO]->xAxis->setLabel("时间(s)");

	m_dataDW[INDEX_THREE] = new QString("kw");
	m_plots[INDEX_THREE]->yAxis->setLabel("功率(kw)");
	m_plots[INDEX_THREE]->xAxis->setLabel("时间(s)");

	

	//初始化 三种数据线的 颜色
	m_init_pen[INDEX_ONE] = new QPen();
	m_init_pen[INDEX_ONE]->setBrush(Qt::blue);

	m_init_pen[INDEX_TWO] = new QPen();
	m_init_pen[INDEX_TWO]->setBrush(Qt::blue);

	m_init_pen[INDEX_THREE] = new QPen();
	m_init_pen[INDEX_THREE]->setBrush(Qt::blue);

	int row = 1, col = 9;

	QHBoxLayout* pTableLayout = new QHBoxLayout;
	pTableLayout->addWidget(pTableOne);
	pTableLayout->addWidget(pTableTwo);

	

	QGridLayout* pRightLayout = new QGridLayout;
	pRightLayout->addWidget(pLabelST, 0, 0);
	pRightLayout->addWidget(pCombox, 0, 1);
	pRightLayout->addWidget(pLabel,1,0);
	pRightLayout->addWidget(pEdit,1,1);
	pRightLayout->addWidget(pButton,0,3);
	pRightLayout->addWidget(pButton2, 1, 3);

	
		
	pRightLayout->addWidget(pLabelXB, 2, 0);
	pRightLayout->addWidget(pEditXB, 2, 1);
	pRightLayout->addWidget(pLabelYB, 2, 2);
	pRightLayout->addWidget(pLabelXE, 3, 0);
	pRightLayout->addWidget(pEditXE, 3, 1);
	pRightLayout->addWidget(pLabelYE, 3, 2);
	pRightLayout->addWidget(pLabelMC, 4, 0);
	pRightLayout->addWidget(pEditMC, 4, 1);

	pRightLayout->addWidget(pButtonJSOne, 3, 3);
	pRightLayout->addWidget(pButtonJSTwo, 4, 3);

	pRightLayout->addLayout(pTableLayout,5,0,1,4);
	pRightLayout->addWidget(pAvgGLOne,6, 0 );
	pRightLayout->addWidget(m_avgGLOne, 6, 1);
	pRightLayout->addWidget(pAvgGLTwo, 6, 2);
	pRightLayout->addWidget(m_avgGLTwo, 6, 3);
	pRightLayout->addWidget(pButtonDrOne, 8, 2);
	pRightLayout->addWidget(pButtonDrTwo, 8, 3);
	pRightLayout->addWidget(pAvgGLAll, 9, 2);
	pRightLayout->addWidget(m_avgGLAll, 9, 3);
	pRightLayout->addWidget(pButtonDcAvg, 10, 3);
	pRightLayout->addWidget(pAvgTable, 7,0,5,2);

	
	pRightLayout->addWidget(pAvgGLAll);
	//pRightLayout->setColumnStretch(0, 1);
	//pRightLayout->setColumnStretch(1, 1);

	pRightLayout->setRowStretch(0, 1);
	pRightLayout->setRowStretch(1, 20);
	QGridLayout* pLayout = new QGridLayout;

	QHBoxLayout* pLayoutOne = new QHBoxLayout;
	pLayoutOne->addWidget(m_title[INDEX_ONE]);
	pLayoutOne->addWidget(m_checkBox[INDEX_ONE]->m_checkOne);
	pLayoutOne->addWidget(m_checkBox[INDEX_ONE]->m_checkTwo);
	pLayout->addLayout(pLayoutOne, 0, 0);
	pLayout->addWidget(m_plots[INDEX_ONE],1,0 ,1, 3);
	

	QHBoxLayout* pLayoutTwo = new QHBoxLayout;
	pLayoutTwo->addWidget(m_title[INDEX_TWO]);
	pLayoutTwo->addWidget(m_checkBox[INDEX_TWO]->m_checkOne);
	pLayoutTwo->addWidget(m_checkBox[INDEX_TWO]->m_checkTwo);
	pLayout->addLayout(pLayoutTwo, 2, 0);
	pLayout->addWidget(m_plots[INDEX_TWO], 3, 0, 1, 3);

	QHBoxLayout* pLayoutThree = new QHBoxLayout;
	pLayoutThree->addWidget(m_title[INDEX_THREE]);
	pLayoutThree->addWidget(m_checkBox[INDEX_THREE]->m_checkOne);
	pLayoutThree->addWidget(m_checkBox[INDEX_THREE]->m_checkTwo);
	pLayout->addLayout(pLayoutThree, 4, 0);
	pLayout->addWidget(m_plots[INDEX_THREE], 5, 0, 1, 3);
	pLayout->addLayout(pRightLayout, 0, 3,6,1);

	pLayout->setColumnStretch(0, col);
	pLayout->setColumnStretch(1, 1);

	pCenter->showMaximized();
	pCenter->setLayout(pLayout);
	setCentralWidget(pCenter);

	m_plots[INDEX_ONE]->installEventFilter(this);
	m_plots[INDEX_TWO]->installEventFilter(this);
	m_plots[INDEX_THREE]->installEventFilter(this);

	for (int index = INDEX_ONE; index < INDEX_MAX; ++index)
	{
		m_checkBox[index]->m_checkOne->installEventFilter(this);
		m_checkBox[index]->m_checkTwo->installEventFilter(this);
	}

	m_statusLabel = new QLabel("");
	m_statusLabel->setAlignment(Qt::AlignCenter);
	m_statusLabel->setMinimumSize(m_statusLabel->sizeHint());
	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
	statusBar()->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
	statusBar()->addWidget(m_statusLabel);
	//statusBar()->showMessage("", 3000); // 显示临时信息，时间3秒钟.
	setWindowState(Qt::WindowMaximized);
}

/*打开文件*/
void DataAnalyze::on_open_click(bool checked )
{
	QFileDialog fileDialog ;
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	fileDialog.setWindowTitle(tr("Open Image"));
	fileDialog.setDirectory(".");
	fileDialog.setDefaultSuffix("csv");
	QStringList pathList;
	if (fileDialog.exec() == QDialog::Accepted) {
		pathList  = fileDialog.selectedFiles();
	}
	
		WorkerRead* work = new WorkerRead(pathList);
		connect(work, &WorkerRead::showData, this, &DataAnalyze::on_ui_showData);
		connect(work, &WorkerRead::finished, work, &QObject::deleteLater);
		work->start();
	
}
//启动旧的分析软件
void DataAnalyze::on_run_old(bool )
{
	QProcess process(this);
	process.startDetached("DataAnalyzeOld.exe");
}


void DataAnalyze::show_ui_Message()
{
	QMessageBox box;
	box.setText("导出完成");
	box.exec();
}
//001 导出数据到excel
void DataAnalyze::on_export_one(bool checked )
{
	int index = INDEX_ONE; //001数据
	QVector<double>** pTempTime = nullptr,**pTempData=nullptr;
		//第一种算法平滑过,输出数据
	if (FLAG_ONE == m_flag[index])
	{
		pTempTime = m_timeX_res;
		pTempData = m_dataY_res;
	}

	//第二种算法平滑过,输出数据
	if (FLAG_TWO == m_flag[index]
		)
	{
		pTempTime = m_timeX_res2;
		pTempData = m_dataY_res2;
	}
	if (pTempTime != nullptr && pTempData != nullptr)
	{

		QString filepath = QFileDialog::getSaveFileName(this, tr("Save orbit")
			, ".", tr("(*.csv)"));
		if (!filepath.isEmpty())
		{
			WorkerWrite* work = new WorkerWrite(pTempTime, pTempData, filepath, index);
			connect(work, &WorkerWrite::showMessage, this, &DataAnalyze::show_ui_Message);
			connect(work, &WorkerWrite::finished, work, &QObject::deleteLater);
			work->start();
			statusBar()->showMessage("正在导出数据,请等待!", 3000);
		}
	}
	else
			statusBar()->showMessage("没有经过平滑,导出数据失败!", 3000);
		
	
}
//002  导出数据到excel
void DataAnalyze::on_export_two(bool checked )
{
	int index = INDEX_TWO; //001数据
	QVector<double>** pTempTime = nullptr, **pTempData = nullptr;
	//第一种算法平滑过,输出数据
	if (FLAG_ONE == m_flag[index])
	{
		pTempTime = m_timeX_res;
		pTempData = m_dataY_res;
	}

	//第二种算法平滑过,输出数据
	if (FLAG_TWO == m_flag[index]
		)
	{
		pTempTime = m_timeX_res2;
		pTempData = m_dataY_res2;
	}
	if (pTempTime != nullptr && pTempData != nullptr)
	{

		QString filepath = QFileDialog::getSaveFileName(this, tr("Save orbit")
			, ".", tr("(*.csv)"));
		if (!filepath.isEmpty())
		{
			WorkerWrite* work = new WorkerWrite(pTempTime, pTempData, filepath, index);
			connect(work, &WorkerWrite::showMessage, this, &DataAnalyze::show_ui_Message);
			connect(work, &WorkerWrite::finished, work, &QObject::deleteLater);
			work->start();
			statusBar()->showMessage("正在导出数据,请等待!", 3000);
		}
	}
	else
		statusBar()->showMessage("没有经过平滑,导出数据失败!", 3000);

}
//功率数据
void DataAnalyze::on_export_three(bool checked)
{
	int index = INDEX_THREE; //001数据
	QVector<double>** pTempTime = nullptr, **pTempData = nullptr;
	//第一种算法平滑过,输出数据
	if (FLAG_ONE == m_flag[index])
	{
		pTempTime = m_timeX_res;
		pTempData = m_dataY_res;
	}

	//第二种算法平滑过,输出数据
	if (FLAG_TWO == m_flag[index]
		)
	{
		pTempTime = m_timeX_res2;
		pTempData = m_dataY_res2;
	}
	if (pTempTime != nullptr && pTempData != nullptr)
	{

		QString filepath = QFileDialog::getSaveFileName(this, tr("Save orbit")
			, ".", tr("(*.csv)"));
		if (!filepath.isEmpty())
		{
			WorkerWrite* work = new WorkerWrite(pTempTime, pTempData, filepath, index);
			connect(work, &WorkerWrite::showMessage, this, &DataAnalyze::show_ui_Message);
			connect(work, &WorkerWrite::finished, work, &QObject::deleteLater);
			work->start();
			statusBar()->showMessage("正在导出数据,请等待!", 3000);
		}
	}
	else
		statusBar()->showMessage("没有经过平滑,导出数据失败!", 3000);

}


/*平滑操作 算法2*/
void DataAnalyze::on_start2_click(bool checked)
{

	int mainIndex = m_chooseIndex->currentIndex();
	int data = m_editText->text().toInt();
	if (data <= 0)
	{
		//平滑为0 画原始图
		m_plots[mainIndex]->clearGraphs();
		QCPGraph* pTemp = m_plots[mainIndex]->addGraph();
		pTemp->setPen(*m_init_pen[mainIndex]);
		pTemp->setData(*m_timeX[mainIndex], *m_dataY[mainIndex]);
		m_plots[mainIndex]->replot();

		statusBar()->showMessage("请输入正确平滑系数", 3000);
		return;
	}
	double temp = 0;
	int num = 0;
	int maxSize = m_dataY[INDEX_ONE]->size();


	if (mainIndex < INDEX_MAX && mainIndex >= 0)
	{
		QVector<double> m_time;
		m_dataY_res2[mainIndex]->clear();
		m_timeX_res2[mainIndex]->clear();
		m_flag[mainIndex] = 2; //平滑方式2
		for (int index = 0; index < maxSize; index+= num)
		{
			temp = 0;
			num = 0;
			for (int ind = index; ind < index + data && ind < maxSize; ++ind)
			{
				++num;
				temp += m_dataY[mainIndex]->at(ind);
			}
			if (index + data/2 < maxSize)
			{
				m_dataY_res2[mainIndex]->push_back(temp / num);
				m_time.push_back(m_timeX[mainIndex]->at(index + data/2 ));
			}
			
		}

		m_timeX_res2[mainIndex]->append(m_time);

		m_plots[mainIndex]->clearGraphs();
		//原图 和 平滑图
		bool boolOne = m_checkBox[mainIndex]->m_checkOne->isChecked();
		bool boolTwo = m_checkBox[mainIndex]->m_checkTwo->isChecked();
		if (boolOne)
		{
			QCPGraph* pTemp = m_plots[mainIndex]->addGraph();
			pTemp->setPen(*m_init_pen[mainIndex]);
			pTemp->setData(*m_timeX[mainIndex], *m_dataY[mainIndex]);
		}
		if (boolTwo)
		{
			QCPGraph* pTemp = m_plots[mainIndex]->addGraph();
			pTemp->setPen(QPen(Qt::red));
			pTemp->setData(m_time, *m_dataY_res2[mainIndex]);
		}
		m_plots[mainIndex]->replot();
	}

}
/*平滑操作 算法1*/
void DataAnalyze::on_start_click(bool checked )
{

	int mainIndex = m_chooseIndex->currentIndex();
	int data = m_editText->text().toInt();
	if (data <= 0)
	{
		//平滑为0 画原始图
		m_plots[mainIndex]->clearGraphs();
		QCPGraph* pTemp = m_plots[mainIndex]->addGraph();
		pTemp->setPen(*m_init_pen[mainIndex]);
		pTemp->setData(*m_timeX[mainIndex], *m_dataY[mainIndex]);
		m_plots[mainIndex]->replot();
		statusBar()->showMessage("请输入正确平滑系数", 3000);
		return;
	}
	double temp=0;
	int num = 0;
	int maxSize = m_dataY[mainIndex]->size();
	if (maxSize > m_timeX[mainIndex]->size())
	{
		maxSize = m_timeX[mainIndex]->size();
	}

	if (mainIndex < INDEX_MAX && mainIndex >= 0)
	{
		m_dataY_res[mainIndex]->clear();
		m_timeX_res[mainIndex]->clear();
		m_flag[mainIndex] = 1; //平滑方式1
		for (int index = 0; index < maxSize ; ++index)
		{
			temp = 0;
			num = 0;
			for (int ind = index; ind < index + data && ind < maxSize; ++ind)
			{
				++num;
				temp += m_dataY[mainIndex]->at(ind);
			}
			if (num == data)
			{
				m_dataY_res[mainIndex]->push_back(temp / num);
				m_timeX_res[mainIndex]->push_back(m_timeX[mainIndex]->at(index));
			}
				
		}
		m_plots[mainIndex]->clearGraphs();
		//原图 和 平滑图
		bool boolOne = m_checkBox[mainIndex]->m_checkOne->isChecked();
		bool boolTwo = m_checkBox[mainIndex]->m_checkTwo->isChecked();
		if (boolOne)
		{
			QCPGraph* pTemp = m_plots[mainIndex]->addGraph();
			pTemp->setPen(*m_init_pen[mainIndex]);
			pTemp->setData(*m_timeX[mainIndex], *m_dataY[mainIndex]);
		}
		if (boolTwo)
		{
			QCPGraph* pTemp = m_plots[mainIndex]->addGraph();
			pTemp->setPen(QPen(Qt::red));
			pTemp->setData(*m_timeX[mainIndex], *m_dataY_res[mainIndex]);
		}
		m_plots[mainIndex]->replot();
	}
	
}
/*index:001 002 31800 三种类型的数据标识 分别为INDEX_ONE INDEX_TWO INDEX_THREE*/
void DataAnalyze::on_ui_showData(WorkerRead* worker, int index)
{
	if (index < 0 || index > INDEX_MAX)
	{
		statusBar()->showMessage("请选择正确的文档", 3000);
		return;
	}
	
	QList<QList<QVariant> > list = worker->m_list;
	
	QList<QList<QVariant> >::iterator begin = list.begin(), end = list.end();
	begin += 3; //获取数据行
	double minData = 1000000, maxData = 0, tempData; //获取数据的极值(y轴)
	double minTime = 1000000, maxTime = 0, tempTime; //获取时间的极值(x轴)
	m_dataY[index]->clear();
	m_timeX[index]->clear();
	for (;begin != end ; ++begin)
	{
		tempTime = begin->at(1).toDouble();

		
		if (minTime > tempTime)
		{
			minTime = tempTime;
		}
		if (maxTime < tempTime)
		{
			maxTime = tempTime;
		}

		m_timeX[index]->push_back(tempTime);
		tempData = begin->at(2).toDouble();

		//把负数转为整数
		if (tempData < 0)
		{
			tempData = 0 - tempData;
		}

		if (minData > tempData)
		{
			minData = tempData;
		}
		if (maxData < tempData)
		{
			maxData = tempData;
		}
		
		m_dataY[index]->push_back(tempData);
	}
	m_title[index]->setText(worker->m_fileName);
	m_plots[index]->yAxis->setRange(minData, maxData);
	m_plots[index]->xAxis->setRange(minTime, maxTime);
	m_plots[index]->clearGraphs(); //先清理
	QCPGraph* pTemp = m_plots[index]->addGraph();
	pTemp->setPen(*m_init_pen[index]);
	pTemp->setData(*m_timeX[index], *m_dataY[index]);


	m_plots[index]->replot();
}

/*事件处理*/
bool DataAnalyze::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent* mouseEvent = (QMouseEvent*)event;
		int index = -1;
		if (m_plots[INDEX_ONE] == (QCustomPlot*)watched)
		{
			index = INDEX_ONE;
		}
		if (m_plots[INDEX_TWO] == (QCustomPlot*)watched)
		{
			index = INDEX_TWO;
		}
		if (m_plots[INDEX_THREE] == (QCustomPlot*)watched)
		{
			index = INDEX_THREE;
		}
	
		if (index != -1)
		{
			//获取鼠标坐标点
			int x_pos = mouseEvent->pos().x();
			int y_pos = mouseEvent->pos().y();

			// 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
			// coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
			float x_val = m_plots[index]->xAxis->pixelToCoord(x_pos);
			float y_val = m_plots[index]->yAxis->pixelToCoord(y_pos);

			// 然后打印在界面上
// 			m_showLabel[index]->setText(QString("%3,%4").arg(x_val).arg(y_val));
// 			m_showLabel[index]->move(x_pos+100, y_pos);
// 			
// 			m_showLabel[index]->show();
// 			
			m_statusLabel->setText(QString("(x=%3,y=%4)").arg(x_val).arg(y_val));
		}
	}
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouseEvent = (QMouseEvent*)event;
		int index = -1;
		if (m_plots[INDEX_ONE] == (QCustomPlot*)watched)
		{
			index = INDEX_ONE;
		}
		if (m_plots[INDEX_TWO] == (QCustomPlot*)watched)
		{
			index = INDEX_TWO;
		}
		if (m_plots[INDEX_THREE] == (QCustomPlot*)watched)
		{
			index = INDEX_THREE;
		}
		if (-1 != index)
		{
			m_chooseIndex->setCurrentIndex(index);
		}
		if (index != -1)
		{
			MyPoint* choosePos = m_choosePos[index];
			float x_val = -1,y_val = -1; //选择的点
			int chooseIndex = -1; //表示 第几次选择 0 1 2
								  //获取鼠标坐标点
			int x_pos = mouseEvent->pos().x();
			int y_pos = mouseEvent->pos().y();

			x_val = m_plots[index]->xAxis->pixelToCoord(x_pos);
			y_val = m_plots[index]->yAxis->pixelToCoord(y_pos);
			QString strDW = *m_dataDW[index];
			if (choosePos->m_x == -1) //表示 第一次选取
			{
				choosePos->m_x = x_val;
				chooseIndex = CHOOSE_ONE;
				m_pEditXB->setText(QString("%1").arg(x_val));
				m_pLabelYB->setText(QString("%1%2").arg(y_val).arg(strDW));
			}
			else if (choosePos->m_y == -1) //第二次选取点
			{
				choosePos->m_y = x_val;
				chooseIndex = CHOOSE_TWO;
				m_pEditXE->setText(QString("%1").arg(x_val));
				m_pLabelYE->setText(QString("%1%2").arg(y_val).arg(strDW));
			}
			else //第三次选取
			{
				//重置
				choosePos->m_x = -1;
				choosePos->m_y = -1;
				choosePos->m_x = x_val;
				chooseIndex = CHOOSE_THREE;
				m_pEditXB->setText(QString("%1").arg(x_val));
				m_pLabelYB->setText(QString("%1%2").arg(y_val).arg(strDW));
				m_pEditXE->setText(QString(""));
				m_pLabelYE->setText(QString(""));
			}
		
			
			
		}
	}
	//checkbox 点击事件 处理图形显示
	if (event->type() == QEvent::MouseButtonRelease)
	{
		QCheckBox* pTemp = (QCheckBox*)watched;
		
		for (int index = INDEX_ONE; index < INDEX_MAX; ++index)
		{
			//找到相应 图形
			if (m_checkBox[index]->m_checkOne == watched 
				|| m_checkBox[index]->m_checkTwo == watched)
			{
				//原图 和 平滑图
				bool boolOne = m_checkBox[index]->m_checkOne->isChecked();
				bool boolTwo = m_checkBox[index]->m_checkTwo->isChecked();
				if (m_checkBox[index]->m_checkOne == watched)
				{
					boolOne = !boolOne;
				}
				if (m_checkBox[index]->m_checkTwo == watched)
				{
					boolTwo = !boolTwo;
				}

				m_plots[index]->clearGraphs();
				if (boolOne)
				{
					QCPGraph* pTemp = m_plots[index]->addGraph();
					pTemp->setPen(*m_init_pen[index]);
					pTemp->setData(*m_timeX[index], *m_dataY[index]);
				}
				if (boolTwo)
				{
					QVector<double>* pTime = nullptr, *pData = nullptr;
					if (FLAG_ONE == m_flag[index]) //进行过平滑算法 1
					{
						pTime = m_timeX_res[index];
						pData = m_dataY_res[index];
					}
					if (FLAG_TWO == m_flag[index]) //进行过平滑算法 1
					{
						pTime = m_timeX_res2[index];
						pData = m_dataY_res2[index];
					}
					if (pTime !=nullptr && pData != nullptr)
					{
						QCPGraph* pTemp = m_plots[index]->addGraph();
						pTemp->setPen(QPen(Qt::red));
						pTemp->setData(*pTime, *pData);
					}
					
				}
				m_plots[index]->replot();
			}
		}
		
	}

	return QMainWindow::eventFilter(watched, event);
}

//计算惯量值 算法1 算法2
void DataAnalyze::on_js_click_one(bool checked )
{
	double begin = m_pEditXB->text().toDouble();
	double end = m_pEditXE->text().toDouble();
	//int index = m_chooseIndex->currentIndex();
	if (begin != 0 && end != 0) //数据有效
	{
		if (begin > end) //范围从小到大 
		{
			double temp = begin;
			begin = end;
			end = temp;
		}
		//算法1   转速数据 和 需要功率 数据 所以 保证这两种数据 时间、平滑度 一致
		if (m_flag[INDEX_TWO] != m_flag[INDEX_THREE])  //两种数据 平滑度不一致 错误
		{
			statusBar()->showMessage("数据平滑度不一致,计算惯量失败!", 3000);
			return;
		}
		int phIndex = m_flag[INDEX_TWO]; //平滑度 选择不同的缓存
		QVector<double>** pData = nullptr,**pTime = nullptr;
		//没有平滑过
		if (FLAG_ZERO == phIndex)
		{
			pTime = m_timeX;
			pData = m_dataY;
		}
		//平滑方式1
		if (FLAG_ONE == phIndex)
		{
			pTime = m_timeX_res;
			pData = m_dataY_res;
		}
		//平滑方式2
		if (FLAG_TWO == phIndex)
		{
			pTime = m_timeX_res2;
			pData = m_dataY_res2;
		}
		//两种数据的 时间对应 才有效
		if (pTime != nullptr && pData != nullptr &&
			pTime[INDEX_TWO]->size() == pTime[INDEX_THREE]->size()
			&& pData[INDEX_THREE]->size() == pData[INDEX_TWO]->size())
		{
			int curIndex = m_chooseIndex->currentIndex();
			//算出 真正的位置
			float xMinBegin = 10000, xMinEnd = 10000;
			int xBegin = -1, xEnd = -1;
			double curTimeB = 0,curTimeE;
			double beginTime = 0, endTime = 0; //保存起始 终止 时间
			for (int index = 0; index < pTime[curIndex]->size(); ++index)
			{
				//计算 选择的坐标 起始 与 终点 最近的两个点
				curTimeB = pTime[curIndex]->at(index) - begin;
				curTimeE = pTime[curIndex]->at(index) - end;

				//计算间距
				if (curTimeB < 0)
				{
					curTimeB = 0 - curTimeB;
				}
				if (curTimeE < 0)
				{
					curTimeE = 0 - curTimeE;
				}
				if (curTimeB < xMinBegin)
				{
					xMinBegin = curTimeB;
					xBegin = index;
					beginTime = pTime[curIndex]->at(index);
				}
				if (curTimeE < xMinEnd)
				{
					xMinEnd = curTimeE;
					xEnd = index;
					endTime = pTime[curIndex]->at(index);
				}
			}
			//有效范围
			if (xBegin != -1 && xEnd != -1 && xBegin < xEnd)
			{
				float t = pTime[curIndex]->at(xBegin + 1) - pTime[curIndex]->at(xBegin);
				if (t <= 0)
				{
					statusBar()->showMessage("选择范围有误,计算失败!", 3000); 
					return;
				}

				//计算和
				double sum = 0;
				//功率 从pn+1 到 pm-1 的和
				for (int index = xBegin+1; index < xEnd -1; ++index)
				{
					sum += pData[INDEX_THREE]->at(index);
				}

				double zsEnd = pData[INDEX_TWO]->at(xEnd);
				double zsBegin = pData[INDEX_TWO]->at(xBegin);

				float pai = 3.141592; //π

				double  res = 1800000 * t*(0.5*(pData[INDEX_THREE]->at(xBegin) + pData[INDEX_THREE]->at(xEnd))
					+ sum);
				double div = (qPow(pai,2)*(qPow(pData[INDEX_TWO]->at(xEnd),2)
					- qPow(pData[INDEX_TWO]->at(xBegin), 2)));
				res = res / div;
				//m_statusLabel->setText(QString("%1").arg(res));
				int row = m_table_modelOne->rowCount();
				m_table_modelOne->setItem(row, 0
					, new QStandardItem(QString("%1").arg(res)));
				m_table_modelOne->setItem(row, 1
					, new QStandardItem(QString("(%1-%2)(%3-%4)")
						.arg(beginTime).arg(endTime)
					.arg(zsBegin).arg(zsEnd)));
				double sumData = res;
				QStandardItem* pTemp;
				QString strTemp;
				QStringList pList;
				for (int index = 0; index < row; ++index)
				{
					strTemp = m_table_modelOne->index(index, 0).data().toString();

					 sumData +=strTemp.toDouble();
				}
				m_avgGLOne->setText(QString("%1 kg.m²").arg(sumData/(row+1)));
			}
		}
	}
	else
	{
		statusBar()->showMessage("请选择一个时间段", 3000);
	}
}
void DataAnalyze::on_js_click_two(bool checked )
{

	double dbTL = m_pEditMC->text().toDouble();
	if (dbTL == 0)
	{
		statusBar()->showMessage("请输入正确的摩擦转矩", 3000);
		return;
	}
	double begin = m_pEditXB->text().toDouble();
	double end = m_pEditXE->text().toDouble();
	//int index = m_chooseIndex->currentIndex();
	if (begin != 0 && end != 0) //数据有效
	{
		if (begin > end) //范围从小到大 
		{
			double temp = begin;
			begin = end;
			end = temp;
		}
		//算法2   以平滑后的转速和扭矩数值为计算基准据 所以 保证这两种数据 时间、平滑度 一致
		if (m_flag[INDEX_ONE] != m_flag[INDEX_TWO])  //两种数据 平滑度不一致 错误
		{
			statusBar()->showMessage("数据平滑度不一致,计算惯量失败!", 3000);
			return;
		}
		int phIndex = m_flag[INDEX_TWO]; //平滑度 选择不同的缓存
		QVector<double>** pData = nullptr, **pTime = nullptr;
		//没有平滑过
		if (FLAG_ZERO == phIndex)
		{
			pTime = m_timeX;
			pData = m_dataY;
		}
		//平滑方式1
		if (FLAG_ONE == phIndex)
		{
			pTime = m_timeX_res;
			pData = m_dataY_res;
		}
		//平滑方式2
		if (FLAG_TWO == phIndex)
		{
			pTime = m_timeX_res2;
			pData = m_dataY_res2;
		}
		//两种数据的 时间对应 才有效
		if (pTime != nullptr && pData != nullptr &&
			pTime[INDEX_TWO]->size() == pTime[INDEX_ONE]->size()
			&&pData[INDEX_ONE]->size() == pData[INDEX_TWO]->size())
		{
			int curIndex = m_chooseIndex->currentIndex();
			//算出 真正的位置
			float xMinBegin = 10000, xMinEnd = 10000;
			int xBegin = -1, xEnd = -1;
			double curTimeB = 0, curTimeE;
			double beginTime = 0, endTime = 0; //保存起始 终止 时间
			for (int index = 0; index < pTime[curIndex]->size(); ++index)
			{
				//计算 选择的坐标 起始 与 终点 最近的两个点
				curTimeB = pTime[curIndex]->at(index) - begin;
				curTimeE = pTime[curIndex]->at(index) - end;

				//计算间距
				if (curTimeB < 0)
				{
					curTimeB = 0 - curTimeB;
				}
				if (curTimeE < 0)
				{
					curTimeE = 0 - curTimeE;
				}
				if (curTimeB < xMinBegin)
				{
					xMinBegin = curTimeB;
					xBegin = index;
					beginTime = pTime[curIndex]->at(index);
				}
				if (curTimeE < xMinEnd)
				{
					xMinEnd = curTimeE;
					xEnd = index;
					endTime = pTime[curIndex]->at(index);
				}
			}
			//有效范围
			if (xBegin != -1 && xEnd != -1 && xBegin < xEnd)
			{
				//时间间隔
				float t = pTime[curIndex]->at(xBegin + 1) - pTime[curIndex]->at(xBegin);
				if (t <= 0)
				{
					statusBar()->showMessage("选择范围有误,计算失败!", 3000);
					return;
				}

				//计算和
				double sum = 0;
				//功率 从pn+1 到 pm-1 的和
				//INDEX_ONE 扭矩    INDEX_TWO 转速
				for (int index = xBegin+1; index < xEnd - 1; ++index)
				{
					sum += (pData[INDEX_ONE]->at(index)-dbTL)*pData[INDEX_TWO]->at(index);
				}
				float pai = 3.141592; //π

				double  res = ((pData[INDEX_ONE]->at(xBegin)-dbTL)*pData[INDEX_TWO]->at(xBegin)
					+ (pData[INDEX_ONE]->at(xEnd) - dbTL)*pData[INDEX_TWO]->at(xEnd))/2;
				double zsEnd = pData[INDEX_TWO]->at(xEnd);
				double zsBegin = pData[INDEX_TWO]->at(xBegin);
				double zsBegin_show = zsBegin;
				double zsEnd_show = zsEnd;
				zsBegin = qPow(zsBegin,2);
				zsEnd = qPow(zsEnd,2);
				double div = pai*(zsEnd - zsBegin);
				res = (60*t*(res+sum)) / div;
				//m_statusLabel->setText(QString("%1").arg(res));
				int row = m_table_modelTwo->rowCount();
				m_table_modelTwo->setItem(row, 0
					, new QStandardItem(QString("%1").arg(res)));
				m_table_modelTwo->setItem(row, 1
					, new QStandardItem(QString("(%1-%2)(%3-%4)")
						.arg(beginTime).arg(endTime)
					.arg(zsBegin_show).arg(zsEnd_show)));
			
				double sumData = res;
				
				QString strTemp;
				QStringList pList;
				for (int index = 0; index < row; ++index)
				{
					strTemp = m_table_modelTwo->index(index, 0).data().toString();
					
					sumData += strTemp.toDouble();
				}
				m_avgGLTwo->setText(QString("%1  kg.m²").arg(sumData/(row+1)));
			
			}
		}
	}
}

void DataAnalyze::table_delete_one(const QModelIndex & index)
{
	
	m_table_modelOne->removeRow(index.row());
	int row = m_table_modelOne->rowCount();
	QString strTemp;
	
	double sumData = 0;
	for (int index = 0; index < row; ++index)
	{
		strTemp = m_table_modelOne->index(index, 0).data().toString();

		sumData += strTemp.split(" ").at(0).toDouble();
	}
	if (row>0)
	{
		m_avgGLOne->setText(QString("%1 kg.m²").arg(sumData / (row)));
	}
	else
		m_avgGLOne->setText(QString("0 kg.m²"));
	

}
void DataAnalyze::table_delete_two(const QModelIndex &index)
{
	m_table_modelTwo->removeRow(index.row());
	int row = m_table_modelTwo->rowCount();
	QString strTemp;

	double sumData = 0;
	for (int index = 0; index < row; ++index)
	{
		strTemp = m_table_modelTwo->index(index, 0).data().toString();

		sumData += strTemp.split(" ").at(0).toDouble();
	}
	if (row > 0)
	{
		m_avgGLTwo->setText(QString("%1 kg.m²").arg(sumData / (row)));
	}
	else
		m_avgGLTwo->setText(QString("0 kg.m²"));
}

void DataAnalyze::table_delete_avg(const QModelIndex &index)
{
	m_avgTable_model->removeRow(index.row());
	int row = m_avgTable_model->rowCount();
	QString strTemp;

	double sumData = 0;
	for (int index = 0; index < row; ++index)
	{
		strTemp = m_avgTable_model->index(index, 1).data().toString();

		sumData += strTemp.split(" ").at(0).toDouble();
	}
	if (row > 0)
	{
		m_avgGLAll->setText(QString("%1 kg.m²").arg(sumData / (row)));
	}
	else
		m_avgGLAll->setText(QString("0 kg.m²"));
}

//导入 算法1 算得平均惯量
void DataAnalyze::on_dr_click_one(bool checked)
{

	double res = m_avgGLOne->text().split(" ").at(0).toDouble();
	if (0 == res)
	{
		statusBar()->showMessage("无有效数据导入,导入失败", 3000);
		return;
	}
	int row = m_avgTable_model->rowCount();
	m_avgTable_model->setItem(row, 0
		, new QStandardItem(QString("%1")
			.arg(m_title[INDEX_ONE]->text().split("#").at(0))));
	
	m_avgTable_model->setItem(row, 1
		, new QStandardItem(QString("%1").arg(res)));

	double sumData = res;

	QString strTemp;
	QStringList pList;
	for (int index = 0; index < row; ++index)
	{
		strTemp = m_avgTable_model->index(index, 1).data().toString();

		sumData += strTemp.toDouble();
	}
	m_avgGLAll->setText(QString("%1 kg.m²").arg(sumData / (row + 1)));
}
//导入 算法2 算得平均惯量
void DataAnalyze::on_dr_click_two(bool checked)
{

	double res = m_avgGLTwo->text().split(" ").at(0).toDouble();
	if (0 == res)
	{
		statusBar()->showMessage("无有效数据导入,导入失败", 3000);
		return;
	}
	int row = m_avgTable_model->rowCount();
	m_avgTable_model->setItem(row, 0
		, new QStandardItem(QString("%1")
			.arg(m_title[INDEX_ONE]->text().split("#").at(0))));

	m_avgTable_model->setItem(row, 1
		, new QStandardItem(QString("%1").arg(res)));

	double sumData = res;

	QString strTemp;
	QStringList pList;
	for (int index = 0; index < row; ++index)
	{
		strTemp = m_avgTable_model->index(index, 1).data().toString();

		sumData += strTemp.toDouble();
	}
	m_avgGLAll->setText(QString("%1 kg.m²").arg(sumData / (row + 1)));
}
//导出 平均惯量到 计算exe windows 消息传递
void DataAnalyze::on_dc_click_two(bool checked)
{
	QString ClassName("ThunderRT6FormDC");
	QString AppName("柴油机最大功率测试软件--WIFI");

	LPCWSTR app = reinterpret_cast<LPCWSTR>(ClassName.data());
	LPCWSTR appCaption = reinterpret_cast<LPCWSTR>(AppName.data());
	HWND hwnd = FindWindow(app, appCaption);
	if (nullptr == hwnd) //程序未启动 启动程序
	{
		QProcess process(this);
		//柴油机功率测试软件V1.0.exe
		QString strPath = QCoreApplication::applicationDirPath() + "//柴油机功率测试软件V1.0.exe";
		bool ret = process.startDetached("柴油机功率测试软件V1.0.exe");
		int err = GetLastError();
		Sleep(300);
		hwnd = FindWindow(app, appCaption);
	}

	//查找到窗口
	if (nullptr != hwnd)
	{
		double res = m_avgGLAll->text().split(" ").at(0).toDouble();
		if (0 == res)
		{
			statusBar()->showMessage("无效数据,导出失败", 3000);
			return;
		}
		HWND tempWnd = GetDlgItem(hwnd, 0x13);
		if (tempWnd != nullptr)
		{
			tempWnd = GetDlgItem(tempWnd, 0x19);
			if (tempWnd != nullptr)
			{
				tempWnd = GetDlgItem(tempWnd, 0x1A);
				if (tempWnd !=nullptr)
				{
					SendMessage(tempWnd, WM_SETTEXT, 0
						, (LPARAM)reinterpret_cast<LPCWSTR>(QString("%1").arg(res).data()));
				}
			}
		}

	}

	
}