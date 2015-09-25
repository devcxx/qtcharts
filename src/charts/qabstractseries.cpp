/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtCharts/QAbstractSeries>
#include <private/qabstractseries_p.h>
#include <private/chartdataset_p.h>
#include <QtCharts/QChart>
#include <private/qchart_p.h>
#include <private/chartitem_p.h>
#include <private/xydomain_p.h>
#include <private/xlogydomain_p.h>
#include <private/logxydomain_p.h>
#include <private/logxlogydomain_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QAbstractSeries
    \inmodule Qt Charts
    \brief Base class for all Qt Chart series.

    Usually you use the series type specific inherited classes instead of the base class.
    \sa QXYSeries, QLineSeries, QSplineSeries, QScatterSeries, QAreaSeries, QAbstractBarSeries, QStackedBarSeries,
    QPercentBarSeries, QPieSeries
*/
/*!
    \qmltype AbstractSeries
    \instantiates QAbstractSeries
    \inqmlmodule QtCharts

    \brief Base class for all Qt Chart series.

    AbstractSeries is the base class for all series.
    The class cannot be instantiated by the user.
*/

/*!
    \enum QAbstractSeries::SeriesType

    The type of the series object.

    \value SeriesTypeLine
    \value SeriesTypeArea
    \value SeriesTypeBar
    \value SeriesTypeStackedBar
    \value SeriesTypePercentBar
    \value SeriesTypePie
    \value SeriesTypeScatter
    \value SeriesTypeSpline
    \value SeriesTypeHorizontalBar
    \value SeriesTypeHorizontalStackedBar
    \value SeriesTypeHorizontalPercentBar
    \value SeriesTypeBoxPlot
*/

/*!
    \property QAbstractSeries::type
    The type of the series.
*/
/*!
    \qmlproperty ChartView.SeriesType AbstractSeries::type
    The type of the series.
*/

/*!
    \property QAbstractSeries::name
    \brief name of the series property. The name is shown in legend for series and supports html formatting.
*/
/*!
    \qmlproperty string AbstractSeries::name
    Name of the series. The name is shown in legend for series and supports html formatting.
*/

/*!
    \fn void QAbstractSeries::nameChanged()
    This signal is emitted when the series name changes.
*/
/*!
    \qmlsignal AbstractSeries::onNameChanged()
    This signal is emitted when the series name changes.
*/

/*!
    \property QAbstractSeries::visible
    \brief whether the series is visible or not; true by default.
*/
/*!
    \qmlproperty bool AbstractSeries::visible
    Visibility of the series. True by default.
*/

/*!
    \fn void QAbstractSeries::visibleChanged()
    Emitted when the series visibility changes.
*/
/*!
    \qmlsignal AbstractSeries::onVisibleChanged()
    Emitted when the series visibility changes.
*/

/*!
    \property QAbstractSeries::opacity
    \brief The opacity of the series.

    By default the opacity is 1.0. The valid values range from 0.0 (transparent) to 1.0 (opaque).
*/
/*!
    \qmlproperty real AbstractSeries::opacity
    The opacity of the series. By default the opacity is 1.0.
    The valid values range from 0.0 (transparent) to 1.0 (opaque).
*/

/*!
    \fn void QAbstractSeries::opacityChanged()
    Emitted when the opacity of the series changes.
*/
/*!
    \qmlsignal AbstractSeries::onOpacityChanged()
    Emitted when the opacity of the series changes.
*/

