import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts 2.3


Window {
    id:root
    minimumWidth: 1150
    minimumHeight: 500
    maximumWidth: 1150
    maximumHeight: 500
    visible: true
    title: qsTr("Soroush Game")
    color: "#CACACA"

    ColumnLayout
    {
        id:socketstatus
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 40

        RoundButton
        {
            height: 2
            width:  2
            radius: 50
            background: Rectangle{
                color: "yellow"
                radius: 50
            }
        }
    }



    Item{
        id: maincontainer
        width: parent.width-100
        height: parent.height
        anchors.centerIn: parent


        Rectangle
        {
            id: clientdata
            anchors.top: maincontainer.top
            height: 100
            width: maincontainer.width
            border.width: 0
            color: "#136597"

            RowLayout{
                anchors.centerIn: parent
                TextField{
                    placeholderText: "name"
                    onTextChanged:
                    {

                    }
                }
                TextField{
                    placeholderText: "family"
                }

                ComboBox
                {
                    id: combo
                    model: ["easy","hard"]
                    onCurrentIndexChanged:
                    {


                    }
                }
            }
        }


        Rectangle
        {
            id:chartcontainer
            visible: true
            anchors.top: clientdata.bottom
            anchors.topMargin: 6
            height: 410
            width: maincontainer.width

            ChartView {
                title: "Two Series, Common Axes"
//                anchors.fill: parent
                width: maincontainer.width
                height: maincontainer.height -200
                legend.visible: false
                antialiasing: true

                ValuesAxis {
                    id: axisX
                    min: 0
                    max: 10
                    tickCount: 5
                }

                ValuesAxis {
                    id: axisY
                    min: -0.5
                    max: 1.5
                }

                LineSeries {
                    id: series1
                    axisX: axisX
                    axisY: axisY
                }
            }

            // Add data dynamically to the series
            Component.onCompleted: {
                for (var i = 0; i <= 20; i++) {
                    series1.append(i, Math.random());
                    //            series2.append(i, 5);
                }
            }
        }
    }
}
