#include "Window.h"

 static Game* game;

RenderingEngine* Window::renderingEngine;

int32_t Window::WIDTH=0;
int32_t Window::HEIGHT=0;


int32_t Window::GetWindowWidth(){
	return WIDTH;
}

int32_t Window::GetWindowHeight(){

	return HEIGHT;
}

void Window::OnFocus(){

	game->OnFocus();

}
void Window::OnLoseFocus(){

	game->OnLoseFocus();
}

void Window::WindowAwake(){

	game=new Game();

}

void Window::WindowStart(){
	renderingEngine=new RenderingEngine();
	game->Start();

}

void Window::Update(float delta){
	game->Update(delta);
	//game->Input();
}

 void Window::Render(){

	 game->Render(Window::renderingEngine);
	 //renderingEngine->Render(game->GetRootGameObject());
}
 void Window::InitWindowSize(int32_t width,int32_t height){
	  WIDTH=width;
	  HEIGHT=height;
	  RenderingEngine::SetWindowSize(width,height);
  }

  void Window::OnApplicationQuit(){
	  game->ApplicationQuit(Window::renderingEngine);
	  delete game;
  }
   void Window::Resize(int32_t width,int32_t height){
	   WIDTH=width;
	   HEIGHT=height;
   }
   void Window::Pause(){
	   game->Pause(Window::renderingEngine);
	   delete renderingEngine;
	   renderingEngine=NULL;

   }
   void Window::Stop(){
	   game->Stop();
   }
   void Window::OnSurfaceDestroy(){
	   game->OnSurfaceDestroy();
   }

   void Window::Resume(){
	   renderingEngine=new RenderingEngine();
	   game->Resume(Window::renderingEngine);
   }
   void Window::LowMemory(){
	   game->LowMemory();
   }

   RenderingEngine* Window::GetRenderingEngine(){

	   return renderingEngine;
   }

   Vector2 Window::GetWindowCenter(){

	   return Vector2((float)GetWindowWidth()/2.0f,(float)GetWindowHeight()/2.0f);
   }

