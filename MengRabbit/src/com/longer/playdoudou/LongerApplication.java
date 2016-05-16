package com.longer.playdoudou;

import android.app.Application;
import android.text.TextUtils;

public class LongerApplication extends Application {
	
	private native String getAdConfig();
	public static String[] AD_CONFIG = null;
	
	
	static {
		System.loadLibrary("render");
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		if(!TextUtils.isEmpty(getAdConfig())){
			AD_CONFIG = getAdConfig().split(",");
		}
	}

}
