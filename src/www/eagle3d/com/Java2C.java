package www.eagle3d.com;

public class Java2C {
	static {  
       
        System.loadLibrary("eagle3d");  
    }  
	
	public native static void SetPackageCodePath(String path);
	
	public native static void SetEaglePackageClassNames(String[] classNames);
	
	public static native void SetEagleClass(Class<?> eagleClass);
}
