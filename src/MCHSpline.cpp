#include "MCHSpline.h"
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

MCHSpline::MCHSpline()
	: limit(0)
{

}

MCHSpline::~MCHSpline()
{
	//m->clear();
	//if (m) delete[] m; m = NULL;
}

bool MCHSpline::monotonic_cubic_Hermite_spline(QPointF& new_p)
{
	x_src.push_back(new_p.x());
	y_src.push_back(new_p.y());
	limit = new_p.x();
	int n = (int)x_src.size();
	int i = 0;
	double _m = 0;
	if (n == 2 && m.size() == 0)
	{
		_m = (y_src.at(1) - y_src.at(0)) / (x_src.at(1) - x_src.at(0));
		m.push_back(_m);
		m.push_back(0);
		
	}
	else if (n > 2 && m.size())
	{
		_m = (y_src.at(n - 1) - y_src.at(n - 2)) / (x_src.at(n - 1) - x_src.at(n - 2));
		m.push_back(_m);
		m[n - 2] = (y_src.at(n - 2) - y_src.at(n - 3)) / (2.0*(x_src.at(n - 2) - x_src.at(n - 3))) + (y_src.at(n - 1) - y_src.at(n - 2)) / (2.0*(x_src.at(n - 1) - x_src.at(n - 2)));
		if (n == 3)
		{
			monotonicity(0, 1);
			monotonicity(1, 2);
		}
		else
		{
			monotonicity(n - 2, n - 1);
		}
	}
	return true;
}

bool MCHSpline::monotonic_cubic_Hermite_spline(int idx, QPointF& new_p)
{
	int n = x_src.size();
	x_src.replace(idx, new_p.x());
	y_src.replace(idx, new_p.y());
	if (new_p.x() > limit)
		limit = new_p.x();
	if (idx == n - 1)
	{
		limit = new_p.x();
	}
	double _m = 0;
	if (n > 2)
	{
		if (idx == 0 || idx == 1)
		{
			m[0] = (y_src.at(1) - y_src.at(0)) / (x_src.at(1) - x_src.at(0));
			monotonicity(0, 1);
			monotonicity(1, 2);
		}
			

		if (idx >= n - 2)
		{
			_m = (y_src.at(n - 1) - y_src.at(n - 2)) / (x_src.at(n - 1) - x_src.at(n - 2));
			m[n - 1] = _m;
			monotonicity(n - 3, n - 2);
			monotonicity(n - 2, n - 1);
		}
		
		if (idx >= 1 && idx <= n - 2)
		{
			int s = idx - 1 == 0 ? 1 : idx - 1;
			int e = (idx + 1) == (n - 1) ? idx : idx + 1;
			for (int i = s; i <= e; i++)
			{
				m[i] = (y_src[i] - y_src[i - 1]) / (2.0*(x_src[i] - x_src[i - 1])) + (y_src[i + 1] - y_src[i]) / (2.0*(x_src[i + 1] - x_src[i]));
			}
			monotonicity(idx - 1, idx);
			monotonicity(idx, idx + 1);
		}
	}
	return true;
}

void MCHSpline::monotonicity(int i, int j)
{
	
	double dk = (y_src.at(j) - y_src.at(i)) / (x_src.at(j) - x_src.at(i));
	if (fabs(dk) <= 1e-9)
	{
		m[i] = m[j] = 0.0;
	}
	else
	{
		double ak = m[i] / dk;
		double bk = m[j] / dk;
		if (ak*ak + bk*bk > 9.0)
		{
			m[i] = 3.0 / (sqrt(ak * ak + bk * bk)) * ak * dk;
			m[j] = 3.0 / (sqrt(ak * ak + bk * bk)) * bk * dk;
		}
	}
	
}

