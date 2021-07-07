import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480

    Connections {
        target: engTop

        onProgress: {
            progressBar.value = Math.ceil(percent)
            for (var i = 0; i < tops.length; i++)  {
                var el = tops[i]
                var maxRating = tops[0].rating
                var itemList = {word: el.word, rating: el.rating / maxRating}
                if (i > modelList.count) {
                    modelList.append(itemList)
                }
                else {
                    modelList.set(i, itemList)
                }
            }
        }

        onStop: {
            progressBar.value = 0
            progressBar.visible = false
        }
    }

    FileDialog {
        id: fileDialog
        title: "Выбор файла ..."
        nameFilters: ["*"]
        onAccepted: {
            modelList.clear()
            engTop.start(fileDialog.fileUrl)
            progressBar.visible = true
        }
    }

    GridLayout {
        id: gridLayout
        columns: 1
        anchors.fill: parent

        Button {
            Layout.fillWidth: true

            text: " Выбор файла "
            onClicked: {
                if (!engTop.isStart()) {
                    fileDialog.open();
                }
            }
        }

        ProgressBar {
            id: progressBar
            width: mainWindow.width

            Layout.fillWidth: true
            visible: false

            minimumValue: 0
            maximumValue: 100

            Text {
                text: progressBar.value + qsTr(" %")
                anchors.centerIn: parent
                Layout.fillWidth: true;
                Layout.fillHeight: true;
            }
        }

        ListModel {
            id: modelList
        }

        Component{
            id: vistaLista
            Rectangle{

                color: "lightsteelblue"
                width: parent.parent.width * rating
                height: parent.parent.height / modelList.count - 2
                border.color: "blue"
                border.width: 1

                Text {
                    text: qsTr(word)
                    anchors.centerIn: parent
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                }
            }
        }

        Rectangle{
            id: contenedor
            Layout.fillHeight: true
            Layout.fillWidth: true

            ListView {
                id: list
                height: list.height
                spacing: 2
                model: modelList
                delegate: vistaLista
                anchors.fill: parent
                highlightRangeMode: ItemView.NoHighlightRange
                boundsBehavior: Flickable.StopAtBounds
            }
        }
    }
}
