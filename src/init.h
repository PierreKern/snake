#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Audio.h>

typedef struct segment_s {
    sfVector2f position;
    struct segment_s *next;
} segment_t;

typedef struct snake_s {
    segment_t *head;
    sfVector2f direction;
    int length;
} snake_t;

typedef struct food_s {
    sfVector2f position;
} food_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfVideoMode video_mode;
    snake_t snake;
    food_t food;
    int score;
    sfFont *font;
} window_t;

