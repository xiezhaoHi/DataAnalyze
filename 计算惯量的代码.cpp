//计算惯量值 算法1 算法2
void DataAnalyze::on_js_click_one(bool checked )
{
	//选取的时间点
	double begin = m_pEditXB->text().toDouble();
	double end = m_pEditXE->text().toDouble();
	
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
		else
		{
			statusBar()->showMessage("数据不完整!", 3000);
		}
	}
	else
	{
		statusBar()->showMessage("请选择一个时间段!", 3000);
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
	//选取的时间段
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
				//时间段 的转速
				double zsEnd = pData[INDEX_TWO]->at(xEnd);
				double zsBegin = pData[INDEX_TWO]->at(xBegin);
				double zsBegin_show = zsBegin;
				double zsEnd_show = zsEnd;
				zsBegin = qPow(zsBegin,2);
				zsEnd = qPow(zsEnd,2);
				double div = pai*(zsEnd - zsBegin);
				res = (60*t*(res+sum)) / div;
				
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
