package www.eagle3d.com;



import java.io.IOException;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;


import dalvik.system.DexFile;
import android.app.NativeActivity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class EagleNativeActivity extends NativeActivity {
	static {
	       System.loadLibrary("eagle3d");
	      
	    }
	
	
	public static ClassLoader CLASS_LOADER;
	
	public static PackageManager EAGLE_PACKAGE_MANAGER;
	
	public static String APK_FILE_PATH;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		APK_FILE_PATH = null;
		ApplicationInfo appInfo = null;
		EAGLE_PACKAGE_MANAGER = this.getPackageManager();
		try {
	    appInfo = EAGLE_PACKAGE_MANAGER.getApplicationInfo("www.eagle3d.com", 0);
		} catch (NameNotFoundException e) {
	    e.printStackTrace();
	    throw new RuntimeException("Unable to locate assets, aborting...");
		}
		CLASS_LOADER=this.getClassLoader();
		
		APK_FILE_PATH = appInfo.sourceDir;
		Log.i("Eagle3D", APK_FILE_PATH);
		Java2C.SetEagleClass(EagleDevelop.class);
		Java2C.SetPackageCodePath(APK_FILE_PATH);
		SetCurrentPackageClasses();
		
	
	}
	
	
	
	public void SetCurrentPackageClasses(){
		
		DexFile dexfile=null;
		try {
			dexfile = new DexFile(APK_FILE_PATH);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
        Enumeration<String> entries = dexfile.entries();
        List<String> classesList=new ArrayList<String>();
        while (entries.hasMoreElements()) {
        	String name = (String) entries.nextElement();
        	
        	if(name.equals("www.eagle3d.com.EagleDevelop") || !name.contains("www.eagle3d.com")){
        		continue;
        	}
        	name=name.replace(".", "/");
        	Log.i("Eagle3D class name:", name);
        	classesList.add(name);	
        }
        String[] classesNames=new String[classesList.size()];
        for(int i=0;i<classesList.size();i++){
        	classesNames[i]=classesList.get(i);
        }  
		Java2C.SetEaglePackageClassNames(classesNames);
		
	}
	
	@Override  
	public boolean onTouchEvent(MotionEvent event) {
		 			Touch.GetTouchInatance().SetTouchCount(event.getPointerCount());
		 			int action =event.getActionMasked();
	                 switch (action) {  
	                 case MotionEvent.ACTION_DOWN:
	                	 		final  int pointerIndex=event.getActionIndex();
		                    	try{
	                	 		final float x = event.getX(event.getPointerId(pointerIndex));  
				                final float y = event.getY(event.getPointerId(pointerIndex));
		                    	Touch.GetTouchInatance().SetTouchPosition(pointerIndex,new Vector3(x,y,0));
		                    	}catch(Exception e){
		                    		Log.i("Eagle3D", e.getMessage());
		                    	} 
		                    	Log.i("Eagle3D", "index"+pointerIndex);
	                     break;  
	                 case MotionEvent.ACTION_UP:
	                	 Log.i("Eagle3D", "indexUP"+event.getActionIndex());
		                 Touch.GetTouchInatance().SetTouchCurrentUPIndex(event.getActionIndex());
	                     break;
	                 case MotionEvent.ACTION_POINTER_DOWN:
	                	 
	                	 final  int pointerIndex2=event.getActionIndex();
	                	 try{
	                	 final float x2 = event.getX(event.getPointerId(pointerIndex2));  
			             final float y2 = event.getY(event.getPointerId(pointerIndex2));
			             Touch.GetTouchInatance().SetTouchPosition(pointerIndex2,new Vector3(x2,y2,0));
	                	 }catch(Exception e){
	                		 
	                		 Log.i("Eagle3D", e.getMessage());
	                	 }
			             Log.i("Eagle3D", "index"+pointerIndex2);
	                	 break;
	                 case MotionEvent.ACTION_POINTER_UP:
	                	 
	                	 Touch.GetTouchInatance().SetTouchCurrentUPIndex(event.getActionIndex());
	                	 Log.i("Eagle3D", "indexUP"+event.getActionIndex());
	                	 break;
	                 case MotionEvent.ACTION_MOVE: {  
	                	
	                    for(int i=0;i<event.getPointerCount();i++){
	                    	try{
	                    	final float x1 = event.getX(event.getPointerId(i));  
			                final float y1 = event.getY(event.getPointerId(i));
	                    	Touch.GetTouchInatance().SetDeltaPosition(event.getPointerId(i),new Vector3(x1,y1,0));
	                    	}catch(Exception e){
	                    	
	                    	Log.i("Eagle3D", e.getMessage());
	                    	}
	                   }
		                 break;  
	              
	        }  
	      }
        	return true;
	    }  	      
	 @Override  
	 public boolean onKeyDown(int keyCode, KeyEvent event) {  
	        return super.onKeyDown(keyCode, event);  
	 }

	
}








