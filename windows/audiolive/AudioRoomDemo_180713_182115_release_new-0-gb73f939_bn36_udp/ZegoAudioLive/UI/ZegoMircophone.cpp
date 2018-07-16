#include "ZegoMircophone.h"

MircoPhoneButton::MircoPhoneButton(QWidget  * parent) : QPushButton(parent)
{
	m_progValue = 0;
	isEabled = true;
}

MircoPhoneButton::~MircoPhoneButton()
{
 
}

void MircoPhoneButton::paintEvent(QPaintEvent *event)
{
	//先绘制父控件图
	QPushButton::paintEvent(event);

	if (m_progValue > 15 && isEabled)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

		QColor color(14, 136, 235);
		painter.setPen(QPen(color, 0, Qt::SolidLine));
		painter.setBrush(QBrush(color, Qt::SolidPattern));

		int height = 19 * m_progValue / 100.0;
		int y = 4 + (18 - height);

		painter.drawRoundedRect(12, y, 9, height, 8, 6);
	}
}

void MircoPhoneButton::setProgValue(int value)
{
	m_progValue = value;
}

void MircoPhoneButton::setMyEnabled(bool state)
{
	isEabled = state;
}