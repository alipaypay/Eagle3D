package www.eagle3d.com;
import java.util.HashMap;
public class Touch {
	public static Touch touch;
	private  int touchCount=0;
	private HashMap<Integer, Vector3> deltaPosition = new HashMap<Integer, Vector3>();
	private HashMap<Integer, Vector3> touchPosition = new HashMap<Integer,Vector3>();
	private int currentIndex=0;
	private Touch(){
	}
	public static Touch GetTouchInatance(){
		if(touch==null){
			touch=new Touch();
		}
		return touch;
	}
	
	public void SetDeltaPosition(int index,Vector3 vec){
		deltaPosition.put(index, vec);
	}
	
	public void SetTouchPosition(int index,Vector3 vector3){
		touchPosition.put(index, vector3);
	}
	
	public void SetTouchCurrentUPIndex(int index){
		
		touchPosition.remove(index);
	}
	
	public Vector3 GetDeltaPosition(){
		
		Vector3 vec=deltaPosition.get(currentIndex);
		return vec;
	}
	
	public Vector3 GetTouchPosition(){
		Vector3 vec=touchPosition.get(currentIndex);
		return vec;
	}
	
	public void SetCurrentIndex(int index){
		
		currentIndex=index;
	}
	
	public  void SetTouchCount(int count){
		touchCount=count;
		
	}
	public  int GetTouchCount(){
		
		return touchCount;
	}
	
}
