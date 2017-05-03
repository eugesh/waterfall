
cmake_minimum_required (VERSION 2.8.11)

project (image_viewer CXX)

include (FindPkgConfig)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Release")
endif ()

if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif ()

if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif ()

if (NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif ()

set (QTLIBS QtGui QtCore QtNetwork)
find_package (Qt4 REQUIRED)
# qt4_wrap_cpp (MOC_SOURCES ${HEADERS})
include(${QT_USE_FILE})

pkg_check_modules (GLIB2 REQUIRED "glib-2.0 gobject-2.0 gthread-2.0 gio-2.0")
pkg_check_modules (LIBXML2 REQUIRED "libxml-2.0")
add_definitions (${GLIB2_CFLAGS} ${LIBXML2_CFLAGS})
link_directories (${GLIB2_LIBRARY_DIRS} ${LIBXML2_LIBRARY_DIRS})

find_package( GDAL )
include_directories( ${GDAL_INCLUDE_DIRS} )

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscancore/hyscancore")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscantypes/hyscantypes")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscandb/hyscandb")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscancache/hyscancache")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscanmath/hyscanmath")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../pycppwrapper/pycppwrapper")

link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscancore/bin")
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscantypes/bin")
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscandb/bin")
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscancache/bin")
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../libhyscanmath/bin")
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../pycppwrapper/bin")
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set (ADDON_LIBRARIES ${ADDON_LIBRARIES} hyscantypes hyscandb hyscancache hyscanmath hyscancore cpp_acoustic_wrap cpp_bd_wrap)

add_definitions (-DG_LOG_DOMAIN="ImageViewer")
add_subdirectory ("source")
add_subdirectory ("graphic_item_image")
