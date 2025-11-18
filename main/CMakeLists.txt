idf_component_register(SRCS main.c game.c bird.c ../resources/flappy_bird_bitmap.c
                       INCLUDE_DIRS . ../resources
                       PRIV_REQUIRES config lcd sound pin esp_timer)
# PRIV_REQUIRES ...
# target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
