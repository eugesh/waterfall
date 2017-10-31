include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/source")

set (HEADERS
	 cthread.h
	 Krest_scene.h
	 Krest_window.h)

QT4_WRAP_UI(UISrcs ${CMAKE_CURRENT_SOURCE_DIR}/../form_ui/form_mainwindow.ui)

# QT4_WRAP_CPP(MOCSrcs HEADERS)
QT4_WRAP_CPP(MOCSrcs cthread.h)
QT4_WRAP_CPP(MOCSrcs Krest_scene.h)
QT4_WRAP_CPP(MOCSrcs Krest_window.h)
QT4_WRAP_CPP(MOCSrcs sonar_emu_thread.h)

add_executable (img_viewer
	            cthread.cpp
	            sonar_emu_thread.cpp
	            Krest_scene.cpp
	            Krest_window.cpp
	            krest.cpp
	            krestview.cpp
	            RubberRect.cpp
	            main.cpp
	            ${MOCSrcs} ${UISrcs})

target_link_libraries (img_viewer ${ADDON_LIBRARIES} ${GLIB2_LIBRARIES} ${HYSCAN_LIBRARIES} ${QTLIBS} ${QT_LIBRARIES} ${GDAL_LIBRARY} ${OpenCV_LIBS} image_item)
# target_link_libraries (img_viewer ${ADDON_LIBRARIES} ${GLIB2_LIBRARIES} ${HYSCAN_LIBRARIES} ${QTLIBS} ${QT_LIBRARIES} ${GDAL_LIBRARY} image_item)
# set_target_properties (img_viewer PROPERTIES DEFINE_SYMBOL "HYSCAN_API_EXPORTS")
