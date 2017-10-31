
add_library (image_item SHARED graphic_item_image.cpp)

target_link_libraries (image_item ${ADDON_LIBRARIES} ${GDAL_LIBRARY} ${QT_LIBRARIES} ${OpenCV_LIBS})

set_target_properties (image_item PROPERTIES DEFINE_SYMBOL "HYSCAN_API_EXPORTS")
