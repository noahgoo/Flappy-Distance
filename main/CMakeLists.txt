idf_component_register(SRCS main.c game.c bird.c ../resources/flappy_bird_bitmap.c pipe.c
                       INCLUDE_DIRS . ../resources
                       PRIV_REQUIRES config lcd sound pin esp_timer cursor)
# PRIV_REQUIRES ...
# target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
