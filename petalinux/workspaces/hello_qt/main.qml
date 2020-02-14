import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: window
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Hello World")

    Text {
        id: text
        text: qsTr("Welcome to inipro.net")
        anchors.centerIn: parent
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
    }
}