bool MCHSpline::monotonic_cubic_Hermite_spline(double lmt, QVector<double>& x_src, QVector<double>& y_src)
{
// 	limit = lmt;
// 	int n = (int)x_src.size();
// 	int i = 0;
// 	if (!m)
// 		m = new QVector<double>;
// 
// 	m[0] = (y_src[1] - y_src[0]) / (x_src[1] - x_src[0]);
// 	m[n - 1] = (y_src[n - 1] - y_src[n - 2]) / (x_src[n - 1] - x_src[n - 2]);
// 	for (i = 1; i < n - 1; i++)
// 	{
// 		m[i] = (y_src[i] - y_src[i - 1]) / (2.0*(x_src[i] - x_src[i - 1])) + (y_src[i + 1] - y_src[i]) / (2.0*(x_src[i + 1] - x_src[i]));
// 	}
// 
// 	for (i = 0; i < n - 1; i++)
// 	{
// 		double dk = (y_src[i + 1] - y_src[i]) / (x_src[i + 1] - x_src[i]);
// 		if (fabs(dk) <= 1e-9)
// 		{
// 			m[i] = m[i + 1] = 0.0;
// 		}			
// 		else
// 		{
// 			double ak = m[i] / dk;
// 			double bk = m[i + 1] / dk;
// 			if (ak*ak + bk*bk > 9.0)
// 			{
// 				m[i] = 3.0 / (sqrt(ak * ak + bk * bk)) * ak * dk;
// 				m[i + 1] = 3.0 / (sqrt(ak * ak + bk * bk)) * bk * dk;
// 			}
// 		}
// 	}

// 	for (i = 0; i < n - 1; i++)
// 	{
// 		double cur_x = x_src[i];
// 		double next_x = x_src[i + 1];
// 		//int v = (int)(1e-9 + x_src[i + 1]);
// 		double cur_y = y_src[i];
// 		double next_y = y_src[i + 1];
// 		double h = next_x - cur_x;
// 		double x = 0;
// 		double inc = h * 0.01;
// 		for (x = cur_x; x < next_x; x += inc)
// 		{
// 			if (x > limit)
// 				break;
// 			double t = (x - cur_x) / h;
// 			x_data.push_back(x);
// 			double y = cur_y * h00(t) + h * m[i] * h10(t) + next_y * h01(t) + h * m[i + 1] * h11(t);
// 			y_data.push_back(y);
// 		}
// 	}

	//delete[] m;

	return true;
}

void MCHSpline::calculate_curve_auto(QLineSeries* series, int sid, bool _base /* = false */)
{
	int n = x_src.size();
	if (_base)
		series->clear();
	int cnt = 0;
	for (int i = sid; i < n - 1; i++)
	{
		start_ids.push_back(cnt);
		double cur_x = x_src[i];
		double next_x = x_src[i + 1];
		//int v = (int)(1e-9 + x_src[i + 1]);
		double cur_y = y_src[i];
		double next_y = y_src[i + 1];
		double h = next_x - cur_x;
		double x = 0;
		double inc = h * 0.01;
		for (x = cur_x; x < next_x; x += inc)
		{
			if (x > limit)
				break;
			double t = (x - cur_x) / h;
			//x_out->push_back(x);
			double y = cur_y * h00(t) + h * m.at(i) * h10(t) + next_y * h01(t) + h * m.at(i + 1) * h11(t);
			series->append(x, y);
			cnt++;
		}
	}
}

void MCHSpline::calculate_curve_auto(QLineSeries* series, int sid, int eid)
{
	///find()
	int n = x_src.size();
	int cnt = 0;
	int s = (sid == 0) ? 0 : sid - 1;
	int e = (eid == x_src.size()) ? eid - 1 : eid;
	int start_id = start_ids.at(s);
	//int 
	series->clear();
	for (int i = 0; i < n - 1; i++)
	{
		double cur_x = x_src[i];
		double next_x = x_src[i + 1];
		//int v = (int)(1e-9 + x_src[i + 1]);
		double cur_y = y_src[i];
		double next_y = y_src[i + 1];
		double h = next_x - cur_x;
		double x = 0;
		double inc = h * 0.01;
		for (x = cur_x; x < next_x; x += inc)
		{
			if (x > limit)
				break;
			double t = (x - cur_x) / h;
			//x_out->push_back(x);
			double y = cur_y * h00(t) + h * m.at(i) * h10(t) + next_y * h01(t) + h * m.at(i + 1) * h11(t);
			//series->append(x, y);
			series->append(QPointF(x, y));
			cnt++;
			//y_out->push_back(y);
		}
	}
}

void MCHSpline::setData2LineSeries(QLineSeries* series)
{
	int n = x_src.size();
	if (n > 3)
	{
		calculate_curve_auto(series, n - 2, false);
	}
	else if (n == 3)
	{
		calculate_curve_auto(series, 0, true);
	}
	else
	{
		series->append(x_src.at(n - 1), y_src.at(n - 1));
	}
// 	int n = x_data.size();
// 	QVector<double>::iterator x = x_data.begin();
// 	QVector<double>::iterator y = y_data.begin();
// 	for (; (x != x_data.end()) && (y != y_data.end()); x++, y++)
// 	{
// 		series->append(*x, *y);
// 	}
}

void MCHSpline::update_curve(int idx, QPointF& new_p, QLineSeries* series)
{
	int n = x_src.size();
	if (n >= 3)
	{
		monotonic_cubic_Hermite_spline(idx, new_p);
	}
}