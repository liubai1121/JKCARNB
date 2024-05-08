add_library(GtkUtils gtkutil.c)
add_library(StringFormatUtil stringformatutil.c)
add_library(CalculateCarPriceUtil calculatecarpriceutil.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MPFR REQUIRED mpfr)
pkg_check_modules(GMP REQUIRED gmp)
pkg_check_modules(GTK4 REQUIRED gtk4)


target_include_directories(GtkUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${GTK4_INCLUDE_DIRS})
target_include_directories(StringFormatUtil INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories(CalculateCarPriceUtil INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GtkUtils PRIVATE ${GTK4_LIBRARIES})
target_link_libraries(CalculateCarPriceUtil PRIVATE ${MPFR_LIBRARIES} PRIVATE ${GMP_LIBRARIES})

install(TARGETS GtkUtils StringFormatUtil CalculateCarPriceUtil DESTINATION lib)
install(FILES stringformatutil.h gtkutil.h calculatecarpriceutil.h DESTINATION include)