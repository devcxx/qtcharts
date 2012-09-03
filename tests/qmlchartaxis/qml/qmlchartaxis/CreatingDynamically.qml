/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

import QtQuick 1.0
import QtCommercial.Chart 1.1

ChartView {
    id: chartView
    title: "creating dyn. new series"
    property int index: 0

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            switch (index) {
            case 0:
                while (chartView.count) {
                    console.log("Destroying series. Count: " + chartView.count);
                    chartView.series(0).destroy();
                }
                var line = chartView.createSeries(ChartView.SeriesTypeLine, "line");
                line.append(0, 0);
                line.append(1, 1);
                line.append(2, 2);
                line.append(3, 3);
                line.append(4, 4);
                break;
            case 1:
                chartView.axisX().min = 0;
                chartView.axisX().max = 4.5;
                chartView.axisY().min = 0;
                chartView.axisY().max = 4.5;
                break;
            default:
                var scatter = chartView.createSeries(ChartView.SeriesTypeScatter, "scatter");
                scatter.append(0, 0);
                scatter.append(0.5, 1);
                scatter.append(1, 2);
                scatter.append(1.5, 3);
                scatter.append(2, 4);
                scatter.append(1, 1);
                scatter.append(2, 2);
                scatter.append(3, 3);
                scatter.append(4, 4);
            }
            index = (index + 1) % 3;
        }
    }
}