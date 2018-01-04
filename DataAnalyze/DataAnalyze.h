#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DataAnalyze.h"
#include <QThread>
#include "MyExcel.h"
#include <QCustomPlot\qcustomplot\qcustomplot.h>
#include <ObjBase.h>
#include <QCheckBox>
#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  
enum enum_index
{
	INDEX_ONE , //001 数据
	INDEX_TWO , //002 数据
	INDEX_THREE, //31800 功率 数据
	INDEX_MAX
};
enum enum_flag
{
	FLAG_ZERO, //没有平滑过
	FLAG_ONE,//第一种平滑算法
	FLAG_TWO //第二种平滑

};
enum enum_choose
{
	CHOOSE_ONE, //第一次选取点
	CHOOSE_TWO,//第二次选取点
	CHOOSE_THREE//第三次选取点
};
//读写 工作线程 
class WorkerRead : public QThread
{
	Q_OBJECT
public:
	void run()
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		MyExcel exl;
		for each (QString var in m_filePath)
		{
			int indexRet;
			m_list = exl.readAll(var, indexRet, m_fileName);
			emit showData(this, indexRet);
		}
		
		CoUninitialize();
	}
	 WorkerRead(QStringList const& filePath):m_filePath(filePath)
	{
	
	}
	 //保存文件全路径
	 QStringList m_filePath;
	 QList<QList<QVariant> > m_list;
	 QString m_fileName;
 Q_SIGNALS:
	 void showData(WorkerRead* worker, int index);

private:

};
//记录选取点
struct MyPoint 
{
public:
	float m_x;
	float m_y;
	MyPoint(float x, float y) :m_x(x),m_y(y){}
};
//保存 原图 和 平滑后的图  两个 checkbox
struct MyCheck
{
public:
	QCheckBox*  m_checkOne; //原图显示
	QCheckBox*  m_checkTwo; //平滑图显示
	MyCheck(int width = 100)
	{
		m_checkOne = new QCheckBox;
		m_checkOne->setText("显示原图");
		m_checkOne->setFixedWidth(width);
		m_checkOne->setChecked(true);
		m_checkTwo = new QCheckBox;
		m_checkTwo->setText("显示平滑图");
		m_checkTwo->setFixedWidth(width);
		m_checkTwo->setChecked(true);
	}
};
class WorkerWrite : public QThread
{
	Q_OBJECT
public:
	WorkerWrite(QVector<double>** time, QVector<double>** data, QString strFile,int index)
		:m_time(time),m_data(data),m_strFile(strFile), m_index(index){}
	void run()
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		QTime t;
		t.start();
		MyExcel ex;
		ex.writeAll(m_strFile, m_time, m_data, m_index);
		int test = t.elapsed();
		emit showMessage();
		CoUninitialize();
		
	}
	QVector<double>** m_time;
	QVector<double>** m_data;
	QString m_strFile;
	int m_index;// INDEX_ONE ...INDEX_THREE  三种图标识
Q_SIGNALS:
	void showMessage(); //标识完成
};
class DataAnalyze : public QMainWindow
{
	Q_OBJECT

public:
	DataAnalyze(QWidget *parent = Q_NULLPTR);
	void on_action_open_triggered();
	bool DataAnalyze::eventFilter(QObject *watched, QEvent *event);
public Q_SLOTS:
		//导出001数据
		void on_export_one(bool checked = false);	
		//导出002数据
		void on_export_two(bool checked = false);
		//导出功率数据
		void on_export_three(bool checked = false);

		void on_run_old(bool checked = false);
		void on_open_click(bool checked = false);
		void on_ui_showData(WorkerRead* worker, int index);
		void on_start_click(bool checked = false);
		void on_start2_click(bool checked = false);
		void on_ZsToTime_click(bool checked = false);
		

		//计算惯量值 算法1 算法2
		void on_js_click_ZJ(bool checked = false);
		void on_js_click_one(bool checked = false);
		void on_js_click_two(bool checked = false);
		void on_dr_click_one(bool checked = false);//导入 算法1 算得平均惯量
		void on_dr_click_two(bool checked = false);//导入 算法2 算得平均惯量
		void on_dc_click_two(bool checked = false); //导出 平均惯量到 计算exe windows 消息传递

		void show_ui_Message(); //标识完成
		void table_delete_one(const QModelIndex &);
		void table_delete_two(const QModelIndex &);
		void table_delete_avg(const QModelIndex &index);

		/*清除列表*/
		void on_clear_one(bool checked = false);
		void on_clear_two(bool checked = false);
		void on_clear_avg(bool checked = false);

		void table_click_one(const QPoint &pos);
		void table_click_two(const QPoint &pos);
		void table_click_avg(const QPoint &pos);
private :
	//坐标 x y  flag:0 起点 1 终点
	void GetRealXY(double &valX, double &valY, int flag);
public:
	int m_table_width; //table 列宽
	QLineEdit*	m_avgGLOne, *m_avgGLTwo,*m_avgGLAll; //平均惯量 算法1 算法2  整个文件平均惯量
	QStandardItemModel * m_table_modelOne, *m_table_modelTwo, *m_avgTable_model;
	QTableView* m_table_one, *m_table_two;
	QMenu* m_menu_one, *m_menu_two, *m_menu_avg; //右键菜单项  tableview
	QLabel* m_statusLabel; //状态栏
	QLineEdit* m_pEditXB; //保存 选取的第一个点 
	QLineEdit* m_pEditXE; //保存 选取的第二个点
	QLabel*		m_pLabelYB;
	QLabel* 	m_pLabelYE;

	QLineEdit* m_pEditZSB; //默认的转速 起点 对比 数值
	QLineEdit* m_pEditZSE; //默认的转速 终点 对比 数值


	QLineEdit* m_pEditMC; //摩擦转矩Nm
	MyPoint* m_choosePos[INDEX_MAX]; //鼠标点击图形控件 选取两次x轴点
	QLabel* m_showLabel[INDEX_MAX]; //显示鼠标移动时 显示 坐标信息
	QCustomPlot* m_plots[INDEX_MAX]; //001数据图控件
	QPen* m_init_pen[INDEX_MAX]; //设置初始化的pen
	QString*	m_dataDW[INDEX_MAX]; //保存数据 单位

	MyCheck* m_checkBox[INDEX_MAX];
	QLabel* m_title[INDEX_MAX];//设置图形标题
	QComboBox* m_chooseIndex; //选择需要平滑的图
	QLineEdit* m_editText; //平滑的系数(只能是数字)

	//存储原始对应时间 和数据
	QVector<double>* m_timeX[INDEX_MAX];
	QVector<double>* m_dataY[INDEX_MAX];
	
	//存储 平滑算法01后的数据
	/*
	平滑算法1: 点向后取 一定数据 求平均,时间不变
	例如: 从1s起  向后 取 10个数值 求平均 值为100, 最后 点为(1s,100)
	1s - 11s, 2s-12s,...
	*/
	QVector<double>* m_timeX_res[INDEX_MAX];
	QVector<double>* m_dataY_res[INDEX_MAX];


	//存储 平滑算法02后的数据
	/*
	平滑算法2: 取一段不交叉的数据 求平均值, 时间取 范围中间值
	例如: 1-10s 、 11-21s ... 范围中的数值 求平均值为 100  时间取中间值为  5 最后点为(5s,100)
	*/
	QVector<double>* m_timeX_res2[INDEX_MAX];
	QVector<double>* m_dataY_res2[INDEX_MAX];

	//标识 0 没有平滑 1 方法1  2标识方法2
	int m_flag[INDEX_MAX];

	Ui::DataAnalyzeClass ui;
};
