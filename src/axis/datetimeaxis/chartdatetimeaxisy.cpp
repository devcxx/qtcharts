/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartdatetimeaxisy_p.h"
#include "chartpresenter_p.h"
#include "qdatetimeaxis.h"
#include "abstractchartlayout_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <QDateTime>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDateTimeAxisY::ChartDateTimeAxisY(QDateTimeAxis *axis, QGraphicsItem *item)
    : VerticalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
}

ChartDateTimeAxisY::~ChartDateTimeAxisY()
{
}

QVector<qreal> ChartDateTimeAxisY::calculateLayout() const
{
    int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QVector<qreal> points;
    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaY = gridRect.height() / (qreal(tickCount) - 1.0);
    for (int i = 0; i < tickCount; ++i)
        points[i] =  qreal(i) * -deltaY + gridRect.bottom();

    return points;
}

void ChartDateTimeAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;
    setLabels(createDateTimeLabels(min(), max(), layout.size(), m_axis->format()));
    VerticalAxis::updateGeometry();
}

void ChartDateTimeAxisY::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick)
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void ChartDateTimeAxisY::handleFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QSizeF ChartDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(axis()->labelsFont());
    QSizeF sh;

    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = createDateTimeLabels(min(), max(), m_axis->tickCount(), m_axis->format());
    qreal width = 0;
    // Height of vertical axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base height is irrelevant.
    qreal height = 0;

    if (ticksList.empty())
        return sh;

    switch (which) {
        case Qt::MinimumSize: {
            QRectF boundingRect = labelBoundingRect(fn, "...");
            width = boundingRect.width() + labelPadding();
            width += base.width();
            height = boundingRect.height() / 2.0;
            sh = QSizeF(width, height);
            break;
        }
        case Qt::PreferredSize: {
            int labelWidth = 0;
            int firstHeight = -1;
            foreach (const QString& s, ticksList) {
                QRect rect = labelBoundingRect(fn, s);
                labelWidth = qMax(rect.width(), labelWidth);
                height = rect.height();
                if (firstHeight < 0)
                    firstHeight = height;
            }
            width = labelWidth + labelPadding() + 2; //two pixels of tolerance
            width += base.width();
            height = qMax(height, qreal(firstHeight)) / 2.0;
            sh = QSizeF(width, height);
            break;
        }
        default:
        break;
    }

    return sh;
}

#include "moc_chartdatetimeaxisy_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
