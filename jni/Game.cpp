#include "Game.h"

GameObject* Game::root=NULL;
Game::Game(){
	Awake();
}

void Game::OnResize(int32_t width,int32_t height){


}

void Game::Awake(){
	InitEagleDevelopClass();
	#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("Awake","()V");
	#endif
	material= Material();//file:///storage/emulated/0/Tencent/QQfile_recv/fz.mp4//http://hls4.l.cztv.com/channels/lantian/channel01/m3u8:540p?k=11d0cfd24dfd7ffb0973dc85f9127982&t=1445682591&time=1445682611578
	material.AddTexture("diffuse",Texture("/storage/emulated/0/tencent/QQfile_recv/fz.mp4",false));//http://img2.imgtn.bdimg.com/it/u=1179463281,1023096875&fm=21&gp=0.jpg//assets/a.png //file:///storage/emulated/0/Tencent/QQfile_recv/fly.mp4
	material.AddVector3("color",Vector3(1.0f,1.0f,1.0f));
	material.AddFloat("specularIntensity",0.8f);
	material.AddFloat("specularPower",4.0f);


	mesh= Mesh("plane3.obj");
	//Mesh mesh2("monkey3.obj");
	LOGI("Mesh Instanite success");
	meshRender=new MeshRender(mesh,material);
	planeObj=new GameObject();
	planeObj->AddComponent(meshRender);
	planeObj->GetTransform()->SetPosition(0.0f,-1.0f,-3.0f);
	LOGI("Mesh Render success");
	AddObject(planeObj);
	LOGI("GameObejct add success");
	GameObject *directionalObject=new GameObject();
	DirectionalLight* dirLight=new DirectionalLight(Vector3(0.0f,0.0f,1.0f),0.4f);
	directionalObject->AddComponent(dirLight);
	directionalObject->GetTransform()->SetRotation(Quaternion(Vector3(1.0f,0.0f,0.0f),EagleMath::ToRadians(30.0f)));
	AddObject(directionalObject);

	camera=new GameObject();
	cam=new Camera(EagleMath::ToRadians(70.0f),(float)Window::GetWindowWidth()/(float)Window::GetWindowHeight(),0.01f,1000.0f);
	cam->SetCameraRect(0,0,Window::GetWindowWidth()/2.0f,Window::GetWindowHeight());
	camera->AddComponent(cam);
	camera->GetTransform()->SetPosition(0.0f,6.0f,-13.0f);
	camera->GetTransform()->SetRotation(Quaternion(Vector3(1.0f,0.0f,0.0f),EagleMath::ToRadians(30.0f)));
	AddObject(camera);




}
void Game::Start(){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("Start","()V");
#endif
}

void Game::OnFocus(){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("OnFocus","()V");
#endif
}
void Game::OnLoseFocus(){

#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("OnLoseFocus","()V");
#endif
}

void Game::Update(float delta){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("Update","()V");
#endif

	GetRootGameObject()->Update(delta);

}

void  Game::AddObject(GameObject* obj){

	GetRootGameObject()->AddChild(obj);
}

void Game::Render(){

}

void Game::Render(RenderingEngine *renderingEngine){
	#ifdef _Android_
		eagleDevelopClass->CallJavaVoidMethod("Render","()V");
	#endif
	renderingEngine->Render(GetRootGameObject());
}



void Game::ApplicationQuit(RenderingEngine *renderingEngine){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("ApplicationQuit","()V");
#endif
	renderingEngine->ApplicationQuit(GetRootGameObject());
}
void Game::Pause(RenderingEngine *renderingEngine){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("Pause","()V");
	//delete eagleDevelopClass;
#endif
	renderingEngine->Pause(GetRootGameObject());
	GetRootGameObject()->RemoveChildAll();
	delete meshRender;

}
void Game::Stop(){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("Stop","()V");
#endif
}
void Game::OnSurfaceDestroy(){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("OnSurfaceDestroy","()V");
#endif
}
void Game::Resume(RenderingEngine *renderingEngine){
		//InitEagleDevelopClass();
#ifdef _Android_
		eagleDevelopClass->CallJavaVoidMethod("Resume","()V");
#endif
		renderingEngine->Resume(GetRootGameObject());
		material= Material();
		material.AddTexture("diffuse",Texture("/storage/emulated/0/tencent/QQfile_recv/fz.mp4",false));///storage/emulated/0/Tencent/QQ_Images/3.tga
		material.AddVector3("color",Vector3(1.0f,1.0f,1.0f));
		material.AddFloat("specularIntensity",0.8f);
		material.AddFloat("specularPower",4.0f);

		mesh= Mesh("plane3.obj");

		meshRender=new MeshRender(mesh,material);
		planeObj=new GameObject();
		planeObj->AddComponent(meshRender);
		planeObj->GetTransform()->SetPosition(0.0f,-1.0f,-3.0f);
		AddObject(planeObj);

		GameObject *directionalObject=new GameObject();
		DirectionalLight* dirLight=new DirectionalLight(Vector3(0.0f,0.0f,1.0f),0.4f);
		directionalObject->AddComponent(dirLight);
		directionalObject->GetTransform()->SetRotation(Quaternion(Vector3(1.0f,0.0f,0.0f),EagleMath::ToRadians(30.0f)));
		AddObject(directionalObject);

		camera=new GameObject();
		cam=new Camera(EagleMath::ToRadians(70.0f),(float)Window::GetWindowWidth()/(float)Window::GetWindowHeight(),0.01f,1000.0f);
		camera->AddComponent(cam);
		camera->GetTransform()->SetPosition(0.0f,6.0f,-13.0f);
		camera->GetTransform()->SetRotation(Quaternion(Vector3(1.0f,0.0f,0.0f),EagleMath::ToRadians(30.0f)));
		AddObject(camera);


}
void Game::LowMemory(){
#ifdef _Android_
	eagleDevelopClass->CallJavaVoidMethod("LowMemory","()V");
#endif
}


void Game::InitEagleDevelopClass(){
	#ifdef _Android_
		eagleDevelopClass=new C2Java(Java2C::CURRENT_CLASS,Core::GetActivity(),true);
	#endif
}

GameObject* Game::GetRootGameObject(){
	if(root==NULL){
		root=new GameObject();
	}

	return root;
}
