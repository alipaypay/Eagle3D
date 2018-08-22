package www.eagle3d.com;

public class Vector3 {
//private:
	private float x,y,z;
	

	//public:
	public Vector3(){
		
		
	}
	
	public Vector3(Vector3 copy){
		
		
	}
	
	public Vector3(float x,float y,float z){
		
		
	}
	
	public Vector3 Assign(Vector3 v){
		
		return this;
	}
	
	public boolean Equals(Vector3 v){
		
		return (x==v.x && y==v.y && z==v.z);
	}
	
	public void Zero(){
		
		
	}
	
	public Vector3 Lose(){
		
		return new Vector3(-x,-y,-z);
	}
	
	
	public Vector3 Plus(Vector3 v){
		return new Vector3(this.x+v.x,this.y+v.y,this.z+v.z);
		
	}
	
	public Vector3 Reduce(Vector3 v){
		
		return new Vector3(this.x-v.x,this.y-v.y,this.z-v.z);
	}
	
	public Vector3 Mul(float val){
		
		return new Vector3(x*val,y*val,z*val);
	}
	
	public Vector3 Except(float val){
		
		float v=1.0f/val;
		return Mul(v);
	}
	
	public void Normalize(){
		
	
	}
	
	
	public float Dot(Vector3 v){
		
		return x*v.x+y*v.y+z*v.z;
	}
	
	
	public float Length( Vector3 v){

		return (float) Math.sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	}
	//Cross product
	public Vector3 CrossProduct( Vector3 v){
		
		return new Vector3(
				y*v.z-z*v.y,
				z*v.x-x*v.z,
				x*v.y-y*v.x
				);
	  }
	//Axis rotate
	public Vector3 Rotate(float angle,Vector3 axis){
		
		return this;
	}
	//v1 vector and v2 vector distance
	 float Distance( Vector3 v1, Vector3 v2){
		float dx=v2.x-v1.x;
		float dy=v2.y-v1.y;
		float dz=v2.z-v1.z;

		return (float) Math.sqrt(dx*dx+dy*dy+dz*dz);

	}
	
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
}
