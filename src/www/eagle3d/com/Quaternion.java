package www.eagle3d.com;

public class Quaternion {
//private
	private float x,y,z,w;

//public 
	public float getX() {
		return x;
	}

	public void setX(float x) {
		this.x = x;
	}

	public float getY() {
		return y;
	}

	public void setY(float y) {
		this.y = y;
	}

	public float getZ() {
		return z;
	}

	public void setZ(float z) {
		this.z = z;
	}

	public float getW() {
		return w;
	}

	public void setW(float w) {
		this.w = w;
	}

	
	public Quaternion(float x,float y,float z,float w){
		
		
	}
	
	public float Length(){
		float sqrt=0;
		return sqrt;
	}
	
	public Quaternion Normalize(){
		
		return this;
		
	}
	
	public Quaternion Mul(Quaternion r){
		
		return this; 
	}
	
	public Quaternion Mul(Vector3 vec){
		
		return this; 
	}	
	
}
