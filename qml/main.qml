import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import StephenQuan 1.0

Window {
    id: app

    visible: true
    width: 500
    height: 700
    title: qsTr("Qt FileDialog App")

    property var content: null
    property url fileUrl

    Page {
        anchors.fill: parent

        header: ToolBar {
            ToolButton {
                text: qsTr( "Back" )
                font.pointSize: 15
                enabled: stackView.depth > 1
                onClicked: stackView.pop()
            }
        }

        StackView {
            id: stackView

            anchors.fill: parent

            initialItem: Page {

                Button {
                    anchors.centerIn: parent

                    text: qsTr( "Start Qt FileDialog App" )
                    font.pointSize: 15

                    onClicked: stackView.push( "FileDialogTest.qml" );
                }
            }
        }
    }
}
