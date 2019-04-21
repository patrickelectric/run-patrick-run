import QtQuick 2.1

import org.kde.kirigami 2.4 as Kirigami
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

import GpxManager 1.0

Kirigami.ApplicationWindow {
    id: root
    property int defaultColumnWidth: Kirigami.Units.gridUnit * 20
    property int columnWidth: defaultColumnWidth
    pageStack.defaultColumnWidth: columnWidth
    pageStack.initialPage: pageMap
    pageStack.globalToolBar.style: Kirigami.ApplicationHeaderStyle.None

    contextDrawer: Kirigami.OverlayDrawer {
        edge: Qt.RightEdge
        handleClosedIcon.source: "configure"

        contentItem: Item {
            implicitWidth: Kirigami.Units.gridUnit * 20
            ColumnLayout {
                width: parent.width
                ComboBox {
                    Layout.fillWidth: true
                    model: map.plugin.availableServiceProviders
                    // There is a big in kirigami overlay
                    // this line is necessary
                    popup.z: 9999
                    onCurrentTextChanged: {
                        print(currentText)
                        //map.plugin.name = currentText
                    }
                }
                CheckBox {
                    text: "potato"
                }
            }
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            id: plugin
            name: "mapbox"
            PluginParameter { name : "mapbox.access_token"; value: "pk.eyJ1IjoianJvbWlvbiIsImEiOiJjajk4YWMzazMwcjA5MnFxc2xpc2p0ZDg0In0.Ikd1UkS5-NvY1V63e3VZwA" }
            PluginParameter { name : "mapbox.mapping.highdpi_tiles"; value: true }
            Component.onCompleted: print(availableServiceProviders)
        }

        center: src.position.coordinate

        zoomLevel: 10

        PositionSource {
            id: src
            updateInterval: 3000
            active: true

            onPositionChanged: {
                var coord = position.coordinate
                console.log("New coordinate:", coord.longitude, coord.latitude);
            }
        }

        MapPolyline {
            line.width: 3
            line.color: 'green'
            path: GpxManager.path
            onPathChanged: {
                map.center = path[0]
                map.zoomLevel = 14
            }

        }

        DropArea {
            id: dropArea
            anchors.fill: parent
            keys: ["text/plain"]
            onEntered: print('entered')
            onDropped: {
                print(drop.text)
                GpxManager.open(drop.text)
            }
        }
    }

    Component {
        id: pageMap

        Kirigami.Page {
            id: kirigamiPageMap
            background: map
        }
    }
}