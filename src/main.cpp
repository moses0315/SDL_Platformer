#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return -1;
    }

    // SDL_image 초기화
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image 초기화 실패: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // 창 생성
    SDL_Window* window = SDL_CreateWindow("SDL2 Image Example",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "창 생성 실패: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "렌더러 생성 실패: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 이미지 로드
    SDL_Texture* texture = IMG_LoadTexture(renderer, "hello.png");
    if (!texture) {
        std::cerr << "이미지 로드 실패: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 렌더링 루프
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // 화면 지우기
        SDL_RenderClear(renderer);

        // 이미지 그리기
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // 렌더링
        SDL_RenderPresent(renderer);
    }

    // 자원 정리
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
