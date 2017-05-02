#ifndef KREST_H
#define KREST_H

#include <QApplication>
#include <QColor>
#include <QRectF>
#include <QWidget>
#include <QString>
#include <QGraphicsItem>

class Krest : public QGraphicsItem
{
    Q_DECLARE_TR_FUNCTIONS (Krest)

public:
	Krest (QGraphicsItem * parent = 0);
	~Krest ();

	void setText (const QString &text);
	QString text ();
	int X, Y;
	QPointF coord;
	QRectF boundingRect () const;
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:;
	void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);

private:;
	QRectF outlineRect () const;
	QString myText;
	QColor myTextColor;
	QColor myBackgroundColor;
	QColor myOutlineColor;
	QColor myKrestColor;
};

#endif
