add_library(NewEnergyVehicles new_energy_vehicles.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(ADWAITA REQUIRED libadwaita-1)

target_include_directories(NewEnergyVehicles INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${GTK4_INCLUDE_DIRS})

target_link_libraries(NewEnergyVehicles 
    PUBLIC ${GTK4_LIBRARIES} 
    PUBLIC ${ADWAITA_LIBRARIES}  
    PRIVATE GtkUtils 
    PRIVATE StringFormatUtil
    PRIVATE CalculateCarPriceUtil)

install(TARGETS NewEnergyVehicles DESTINATION lib)
install(FILES new_energy_vehicles.h DESTINATION include)