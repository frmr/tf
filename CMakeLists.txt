cmake_minimum_required (VERSION 3.10)

add_library (tf STATIC
	src/tfBinaryFile.cpp
	src/tfCsvFile.cpp
	src/tfIniFile.cpp
	src/tfIniFile.hpp
	src/tfIniSection.cpp
	src/tfLogger.cpp
	src/tfString.cpp
	src/tfStringW.cpp
	src/tfTextFile.cpp
	src/tfTime.cpp
	src/tfTimer.cpp
)