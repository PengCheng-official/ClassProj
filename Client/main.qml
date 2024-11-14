import QtQuick 2.15
import QtQuick.Controls 2.15
import "./FluentUI/Controls"

Column{
    spacing: 10
    TextField{
        placeholderText: "TextField"
    }
    TextBox{
        placeholderText: "TextBox"
    }
    TextBox{
        placeholderText: "TextBox"
        FluentUI.trailing: IconButton{
            implicitWidth: 30
            implicitHeight: 20
            icon.name: FluentIcons.graph_Search
            icon.width: 12
            icon.height: 12
        }
    }
    TextBox{
        placeholderText: "TextBox"
        FluentUI.leading: IconButton{
            implicitWidth: 30
            implicitHeight: 20
            icon.name: FluentIcons.graph_Search
            icon.width: 12
            icon.height: 12
        }
    }
}
