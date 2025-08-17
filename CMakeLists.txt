cmake_minimum_required(VERSION 3.16)

project(filesystem-client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appfilesystem-client
    src/main.cpp

    src/core/appinitializer.h src/core/appinitializer.cpp
    src/core/session.h src/core/session.cpp
    src/core/sessionmanager.h src/core/sessionmanager.cpp

    src/models/fileinfo.h
    src/models/client.h
    src/models/fileexplorermodel.h src/models/fileexplorermodel.cpp
    src/models/clientexplorermodel.h src/models/clientexplorermodel.cpp

    src/network/iconnection.h
    src/network/protocol.h
    src/network/protocoltypes.h
    src/network/serialization.h

    src/services/explorerdataprovider.h src/services/explorerdataprovider.cpp
    src/services/localfileinfoprovider.h src/services/localfileinfoprovider.cpp

    src/viewmodels/mainviewmodel.h
    src/viewmodels/connectdialogviewmodel.h src/viewmodels/connectdialogviewmodel.cpp
    src/viewmodels/dataexplorerviewmodel.h src/viewmodels/dataexplorerviewmodel.cpp
)

qt_add_qml_module(appfilesystem-client
    URI filesystem-client
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/ConnectDialog.qml
        qml/DataExplorer.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appfilesystem-client PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appfilesystem-client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appfilesystem-client
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appfilesystem-client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
