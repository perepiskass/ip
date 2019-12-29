# определяем минимальную версию для компиляции
cmake_minimum_required(VERSION 3.2)

# НАЗНАЧАЕМ ИМЯ ПРОЕКТУ И УСТАНАВЛИВАЕМ НОМЕР ВЕРСИИ------------------------
# если определена среда сборки Travis то выставляем номер сборки из Travis
if($ENV{TRAVIS_BUILD_NUMBER})
project(IP_UTILITY VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# если среда не найдена то ставим номер сборки указанный ниже
else()
project(IP_UTILITY VERSION 0.0.5)
endif()
# --------------------------------------------------------------------------

# ДОБАВЛЯЕМ В ПРОЕКТ ДОПОЛНИТЕЛЬНЫЕ БИБЛИОТЕКИ ДЛЯ ТЕСТИРОВАНИЯ-------------
# Опция "REQUIRED" говорит о том, что библиотека необходима проекту. Без нее cmake решит, что отсутствие данной библиотеки - не так уж и страшно, и будет собирать дальше.
# Добовляем в проект библиотеку Boost и нужный в ней компонент unit_test_framework (если нужен другой то пишем через пробел)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads)
# Добавим директории с хедерами Boost, gtest и директорию с исходниками для поиска в них хедеров
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
# --------------------------------------------------------------------------


configure_file(version.h.in version.h)

# СОЗДАЕМ ИСПОЛНЯЕМЫЕ ФАЙЛЫ И ДОБОВЛЯЕМ БИБЛИОТЕКИ В ПРОЕКТ-----------------
# Создаем исполняемый фаил ip_utility из main.cpp
add_executable(ip_utility main.cpp)
# Создаем библиотеку с именем version из источника - файла с именем lib.cpp
add_library(versionlib lib.cpp)
# Создаем библиотеку с именем ipclass из источника - файла с именем ip.cpp
add_library(ipclass ip.cpp)
# Создаем исполняемый фаил test_version из test_version.cpp
add_executable(test_version test_version.cpp)
# Создаем исполняемый фаил gtest_version из gtest_version.cpp
add_executable(gtest_version  gtest_version.cpp)
# --------------------------------------------------------------------------


# УСТАНАВЛИВАЕМ СВОЙСТВА ДЛЯ КОМПИЛЯЦИИ ИСПОЛНЯЕМЫМ ФАЙЛАМ И БИБЛИОТЕКАМ----

set_target_properties(ip_utility versionlib ipclass test_version gtest_version PROPERTIES
# Стандарт С++ версии 14
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(versionlib
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_include_directories(ipclass
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_utility PRIVATE
    versionlib
)
target_link_libraries(ip_utility PRIVATE
    ipclass
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    versionlib
)
target_link_libraries(gtest_version
    ${GTEST_LIBRARIES}
    versionlib
)
target_link_libraries(gtest_version
${CMAKE_THREAD_LIBS_INIT}
versionlib )


if (MSVC)
    target_compile_options(ip_utility PRIVATE
        /W4
    )
    target_compile_options(versionlib PRIVATE
        /W4
    )
    target_compile_options(ipclass PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
    target_compile_options(gtest_version PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_utility PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(versionlib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ipclass PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest_version PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

# ----------------------------------------------------------------------

install(TARGETS ip_utility RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT sise07@gmail.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
add_test(gtest_version gtest_version)
