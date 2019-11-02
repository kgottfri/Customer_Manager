import QtQuick 2.0
import QtQuick.Controls 2.0

//import backend.cpp 1.0

ApplicationWindow {

    id: root
    visibility: "Maximized"
    color: "#9a9494"
    title: "#Main"
    visible: true


    TextField {
        id: lastName
        x: 79
        y: 139
        text: ""
        placeholderText: qsTr("Last Name")


    }

    Button {
        signal submitTextField(var usr, var numDays)
        id: submit
        objectName: "submit"
        x: 80
        y: 353
        width: 314
        height: 91
        text: qsTr("Submit")
        display: AbstractButton.TextBesideIcon
        onClicked:{
            submitTextField(lastName.text,numDays.text)
            lastName.clear()
            numDays.clear()
        }
    }

    TextField {
        id: numDays
        x: 392
        y: 139
        text: qsTr("")
        placeholderText: "Number of Days"
    }

    Button {
        signal searchDb(var name)
        id: search
        objectName: "search"
        x: 494
        y: 353
        width: 326
        height: 91
        text: qsTr("Search")
        onClicked: {
            searchDb(lastName.text)

        }
    }

    Text {

        id: searchResult
        x: 638
        y: 204
        width: 174
        height: 90
        text: qsTr("")
        styleColor: "#ef2929"
        font.pixelSize: 12

    }
    Popup {
        contentItem: Text {
            id: slot
            text: " "
        }
        Button{
            id: ok
            x: 50
            y: 40
            width: 70
            height: 30
            text: qsTr("close")
            onClicked: {
                searchPop.close()
        }

        }

        id: searchPop
        x: 400
        y: 400
        width: 200
        height: 100
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
    Popup{
        contentItem: Text{
            id: addText
            text: " "
        }

        Button{
            id: closeDisplayAdd
            x: 80
            y: 40
            width: 70
            height: 30
            text: qsTr("close")
            onClicked: {
                displayAddWindow.close()
            }
        }
        id: displayAddWindow
        x: 400
        y: 400
        width: 250
        height: 100
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }

    function searchRes(user,resSlot){
        searchPop.open()
        slot.text = "Customer "+user+ " has slot "+resSlot
        return

    }
    function displayAdd(user,resSlot){
        displayAddWindow.open()
        addText.text = "Customer "+user+ " has been assigned slot: "+resSlot

        return

    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:1080;width:2560}D{i:3;anchors_width:120;anchors_x:83;anchors_y:0}
}
##^##*/
