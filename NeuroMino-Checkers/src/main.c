/**
 * NeuroMino Checkers - Main Entry Point
 * 
 * This file contains the main entry point for the checkers game.
 * Stage 4: SDL Initialization - Initialize SDL, create window and renderer
 */

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "GuiNN Checkers v1.0.0"

// Global SDL variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

/**
 * Initialize SDL and create window and renderer
 * 
 * @return true if initialization succeeded, false otherwise
 */
bool init_sdl() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    printf("SDL initialized successfully\n");
    
    // Create window
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    printf("Window created successfully\n");
    
    // Create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    printf("Renderer created successfully\n");
    
    // Set renderer color
    SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xFF);
    
    return true;
}

/**
 * Clean up SDL resources
 */
void cleanup_sdl() {
    printf("Cleaning up SDL resources...\n");
    
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        printf("Renderer destroyed\n");
    }
    
    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
        printf("Window destroyed\n");
    }
    
    SDL_Quit();
    printf("SDL quit successfully\n");
}

/**
 * Main game loop
 */
void game_loop() {
    bool running = true;
    SDL_Event e;
    
    printf("Entering game loop...\n");
    
    while (running) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    printf("Quit event received\n");
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        printf("Escape key pressed, exiting...\n");
                        running = false;
                    }
                    break;
                
                default:
                    break;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xFF);
        SDL_RenderClear(renderer);
        
        // Draw something simple - a white rectangle
        SDL_Rect test_rect = {100, 100, 200, 200};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &test_rect);
        
        // Present the screen
        SDL_RenderPresent(renderer);
    }
    
    printf("Game loop exited\n");
}

/**
 * Main entry point
 */
int main(int argc, char* argv[]) {
    printf("\n");
    printf("==========================================\n");
    printf("GuiNN Checkers - Starting...\n");
    printf("==========================================\n");
    printf("\n");
    
    // Initialize SDL
    if (!init_sdl()) {
        fprintf(stderr, "Failed to initialize SDL!\n");
        return 1;
    }
    
    // Run game loop
    game_loop();
    
    // Clean up
    cleanup_sdl();
    
    printf("\n");
    printf("==========================================\n");
    printf("NeuroMino Checkers - Exited successfully\n");
    printf("==========================================\n");
    printf("\n");
    
    return 0;
}
