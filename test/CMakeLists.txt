add_executable(AgencyCheck AgencyCheck.c)
target_link_libraries(AgencyCheck fascn)

add_executable(fascnTest fascn.c)
target_link_libraries(fascnTest fascn)

add_executable(fascnOut fascnOut.c)
target_link_libraries(fascnOut fascn)

add_executable(fascnParse fascnParse.c)
target_link_libraries(fascnParse fascn)

add_test(fascn
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fascnTest
  0032            # AGENCY CODE
  0001            # SYSTEM CODE
  092446          # CREDENTIAL NUMBER
  0               # CREDENTIAL SERIES
  1               # INDIVIDUAL CREDENTIAL ISSUE
  1112223333      # PERSONAL IDENTIFIER
  1               # ORGANIZATIONAL CATEGORY
  1223            # ORGANIZATIONAL IDENTIFIER
  2               # PERSON/ORGANIZATION
  7               # LRC = Calculated Value, Redundancy Check
  "11010 00001 00001 11001 01000 10110 00001 00001 00001 10000 10110 00001 10011 01000 00100 00100 01101 10110 00001 10110 10000 10110 10000 10000 10000 01000 01000 01000 11001 11001 11001 11001 10000 10000 01000 01000 11001 01000 11111 11100" # Expected output
  )


add_test(fascnOut
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fascnOut
  0032            # AGENCY CODE
  0001            # SYSTEM CODE
  092446          # CREDENTIAL NUMBER
  0               # CREDENTIAL SERIES
  1               # INDIVIDUAL CREDENTIAL ISSUE
  1112223333      # PERSONAL IDENTIFIER
  1               # ORGANIZATIONAL CATEGORY
  1223            # ORGANIZATIONAL IDENTIFIER
  2               # PERSON/ORGANIZATION
  ${PROJECT_SOURCE_DIR}/test/fascn.dat
  )


add_test(fascnParse
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fascnParse
  ${PROJECT_SOURCE_DIR}/test/fascn.dat
  )


add_test(AgencyCheck
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AgencyCheck
  ${PROJECT_SOURCE_DIR}/test/fascn.dat
  )

