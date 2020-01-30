import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import StephenQuan 1.0

Page {
    id: fileDialogTest

    property var content: null
    property url fileUrl

    Flickable {
        id: flickable

        anchors.fill: parent
        anchors.margins: 10

        contentWidth: columnLayout.width
        contentHeight: columnLayout.height
        clip: true

        ColumnLayout {
            id: columnLayout

            width: flickable.width
            spacing: 10

            Text {
                Layout.alignment: Qt.AlignRight
                text: qsTr( "AppFramework %1" ).arg( AppFramework.version )
                font.pointSize: 8
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: "black"
            }

            Text {
                text: qsTr( "FileUrl" )
                font.bold: true
                font.pointSize: 15
            }

            Text {
                id: fileUrlProperties
                Layout.maximumWidth: parent.width
                font.pointSize: 15
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Flow {
                Layout.alignment: Qt.AlignRight
                Layout.maximumWidth: parent.width
                spacing: 10

                Button {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr( "Copy" )
                    font.pointSize: 15
                    onClicked: AppFramework.copyToClipboard( fileDialog.fileUrl )
                }

                Button {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr( "FileDialog" )
                    font.pointSize: 15
                    onClicked: fileDialog.open()
                }

            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: "black"
            }

            Text {
                text: qsTr( "File" )
                font.bold: true
                font.pointSize: 15
            }

            Text {
                id: fileProperties
                Layout.maximumWidth: parent.width
                font.pointSize: 15
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: "black"
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: qsTr( "Copy" )
                font.pointSize: 15
                enabled: fileDialogTest.fileUrl
                onClicked: AppFramework.copyToClipboard( fileProperties.text )
            }

            Text {
                text: qsTr( "FileInfo" )
                font.bold: true
                font.pointSize: 15
            }

            Text {
                id: fileInfoProperties
                Layout.maximumWidth: parent.width
                font.pointSize: 15
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: qsTr( "Copy" )
                font.pointSize: 15
                enabled: fileDialogTest.fileUrl
                onClicked: AppFramework.copyToClipboard( fileInfoProperties.text )
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: "black"
            }

            Text {
                text: qsTr( "Content" )
                font.bold: true
                font.pointSize: 15
            }

            Text {
                Layout.maximumWidth: parent.width
                font.pointSize: 15
                text: fileDialogTest.content || ""
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: qsTr( "Read" )
                font.pointSize: 15
                enabled: fileDialogTest.fileUrl

                onClicked: {
                    let file = AppFramework.file( fileDialogTest.fileUrl );
                    fileDialogTest.content = file.readAll();
                }
            }

        }
    }

    FileDialog {
        id: fileDialog

        onAccepted: updateAppWithFileUrl( fileUrl );
    }

    Component.onCompleted: {
        let fileUrl = AppFramework.loadFromSettings( "fileUrl" );
        if ( fileUrl ) {
            updateAppWithFileUrl( fileUrl );

        }
    }

    function updateAppWithFileUrl( fileUrl ) {
        fileDialogTest.content = null;
        fileDialogTest.fileUrl = fileUrl;

        let info = [
                "url: %1".arg( JSON.stringify( fileUrl ) )
            ];
        fileUrlProperties.text = info.join( "\n" );

        let file = AppFramework.file( fileUrl );
        info = [
                "canRead: %1".arg( JSON.stringify( file.canRead ) ),
                "exists: %1".arg( JSON.stringify( file.exists ) ),
                "fileName: %1".arg( JSON.stringify( file.fileName ) ),
                "size: %1".arg( JSON.stringify( file.size ) ),
                ];
        fileProperties.text = info.join( "\n" );

        let fileInfo = AppFramework.fileInfo( fileUrl );
        info = [
                "absolutePath: %1".arg( JSON.stringify( fileInfo.absolutePath ) ),
                "absoluteFilePath: %1".arg( JSON.stringify( fileInfo.absoluteFilePath ) ),
                "baseName: %1".arg( JSON.stringify( fileInfo.baseName ) ),
                "exists: %1".arg( JSON.stringify( fileInfo.exists ) ),
                "fileName: %1".arg( JSON.stringify( fileInfo.fileName ) ),
                "filePath: %1".arg( JSON.stringify( fileInfo.filePath ) ),
                "size: %1".arg( JSON.stringify( fileInfo.size ) ),
                ];
        fileInfoProperties.text = info.join( "\n" );

        AppFramework.saveToSettings( "fileUrl", fileUrl );
    }
}
