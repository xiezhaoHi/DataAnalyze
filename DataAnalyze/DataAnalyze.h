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
	INDEX_ONE , //001 ����
	INDEX_TWO , //002 ����
	INDEX_THREE, //31800 ���� ����
	INDEX_MAX
};
enum enum_flag
{
	FLAG_ZERO, //û��ƽ����
	FLAG_ONE,//��һ��ƽ���㷨
	FLAG_TWO //�ڶ���ƽ��

};
enum enum_choose
{
	CHOOSE_ONE, //��һ��ѡȡ��
	CHOOSE_TWO,//�ڶ���ѡȡ��
	CHOOSE_THREE//������ѡȡ��
};
//��д �����߳� 
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
	 //�����ļ�ȫ·��
	 QStringList m_filePath;
	 QList<QList<QVariant> > m_list;
	 QString m_fileName;
 Q_SIGNALS:
	 void showData(WorkerRead* worker, int index);

private:

};
//��¼ѡȡ��
struct MyPoint 
{
public:
	float m_x;
	float m_y;
	MyPoint(float x, float y) :m_x(x),m_y(y){}
};
//���� ԭͼ �� ƽ�����ͼ  ���� checkbox
struct MyCheck
{
public:
	QCheckBox*  m_checkOne; //ԭͼ��ʾ
	QCheckBox*  m_checkTwo; //ƽ��ͼ��ʾ
	MyCheck(int width = 100)
	{
		m_checkOne = new QCheckBox;
		m_checkOne->setText("��ʾԭͼ");
		m_checkOne->setFixedWidth(width);
		m_checkOne->setChecked(true);
		m_checkTwo = new QCheckBox;
		m_checkTwo->setText("��ʾƽ��ͼ");
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
	int m_index;// INDEX_ONE ...INDEX_THREE  ����ͼ��ʶ
Q_SIGNALS:
	void showMessage(); //��ʶ���
};
class DataAnalyze : public QMainWindow
{
	Q_OBJECT

public:
	DataAnalyze(QWidget *parent = Q_NULLPTR);
	void on_action_open_triggered();
	bool DataAnalyze::eventFilter(QObject *watched, QEvent *event);
public Q_SLOTS:
		//����001����
		void on_export_one(bool checked = false);	
		//����002����
		void on_export_two(bool checked = false);
		//������������
		void on_export_three(bool checked = false);

		void on_run_old(bool checked = false);
		void on_open_click(bool checked = false);
		void on_ui_showData(WorkerRead* worker, int index);
		void on_start_click(bool checked = false);
		void on_start2_click(bool checked = false);
		void on_ZsToTime_click(bool checked = false);
		

		//�������ֵ �㷨1 �㷨2
		void on_js_click_ZJ(bool checked = false);
		void on_js_click_one(bool checked = false);
		void on_js_click_two(bool checked = false);
		void on_dr_click_one(bool checked = false);//���� �㷨1 ���ƽ������
		void on_dr_click_two(bool checked = false);//���� �㷨2 ���ƽ������
		void on_dc_click_two(bool checked = false); //���� ƽ�������� ����exe windows ��Ϣ����

		void show_ui_Message(); //��ʶ���
		void table_delete_one(const QModelIndex &);
		void table_delete_two(const QModelIndex &);
		void table_delete_avg(const QModelIndex &index);

		/*����б�*/
		void on_clear_one(bool checked = false);
		void on_clear_two(bool checked = false);
		void on_clear_avg(bool checked = false);

		void table_click_one(const QPoint &pos);
		void table_click_two(const QPoint &pos);
		void table_click_avg(const QPoint &pos);
private :
	//���� x y  flag:0 ��� 1 �յ�
	void GetRealXY(double &valX, double &valY, int flag);
public:
	int m_table_width; //table �п�
	QLineEdit*	m_avgGLOne, *m_avgGLTwo,*m_avgGLAll; //ƽ������ �㷨1 �㷨2  �����ļ�ƽ������
	QStandardItemModel * m_table_modelOne, *m_table_modelTwo, *m_avgTable_model;
	QTableView* m_table_one, *m_table_two;
	QMenu* m_menu_one, *m_menu_two, *m_menu_avg; //�Ҽ��˵���  tableview
	QLabel* m_statusLabel; //״̬��
	QLineEdit* m_pEditXB; //���� ѡȡ�ĵ�һ���� 
	QLineEdit* m_pEditXE; //���� ѡȡ�ĵڶ�����
	QLabel*		m_pLabelYB;
	QLabel* 	m_pLabelYE;

	QLineEdit* m_pEditZSB; //Ĭ�ϵ�ת�� ��� �Ա� ��ֵ
	QLineEdit* m_pEditZSE; //Ĭ�ϵ�ת�� �յ� �Ա� ��ֵ


	QLineEdit* m_pEditMC; //Ħ��ת��Nm
	MyPoint* m_choosePos[INDEX_MAX]; //�����ͼ�οؼ� ѡȡ����x���
	QLabel* m_showLabel[INDEX_MAX]; //��ʾ����ƶ�ʱ ��ʾ ������Ϣ
	QCustomPlot* m_plots[INDEX_MAX]; //001����ͼ�ؼ�
	QPen* m_init_pen[INDEX_MAX]; //���ó�ʼ����pen
	QString*	m_dataDW[INDEX_MAX]; //�������� ��λ

	MyCheck* m_checkBox[INDEX_MAX];
	QLabel* m_title[INDEX_MAX];//����ͼ�α���
	QComboBox* m_chooseIndex; //ѡ����Ҫƽ����ͼ
	QLineEdit* m_editText; //ƽ����ϵ��(ֻ��������)

	//�洢ԭʼ��Ӧʱ�� ������
	QVector<double>* m_timeX[INDEX_MAX];
	QVector<double>* m_dataY[INDEX_MAX];
	
	//�洢 ƽ���㷨01�������
	/*
	ƽ���㷨1: �����ȡ һ������ ��ƽ��,ʱ�䲻��
	����: ��1s��  ��� ȡ 10����ֵ ��ƽ�� ֵΪ100, ��� ��Ϊ(1s,100)
	1s - 11s, 2s-12s,...
	*/
	QVector<double>* m_timeX_res[INDEX_MAX];
	QVector<double>* m_dataY_res[INDEX_MAX];


	//�洢 ƽ���㷨02�������
	/*
	ƽ���㷨2: ȡһ�β���������� ��ƽ��ֵ, ʱ��ȡ ��Χ�м�ֵ
	����: 1-10s �� 11-21s ... ��Χ�е���ֵ ��ƽ��ֵΪ 100  ʱ��ȡ�м�ֵΪ  5 ����Ϊ(5s,100)
	*/
	QVector<double>* m_timeX_res2[INDEX_MAX];
	QVector<double>* m_dataY_res2[INDEX_MAX];

	//��ʶ 0 û��ƽ�� 1 ����1  2��ʶ����2
	int m_flag[INDEX_MAX];

	Ui::DataAnalyzeClass ui;
};
