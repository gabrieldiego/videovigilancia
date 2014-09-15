// Downloadedd from https://github.com/MetaCipher/sdl-2.0-basics
#include <SDL2/SDL.h>

class App {
  private:
    static App Instance;
    bool Running;
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Surface* PrimarySurface;
    static const int WindowWidth = 1024;
    static const int WindowHeight = 768;
  private:
    App();
// Capture SDL Events
    void OnEvent(SDL_Event* Event);
// Initialize our SDL game / app
    bool Init();
// Logic loop
    void Loop();
// Render loop (draw)
    void Render();
// Free up resources
    void Cleanup();
  public:
    int Execute(int argc, char* argv[]);
  public:
    static App* GetInstance();
    static int GetWindowWidth();
    static int GetWindowHeight();
};

#include <stdio.h>
#define DEBUG 1
#ifdef DEBUG
#define Log(...) printf(__VA_ARGS__); printf("\n");
#else
#define Log(...) ;
#endif

App App::Instance;
//==============================================================================
App::App() {
  Running = true;
  Window = NULL;
  Renderer = NULL;
  PrimarySurface = NULL;
}
//------------------------------------------------------------------------------
void App::OnEvent(SDL_Event* Event) {
}
//------------------------------------------------------------------------------
bool App::Init() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    Log("Unable to Init SDL: %s", SDL_GetError());
    return false;
  }
  if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    Log("Unable to Init hinting: %s", SDL_GetError());
  }
  if((Window = SDL_CreateWindow(
        "My SDL Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
     ) == NULL) {
    Log("Unable to create SDL Window: %s", SDL_GetError());
    return false;
  }
  PrimarySurface = SDL_GetWindowSurface(Window);
  if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
    Log("Unable to create renderer");
    return false;
  }
  SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
  return true;
}
//------------------------------------------------------------------------------
void App::Loop() {
}
//------------------------------------------------------------------------------
void App::Render() {
  SDL_RenderClear(Renderer);
  SDL_RenderPresent(Renderer);
}
//------------------------------------------------------------------------------
void App::Cleanup() {
  if(Renderer) {
    SDL_DestroyRenderer(Renderer);
    Renderer = NULL;
  }
  if(Window) {
    SDL_DestroyWindow(Window);
    Window = NULL;
  }
  SDL_Quit();
}
//------------------------------------------------------------------------------
int App::Execute(int argc, char* argv[]) {
  if(!Init()) return 0;
  SDL_Event Event;
  while(Running) {
    while(SDL_PollEvent(&Event) != 0) {
      OnEvent(&Event);
      if(Event.type == SDL_QUIT) Running = false;
    }
    Loop();
    Render();
    SDL_Delay(1); // Breath
  }
  Cleanup();
  return 1;
}

//==============================================================================
App* App::GetInstance() { return &App::Instance; }
int App::GetWindowWidth() { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }

int main(int argc, char* argv[]) {
  return App::GetInstance()->Execute(argc, argv);
}

