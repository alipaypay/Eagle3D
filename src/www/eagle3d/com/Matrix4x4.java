package www.eagle3d.com;

public class Matrix4x4 {
//private
	private float[][] mat=new float[4][4];
//public
	public Matrix4x4(){
		
		
	}
	
	public Matrix4x4(float valMat[][]){
		
		
	}
	
	public Matrix4x4 InitRotation(float x,float y,float z){
	
		return this;
	}
	
	public void InitScale(float x,float y,float z){
		
		
	}
	
	public void InitProjection(float fov,float width,float height,float zNear,float zFar){
		
		
	}
	
	public void InitTranslation(float x,float y,float z){
		
		
	}
	
	public Matrix4x4 InitCamera(Vector3 forward,Vector3 up){
		
		return this;
	}
	
	public float[] GetMatLinearArray(){
		float value[]=new float[16];
		
		return value;
		
	}
	
	public void SetMatrix(float copMat[][]){
		
		
	}
	
	public Matrix4x4 Mul(Matrix4x4 tarM){
		Matrix4x4 matResult=new Matrix4x4();
		return matResult;
		
	}
	
	public float GetValue(int x,int y){
		
		return mat[x][y];
	}
	
	public void SetValue(int x,int y,float value){
		
		mat[x][y]=value;
	}
	
	public Matrix4x4 Identity(){
		
		
		return this;
	}
}
