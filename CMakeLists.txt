#  __   __  _______  ___      ___      _______          _______  ______    ___   _______  __    _  ______   ______
# |  | |  ||       ||   |    |   |    |       |        |       ||    _ |  |   | |       ||  |  | ||      | |      |
# |  |_|  ||    ___||   |    |   |    |   _   |        |    ___||   | ||  |   | |    ___||   |_| ||  _    ||___   |
# |       ||   |___ |   |    |   |    |  | |  |        |   |___ |   |_||_ |   | |   |___ |       || | |   |  __|  |
# |       ||    ___||   |___ |   |___ |  |_|  | ___    |    ___||    __  ||   | |    ___||  _    || |_|   | |_____|
# |   _   ||   |___ |       ||       ||       ||_  |   |   |    |   |  | ||   | |   |___ | | |   ||       |   __
# |__| |__||_______||_______||_______||_______|  |_|   |___|    |___|  |_||___| |_______||_|  |__||______|   |__|
#

cmake_minimum_required(VERSION 3.1..3.13)


################ START Main Settings ###################################
if(${CMAKE_VERSION} VERSION_LESS 3.12)                                 #
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})#
else()                                                                 #
    cmake_policy(VERSION 3.13)                                         #
endif()                                                                #
                                                                       #
project(dsp VERSION 1.0                                         #
  DESCRIPTION "Digital Signal Processing Library" #
                   LANGUAGES CXX)                                      #
# Set build type to debug build                                        #
# For the future, parametrize this option                              #
set(CMAKE_BUILD_TYPE Debug)                                            #
################ END Main Settings #####################################


################ START <Template> #######################################
#file(GLOB <TEMPLATE>_HPP "${CMAKE_SOURCE_DIR}/include/<template>/*.hpp")#
#file(GLOB <TEMPLATE>_CPP "${CMAKE_SOURCE_DIR}/src/<template>/*.cpp")    #
#                                                                        #
#add_library(<template> STATIC ${<TEMPLATE>_HPP} ${<TEMPLATE>_CPP})      #
#                                                                        #
#target_include_directories(<template> PUBLIC include/<template>)        #
#target_compile_features(<template> PUBLIC cxx_std_17)                   #
## set_target_properties(calculator PROPERTIES CXX_STANDARD 17)            #
################ END <Template> #########################################

################ START <Template> #######################################
file(GLOB SIGNAL_STATISTICS_HPP "${CMAKE_SOURCE_DIR}/include/SignalStatistics/*.hpp")#
file(GLOB SIGNAL_STATISTICS_CPP "${CMAKE_SOURCE_DIR}/src/SignalStatistics/*.cpp")    # #
add_library(SignalStatistics STATIC ${SIGNAL_STATISTICS_HPP} ${SIGNAL_STATISTICS_CPP})      #
                                                                        #
target_include_directories(SignalStatistics PUBLIC include/SignalStatistics)        #
target_compile_features(SignalStatistics PUBLIC cxx_std_17)                   #
target_compile_options(SignalStatistics PUBLIC -Wall -pedantic)
# set_target_properties(calculator PROPERTIES CXX_STANDARD 17)            #
################ END <Template> #########################################

################ START Executables #############################
#add_executable(calc apps/<exec-name-template>.cpp)                             #
#target_link_libraries(<exec-name-template> PUBLIC <template>)                  #

add_executable(sigstat apps/sigstat.cpp)                             #
target_link_libraries(sigstat PUBLIC SignalStatistics)                  #
################ END Executables ###############################

