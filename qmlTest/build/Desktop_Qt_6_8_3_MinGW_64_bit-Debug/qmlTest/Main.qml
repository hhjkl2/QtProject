// Main.qml
import QtQuick 6.0
import QtCharts 6.0
//import QtCharts 6.2 as Charts
import QtQuick.Controls 6.0
import qmlTest 1.0

// Window {
//     visible: true
//     width: 640
//     height: 480
//     title: qsTr("Hello World")
//     color: "pink"

//     Button
//     {
//         id:quit
//         text:"Quit"
//         anchors.left:parent.left
//         anchors.leftMargin:4
//         anchors.bottom:parent.bottom
//         anchors.bottomMargin:4

//         onClicked:{
//             Qt.quit()
//         }
//     }

// }

Window {
    visible: true
    width: 640
    height: 480

    ChartView {
        anchors.fill: parent
        antialiasing: true

        BarSeries {
            axisX: BarCategoryAxis { categories: ["A", "B", "C"] }
            axisY: ValuesAxis { min: 0; max: 10 }

            BarSet { label: "Test"; values: [2, 5, 8] }
        }
    }
}

// Window {
//     visible: true
//     width: 800
//     height: 600
//     title: "Qt Charts 示例"
//     Charts.ChartView {
//         id: chartView
//         anchors.fill: parent
//         //theme: Charts.ChartView.ChartThemeMaterial
//         //animationOptions: Charts.ChartView.AllAnimations // 启用所有动画
//         animationDuration: 500
//         animationEasingCurve: Easing.OutBounce

//         property var barData: [30, 45, 20, 55, 38, 42]
//         property var barSets: [] // 规范声明

//         axes: [
//             // 横轴
//             Charts.BarCategoryAxis {
//                 id: xAxis
//                 titleText: "通道编号"
//                 categories: barData.map((_,i) => "通道" + (i+1))
//             },
//             // 纵轴
//             Charts.ValuesAxis {
//                 id: yAxis
//                 min: 0
//                 max: 60
//                 titleText: "数值"
//             }
//         ]

//         Charts.BarSeries {
//             id: barSeries

//             Component.onCompleted: {
//                 barData.forEach(function(value, index) {
//                     let barSet = barSeries.append("通道" + (index+1), [value])
//                     barSet.color = Qt.hsla(index/barData.length, 0.8, 0.6, 1)
//                     barSets.push(barSet)
//                 })
//             }

//             axisX: xAxis
//             axisY: yAxis
//         }

//         MouseArea {
//             anchors.fill: parent
//             onClicked: function(mouse) {
//                 if (msgLoader.item) {  // 增加空值检查
//                     const point = chartView.mapToValue(Qt.point(mouse.x, mouse.y), barSeries)
//                     const index = Math.floor(point.x)
//                     if (index >= 0 && index < barSeries.count) {
//                         msgLoader.item.text = "值：" + barSets[index].values[0]
//                         msgLoader.visible = true
//                     }
//                 }
//             }
//         }

//         Loader {
//             id: msgLoader
//             sourceComponent: MyMessageBox{}
//             visible: false
//         }

//         Timer {
//             interval: 1000
//             running: true
//             onTriggered: {
//                 barData = barData.map(function(value){
//                     const newVal = value + (Math.random() > 0.5 ? 5 : -5)
//                     return Math.max(0, Math.min(60, newVal))
//                 })
//                 barData.forEach(function(value, index){
//                     barSets[index].values = [value]
//                 })
//                 yAxis.max = Math.max(60, ...barData)
//             }
//         }
//     }
// }
