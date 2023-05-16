import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts 2.3
import Viewmodels 1.0



Window {
    property Viewmodel mymodel: mainviewmodel
    property var newpoints: mymodel.mypoint
    property int c: 0
    property real lastmax: 0

    onNewpointsChanged:
    {
//        console.log("newpoints[c]",newpoints[c])

        if(mymodel.currentstauts==="green")
        {
//            for( c ; c<newpoints.length ; ++c)
//            {
                if(!isNaN(newpoints[c]) && !isNaN(newpoints[c+1]))
                {
                    console.log("newpoints[c]" , newpoints[c])
                    console.log("newpoints[c+1]" , newpoints[c+1])
                    series1.append(newpoints[c+1], newpoints[c]);
                    if(axisY.max<newpoints[c])
                    {
                        axisY.max=newpoints[c]
                    }
                    c+=2;
                }
//            }
        }
    }


    id:root
    minimumWidth: 1150
    minimumHeight: 500
    maximumWidth: 1150
    maximumHeight: 500
    visible: true
    title: qsTr("Soroush server Game")
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
                color: mymodel.currentstauts
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
                spacing: 10
                Text {
                    id: name
                    text: mymodel.namefamliy[0]
                    font.pixelSize: 20
                    color: "white"
                }
                Text {
                    id: family
                    text: mymodel.namefamliy[1]
                    font.pixelSize: 20
                    color: "white"
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
                id:charts
                enabled: false
                title: "Two Series, Common Axes"
                //                anchors.fill: parent
                width: maincontainer.width
                height: maincontainer.height -200
                legend.visible: false
                antialiasing: true

                ValuesAxis {
                    id: axisX
                    min: 0
                    max: newpoints.length > 0 ? newpoints[newpoints.length-1] : 0
                    tickCount: 10
                }

                ValuesAxis {
                    id: axisY
                    min: 0
                    max:15
                }

                LineSeries {
                    id: series1
                    axisX: axisX
                    axisY: axisY
                }

            }
            Rectangle {
                id:footer
                width: parent.width
                anchors.bottom:parent.bottom
                height: 100
                color: "#136597"
                RowLayout{
                    spacing: 100
                    anchors.centerIn: parent
                    Button
                    {
                        text: "Import File"
                        Layout.minimumWidth: 120
                        Layout.minimumHeight: 40
                        onClicked:
                        {

                        }
                    }
                }
            }
        }
    }
}

