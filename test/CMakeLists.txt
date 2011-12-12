add_executable(AgencyCheck AgencyCheck.c)
target_link_libraries(AgencyCheck fascn)

add_executable(fascnTest fascn.c)
target_link_libraries(fascnTest fascn)

add_executable(fascnOut fascnOut.c)
target_link_libraries(fascnOut fascn)

add_executable(fascnParse fascnParse.c)
target_link_libraries(fascnParse fascn)

add_test(AgencyCheckTest1 AgencyCheck)
