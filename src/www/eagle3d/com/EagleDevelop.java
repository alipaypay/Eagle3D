package www.eagle3d.com;




public interface EagleDevelop {
	
	public  void Awake();
	
	public  void Start();
	
	public  void OnFocus();
	
	public  void OnLoseFocus();

	public  void Update();

	public  void Render();

	public  void ApplicationQuit();
	
	public  void Pause();
	
	public  void Stop();
	
	public  void OnSurfaceDestroy();
	
	public  void Resume();
	
	public  void LowMemory();
	
	public  void OnResize(int width,int height);
	
	
}
