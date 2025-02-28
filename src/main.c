#include "init.h"
#include <stdio.h>
#include <stdlib.h>

void init_snake(snake_t *snake)
{
    snake->length = 1;
    snake->direction = (sfVector2f){20, 0};
    snake->head = malloc(sizeof(segment_t));

    if (!snake->head) {
        printf("Memory allocation error.\n");
        return;
    }
    snake->head->position = (sfVector2f){100, 100};
    snake->head->next = NULL;
}

void init_window(window_t *window)
{
    window->video_mode = (sfVideoMode){1080, 920, 32};
    window->window = sfRenderWindow_create(window->video_mode, "Snake::RE", sfResize | sfClose, NULL);
    window->font = sfFont_createFromFile("font.otf");

    if (!window->window) {
        printf("Error while creating the window.\n");
        return;
    }
    sfRenderWindow_setFramerateLimit(window->window, 10);
    init_snake(&window->snake);
    window->score = 0;
    window->food.position = (sfVector2f){400, 400};
}

void render_snake(window_t *window)
{
    segment_t *current = window->snake.head;

    while (current) {
        sfRectangleShape *rect = sfRectangleShape_create();
        sfRectangleShape_setSize(rect, (sfVector2f){20, 20});
        sfRectangleShape_setPosition(rect, current->position);
        sfRectangleShape_setFillColor(rect, sfGreen);
        sfRenderWindow_drawRectangleShape(window->window, rect, NULL);
        sfRectangleShape_destroy(rect);
        current = current->next;
    }
}


void handle_input(window_t *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window->window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyLeft && window->snake.direction.x == 0)
                window->snake.direction = (sfVector2f){-20, 0};
            if (event.key.code == sfKeyRight && window->snake.direction.x == 0)
                window->snake.direction = (sfVector2f){20, 0};
            if (event.key.code == sfKeyUp && window->snake.direction.y == 0)
                window->snake.direction = (sfVector2f){0, -20};
            if (event.key.code == sfKeyDown && window->snake.direction.y == 0)
                window->snake.direction = (sfVector2f){0, 20};
        }
    }
}

void render_food(window_t *window)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){20, 20});
    sfRectangleShape_setPosition(rect, window->food.position);
    sfRectangleShape_setFillColor(rect, sfRed);
    sfRenderWindow_drawRectangleShape(window->window, rect, NULL);
    sfRectangleShape_destroy(rect);
}



void update_snake(window_t *window)
{
    segment_t *new_head = malloc(sizeof(segment_t));
    segment_t *current = window->snake.head;
    int count = 1;

    if (!new_head) {
        printf("Memory allocation error while adding segment.\n");
        return;
    }
    new_head->position = window->snake.head->position;
    new_head->next = window->snake.head;
    window->snake.head = new_head;
    window->snake.head->position.x += window->snake.direction.x;
    window->snake.head->position.y += window->snake.direction.y;
    while (current->next && count < window->snake.length) {
        current = current->next;
        count++;
    }
    current->next = NULL;
}

void render_window(window_t *window)
{
    sfRenderWindow_clear(window->window, sfBlack);
    render_snake(window);
    render_food(window);
    sfRenderWindow_display(window->window);
}

void check_food_collision(window_t *window)
{
    if (window->snake.head->position.x == window->food.position.x && window->snake.head->position.y == window->food.position.y) {
        window->snake.length++;
        window->food.position = (sfVector2f){(rand() % 50) * 20, (rand() % 45) * 20};
    }
}

int main(void)
{
    window_t window;
    init_window(&window);
    segment_t *current = window.snake.head;

    while (sfRenderWindow_isOpen(window.window)) {
        handle_input(&window);
        update_snake(&window);
        check_food_collision(&window);
        render_window(&window);
    }
    while (current) {
        segment_t *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}