/*!
    \property QAbstractSeries::useOpenGL
    \brief Specifies whether or not the series drawing is accelerated with OpenGL.

    Drawing series with OpenGL is supported only for QLineSeries and QScatterSeries.
    Line series used as edge series for a QAreaSeries cannot use OpenGL acceleration.
    When a chart contains any series that are drawn with OpenGL, a transparent QOpenGLWidget
    is created on top of the chart plot area. Specified series are not drawn on the underlying
    QGraphicsView, but are instead drawn on the created QOpenGLWidget.

    Performance gained from using OpenGL to accelerate series drawing depends on the underlying
    hardware, but in most cases it is significant. For example, on a standard desktop computer,
    enabling OpenGL acceleration for a series typically allows rendering at least hundred times
    more points without reduction on the frame rate.
    Chart size also has less effect on the frame rate.

    The OpenGL acceleration of series drawing is meant for use cases that need fast drawing of
    large numbers of points. It is optimized for efficiency, and therefore the series using
    it lack support for some features available to non-accelerated series.

    There are the following restrictions imposed on charts and series when using OpenGL
    acceleration:

    \list
    \li Series animations are not supported for accelerated series.
    \li Antialiasing is not supported for accelerated series.
    \li Pen styles and marker shapes are ignored for accelerated series.
        Only solid lines and plain scatter dots are supported.
        The scatter dots may be circular or rectangular, depending on the underlying graphics
        hardware and drivers.
    \li Polar charts are not supported for accelerated series.
    \li Since the accelerated series are drawn on top of the entire graphics view, they get drawn
        on top of any other graphics items that you may have on top chart in the same scene.
    \li To enable QOpenGLWidget to be partially transparent, it needs to be stacked on top of
        all other widgets. This means you cannot have other widgets partially covering the
        chart.
    \endlist

    The default value is \c{false}.
*/
/*!
    \qmlproperty bool AbstractSeries::useOpenGL
    Specifies whether or not the series is drawn with OpenGL.

    Drawing series with OpenGL is supported only for LineSeries and ScatterSeries.

    For more details, see QAbstractSeries::useOpenGL documentation. QML applications have similar
    restrictions as those listed in QAbstractSeries::useOpenGL documentation,
    except there is no restriction about covering the ChartView partially with other
    items due to different rendering mechanism.

    The default value is \c{false}.
*/

/*!
    \fn void QAbstractSeries::useOpenGLChanged()
    Emitted when the useOpenGL property value changes.
*/
/*!
    \qmlsignal AbstractSeries::onUseOpenGLChanged()
    Emitted when the useOpenGL property value changes.
*/

