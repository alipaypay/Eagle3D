package www.eagle3d.com;

public class Vertex {
//public:
	public	static final int VERTEX_SIZE=3;
	public	static final int TEXTURE_COORD_SIZE=2;
	public	static final int NORMAL_COORD_SIZE=3;
	public	static final int TOTAL_SIZE=5;
	public	Vector3 Position;
	public	Vector2 TextureCoord;

	
	public	Vertex(Vector3 pos){
		this.Position=pos;
		this.TextureCoord=new Vector2(0,0);
	}
	public	Vertex(Vector3 pos,Vector2 texCoord){
		this.Position=pos;
		this.TextureCoord=texCoord;
		
	}
}
