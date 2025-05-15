import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("订单管理系统（代理模式示例）")

    property var proxyModel:cppProxyModel

    ListView{
        anchors.fill: parent
        model: proxyModel
        delegate: Row{
            width: parent.width
            spacing: 20
            Text { text: model.id; width: 150 }     // ID列
            Text { text: model.time; width: 180 }   // 时间列
            Text { text: model.status; width: 120 } // 状态列
            Text { text: model.amount; width: 100 } // 金额列
        }
    }

    Component.onCompleted: {
        console.log("Model row count:", proxyModel.rowCount());
        if (proxyModel.rowCount() > 0) {
            console.log("First item id:", proxyModel.data(proxyModel.index(0, 0), 0x0101 /*IdRole*/));
        }
    }
}