/*!
    \internal
    \brief Constructs QAbstractSeries object with \a parent.
*/
QAbstractSeries::QAbstractSeries(QAbstractSeriesPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

/*!
    \brief Virtual destructor for the chart series.
*/
QAbstractSeries::~QAbstractSeries()
{
    if (d_ptr->m_chart)
        qFatal("Series still bound to a chart when destroyed!");
}

void QAbstractSeries::setName(const QString &name)
{
    if (name != d_ptr->m_name) {
        d_ptr->m_name = name;
        emit nameChanged();
    }
}

QString QAbstractSeries::name() const
{
    return d_ptr->m_name;
}

void QAbstractSeries::setVisible(bool visible)
{
    if (visible != d_ptr->m_visible) {
        d_ptr->m_visible = visible;
        emit visibleChanged();
    }
}

bool QAbstractSeries::isVisible() const
{
    return d_ptr->m_visible;
}

qreal QAbstractSeries::opacity() const
{
    return d_ptr->m_opacity;
}

void QAbstractSeries::setOpacity(qreal opacity)
{
    if (opacity != d_ptr->m_opacity) {
        d_ptr->m_opacity = opacity;
        emit opacityChanged();
    }
}

void QAbstractSeries::setUseOpenGL(bool enable)
{
#ifdef QT_NO_OPENGL
    Q_UNUSED(enable)
#else
    bool polarChart = d_ptr->m_chart && d_ptr->m_chart->chartType() == QChart::ChartTypePolar;
    bool supportedSeries = (type() == SeriesTypeLine || type() == SeriesTypeScatter);
    if ((!enable || !d_ptr->m_blockOpenGL)
            && supportedSeries
            && enable != d_ptr->m_useOpenGL
            && (!enable || !polarChart)) {
        d_ptr->m_useOpenGL = enable;
        emit useOpenGLChanged();
    }
#endif
}

bool QAbstractSeries::useOpenGL() const
{
    return d_ptr->m_useOpenGL;
}

/*!
    \brief Returns the chart where series belongs to.

    Set automatically when the series is added to the chart
    and unset when the series is removed from the chart.
*/
QChart *QAbstractSeries::chart() const
{
    return d_ptr->m_chart;
}

/*!
    \brief Sets the visibility of the series to true.

    \sa setVisible(), isVisible()
*/
void QAbstractSeries::show()
{
    setVisible(true);
}

/*!
    \brief Sets the visibility of the series to false.

    \sa setVisible(), isVisible()
*/
void QAbstractSeries::hide()
{
    setVisible(false);
}

/*!
 Attach \a axis to the series.
 \return true if the axis was attached successfully, false otherwise.
 \note If multiple axes of same orientation are attached to same series,
       they will have same min/max ranges.
 \sa QChart::addAxis(), QChart::createDefaultAxes()
 */
bool QAbstractSeries::attachAxis(QAbstractAxis* axis)
{
    if(d_ptr->m_chart) {
        return d_ptr->m_chart->d_ptr->m_dataset->attachAxis(this, axis);
    } else {
        qWarning()<<"Series not in the chart. Please addSeries to chart first.";
        return false;
    }
}

/*!
 Detach \a axis from the series.
 \return true if the axis was detached successfully, false otherwise.
 \sa QChart::removeAxis()
 */
bool QAbstractSeries::detachAxis(QAbstractAxis* axis)
{
    if(d_ptr->m_chart) {
        return d_ptr->m_chart->d_ptr->m_dataset->detachAxis(this, axis);
    }
    else {
        qWarning()<<"Series not in the chart. Please addSeries to chart first.";
        return false;
    }
}

/*!
 Returns the list of axes attached to the series. Usually there is an x-axis and a y-axis attached to a series, except
 in case of a QPieSeries, which does not have any axes attached.
 \sa attachAxis(), detachAxis()
 */
QList<QAbstractAxis*> QAbstractSeries::attachedAxes()
{
    return d_ptr->m_axes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractSeriesPrivate::QAbstractSeriesPrivate(QAbstractSeries *q)
    : q_ptr(q),
      m_chart(0),
      m_item(0),
      m_domain(new XYDomain()),
      m_visible(true),
      m_opacity(1.0),
      m_useOpenGL(false),
      m_blockOpenGL(false)
{
}

QAbstractSeriesPrivate::~QAbstractSeriesPrivate()
{
}

void QAbstractSeriesPrivate::setDomain(AbstractDomain* domain)
{
    Q_ASSERT(domain);
    if(m_domain.data()!=domain) {
        if(!m_item.isNull()) QObject::disconnect(m_domain.data(), SIGNAL(updated()), m_item.data(), SLOT(handleDomainUpdated()));
        m_domain.reset(domain);
        if(!m_item.isNull()) {
            QObject::connect(m_domain.data(), SIGNAL(updated()),m_item.data(), SLOT(handleDomainUpdated()));
            m_item->handleDomainUpdated();
        }
    }
}

void QAbstractSeriesPrivate::setPresenter(ChartPresenter *presenter)
{
    m_presenter = presenter;
}

ChartPresenter *QAbstractSeriesPrivate::presenter() const
{
    return m_presenter;
}

void QAbstractSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_ASSERT(!m_item.isNull());
    Q_UNUSED(parent);
    QObject::connect(m_domain.data(), SIGNAL(updated()),m_item.data(), SLOT(handleDomainUpdated()));
}

void QAbstractSeriesPrivate::initializeAnimations(QChart::AnimationOptions options, int duration,
                                                  QEasingCurve &curve)
{
    Q_UNUSED(options);
    Q_UNUSED(duration);
    Q_UNUSED(curve);
}

bool QAbstractSeriesPrivate::reverseXAxis()
{
    bool reverseXAxis = false;
    if (m_axes.size() != 0 && !(m_chart->chartType() == QChart::ChartTypePolar)) {
        int i = 0;
        while (i < m_axes.size()) {
            if (m_axes.at(i)->orientation() == Qt::Horizontal && m_axes.at(i)->isReverse()) {
                reverseXAxis = true;
                break;
            }
            i++;
        }
    }

    return reverseXAxis;
}

bool QAbstractSeriesPrivate::reverseYAxis()
{
    bool reverseYAxis = false;
    if (m_axes.size() != 0 && !(m_chart->chartType() == QChart::ChartTypePolar)) {
        int i = 0;
        while (i < m_axes.size()) {
            if (m_axes.at(i)->orientation() == Qt::Vertical && m_axes.at(i)->isReverse()) {
                reverseYAxis = true;
                break;
            }
            i++;
        }
    }

    return reverseYAxis;
}

// This function can be used to explicitly block OpenGL use from some otherwise supported series,
// such as the line series used as edge series of an area series.
void QAbstractSeriesPrivate::setBlockOpenGL(bool enable)
{
    m_blockOpenGL = enable;
    if (enable)
        q_ptr->setUseOpenGL(false);
}

#include "moc_qabstractseries.cpp"
#include "moc_qabstractseries_p.cpp"

QT_CHARTS_END_NAMESPACE

