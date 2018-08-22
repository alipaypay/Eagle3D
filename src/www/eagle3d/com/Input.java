package www.eagle3d.com;



public class Input {
	
	
	public static Touch GetTouch(int index){
      Touch touch=Touch.GetTouchInatance();
	  touch.SetCurrentIndex(index);
      return touch;
	}
	
	
	
	
	
}

