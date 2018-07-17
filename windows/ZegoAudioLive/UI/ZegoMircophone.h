#pragma once

#include <QPushButton>
#include <QPainter>
#include <QColor>
class MircoPhoneButton : public QPushButton
{
	Q_OBJECT

public:
	MircoPhoneButton(QWidget  * parent);
	~MircoPhoneButton();

protected:
	virtual void paintEvent(QPaintEvent *event);

public:
	void setProgValue(int value);
	void setMyEnabled(bool state);

private:
	int m_progValue;
	bool isEabled;
};