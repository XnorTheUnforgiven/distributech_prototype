cmake_minimum_required (VERSION 3.0.0)
 
project (Distributech)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})
 
set (SOURCE main.cpp ..\src\distributech\abstract.cpp ..\src\distributech\europe.cpp ..\src\distributech\northAmerica.cpp)
 
add_executable (${PROJECT_NAME} ${SOURCE})