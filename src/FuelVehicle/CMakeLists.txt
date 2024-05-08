add_library(FuelVehicle fuel_vehicle.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(ADWAITA REQUIRED libadwaita-1)

target_include_directories(FuelVehicle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${GTK4_INCLUDE_DIRS})

target_link_libraries(FuelVehicle 
    PUBLIC ${GTK4_LIBRARIES} 
    PUBLIC ${ADWAITA_LIBRARIES} 
    PRIVATE GtkUtils 
    PRIVATE StringFormatUtil 
    PRIVATE CalculateCarPriceUtil)

install(TARGETS FuelVehicle DESTINATION lib)
install(FILES fuel_vehicle.h DESTINATION include)