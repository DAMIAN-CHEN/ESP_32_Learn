set(src_dirs
            ECHO
            LCD
            LED
            SPI
            TM1637
            BUZZER)

set(include_dirs
            ECHO
            LCD
            LED
            SPI
            TM1637
            BUZZER)

set(requires
            driver
            esp_timer)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O0 -Wno-error=format=-Wno-format)