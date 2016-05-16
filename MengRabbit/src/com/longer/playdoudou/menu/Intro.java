package com.longer.playdoudou.menu;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;

import com.longer.playdoudou.LongerApplication;
import com.longer.playdoudou.R;
import com.wandoujia.ads.sdk.Ads;

/**
 * 引导页
 * 
 * @author xiangshilong
 *
 */
public class Intro extends Activity {

	private final int INTRO_LENGTH = 500;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.intro);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		
		new AsyncTask<Void, Void, Boolean>() {
			@Override
			protected Boolean doInBackground(Void... params) {
				try {
					Ads.init(Intro.this, LongerApplication.AD_CONFIG[0], LongerApplication.AD_CONFIG[1]);
					return true;
				} catch (Exception e) {
					return false;
				}
			}

			@Override
			protected void onPostExecute(Boolean success) {
				if (success) {
					Ads.preLoad(LongerApplication.AD_CONFIG[2], Ads.AdFormat.banner);
					Ads.preLoad(LongerApplication.AD_CONFIG[3], Ads.AdFormat.interstitial);
					Ads.preLoad(LongerApplication.AD_CONFIG[4], Ads.AdFormat.appwall);
				}
			}
		}.execute();
		
		new Handler().postDelayed(new Runnable() {
			public void run() {
				Intent theMain = new Intent(Intro.this, MapOp.class);
				startActivity(theMain);
				finish();
				overridePendingTransition(R.anim.mainfadein, R.anim.introfadeout);
			}
		}, INTRO_LENGTH);
	}
}