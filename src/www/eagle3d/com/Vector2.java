package www.eagle3d.com;

public class Vector2 {
//private
	private float x,y;

	

	//public 
	public Vector2(){}
	
	public Vector2(Vector2 copy){}
	
	public Vector2(float vx,float vy){}
	
	public Vector2 Assign(Vector2 v){
		this.x=v.x;
		this.y=v.y;
		return this;
		
	}
	
	public Vector2 Roatate(float angle){
		return this;
		
	}
	
	public boolean ToVary(Vector2 v){
		
		return false;
	}
	
	public void Zero(){
		
		x=y=0;
	}
	
	public Vector2 Lose(){
		
		return new Vector2(-x,-y);
	}
	
	public Vector2 Plus(Vector2 v){
		return new Vector2(this.x+v.x,this.y+v.y);
		
	}
	
	public Vector2 Reduce(Vector2 v){
		
		return new Vector2(this.x-v.x,this.y-v.y);
	}
	
	public Vector2 Mul(float val){
		
		return new Vector2(x*val,y*val);
	}
	
	public Vector2 Except(float val){
		
		float v=1.0f/val;
		return Mul(v);
	}
	
	public boolean Equals(Vector2 v){
		
		return (this.x==v.x && this.y==v.y);
	}
	
	public void Normalize(){
		float magSq=(float)(x*x+y*y);
		if(magSq>0.0f){
			float oneOverMag=(float) (1.0f/Math.sqrt(magSq));
			x*=oneOverMag;
			y*=oneOverMag;
		}
	}
	
	public float Dot( Vector2 v) {

		return x*v.x+y*v.y;
	}
	
	public float Length( Vector2 v){

		return (float) (Math.sqrt(v.x*v.x+v.y*v.y));
	}

	public static float Distance( Vector2 v1, Vector2 v2){
		float dx=v2.x-v1.x;
		float dy=v2.y-v1.y;


		return (float)(Math.sqrt(dx*dx+dy*dy));

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
}
