import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 400
    height: 300
    visible: true
    title: "用户管理"

    ListView {
        anchors.fill: parent
        model: userAdapter.users // 绑定适配器的users属性
        delegate: Item {
            width: parent.width
            height: 40
            Text {
                text: "姓名：" + modelData.name + "，年龄：" + modelData.age
                font.pointSize: 12
            }
        }
    }

    TextField {
        id: nameInput
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: 150
        placeholderText: "输入姓名"
    }

    TextField {
        id: ageInput
        anchors.left: nameInput.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        width: 80
        placeholderText: "输入年龄"
        validator: IntValidator{}
    }

    Button {
        anchors.left: ageInput.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        text: "添加用户"
        onClicked: {
            userAdapter.addUser(nameInput.text, parseInt(ageInput.text));
            nameInput.text = "";
            ageInput.text = "";
        }
    }
}
