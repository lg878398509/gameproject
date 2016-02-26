package com.longer.playdoudou.menu;

import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.Gallery;
import android.widget.ImageSwitcher;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;
import android.widget.ViewSwitcher.ViewFactory;

import com.longer.playdoudou.GameInit;
import com.longer.playdoudou.LongerApplication;
import com.longer.playdoudou.R;
import com.longer.playdoudou.utils.GoloProgressDialog;
import com.wandoujia.ads.sdk.Ads;

/**
 * 
 * @author xiangshilong
 *
 */
public class MapOp extends Activity implements ViewFactory {

	int fullversion = 0;

	private int difficulty = 2;
	private int mapSelected = 1;
	private int gameMode = 0;

	private LinearLayout banner_container;

	private Button startGameButton;

	private Gallery gallery;

	private Bitmap bitmap1;
	private Bitmap bitmap2;
	private Bitmap bitmap3;
	private Bitmap bitmap4;
	private Bitmap bitmap5;
	private Bitmap bitmap6;

	/** References to our images */
	private Bitmap[] mmaps = { bitmap1, bitmap2, bitmap3, bitmap4, bitmap5, bitmap6, };

	private long firstTime = 0;
	
	private Handler mHandler = new Handler(){
		public void handleMessage(android.os.Message msg) {
			switch (msg.what) {
			case 0:
				GoloProgressDialog.dismissProgressDialog(MapOp.this);
				break;
			}
		};
	};

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);
		setContentView(R.layout.mainmenu_startgame);

		Resources r = getResources();
		fullversion = r.getInteger(R.integer.app_type);

		BitmapFactory.Options options = new BitmapFactory.Options();
		options.inSampleSize = 8;
		options.inPreferredConfig = Bitmap.Config.RGB_565;
		InputStream is = this.getResources().openRawResource(R.drawable.map1);

		try {
			mmaps[0] = BitmapFactory.decodeStream(is, null, options);
			is = this.getResources().openRawResource(R.drawable.map2);
			mmaps[1] = BitmapFactory.decodeStream(is, null, options);
			if (fullversion == 0)
				options.inSampleSize = 1;
			is = this.getResources().openRawResource(R.drawable.map3);
			mmaps[2] = BitmapFactory.decodeStream(is, null, options);
			is = this.getResources().openRawResource(R.drawable.map4);
			mmaps[3] = BitmapFactory.decodeStream(is, null, options);
			is = this.getResources().openRawResource(R.drawable.map5);
			mmaps[4] = BitmapFactory.decodeStream(is, null, options);
			is = this.getResources().openRawResource(R.drawable.map6);
			mmaps[5] = BitmapFactory.decodeStream(is, null, options);
		} finally {
			try {
				is.close();
			} catch (IOException e) {
				// Skip
			}
		}

		/**
		 * Ensures that the activity is displayed only in the portrait
		 * orientation
		 */
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

		/**
		 * identifying the image views and text view, these are the ones that
		 * will be set.
		 */
		banner_container = (LinearLayout) findViewById(R.id.banner_container);

		showBannerAd();
		gallery = (Gallery) findViewById(R.id.gallery1);
		gallery.setAdapter(new ImageAdapter(this));
		gallery.setOnItemSelectedListener(gItemSelectedHandler);
		gallery.setSelection((gallery.getCount() / 2) - 2, true);

		startGameButton = (Button) findViewById(R.id.startmap);
		startGameButton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				GoloProgressDialog.showProgressDialog(MapOp.this);
				new Thread(){
					public void run() {
						try {
							Thread.sleep(2000);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						mHandler.sendEmptyMessage(0);
					};
				}.start();
				Intent startGame = new Intent(v.getContext(), GameInit.class);
				startGame.putExtra("com.longer.playdoudou.menu.map", mapSelected);
				startGame.putExtra("com.longer.playdoudou.menu.difficulty", difficulty);
				startGame.putExtra("com.longer.playdoudou.menu.wave", gameMode);
				startActivity(startGame);
			}
		});

	}

	private void showBannerAd() {
		try {
			View bannerView = Ads.createBannerView(MapOp.this, LongerApplication.AD_CONFIG[2]);
			banner_container.addView(bannerView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		} catch(Exception e){
			e.printStackTrace();
		}
	}

	public View makeView() {
		ImageView imageView = new ImageView(this);
		imageView.setBackgroundResource(R.drawable.xml_gallery);
		imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
		imageView.setLayoutParams(new ImageSwitcher.LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		return imageView;
	}

	public OnItemSelectedListener gItemSelectedHandler = new OnItemSelectedListener() {
		// @Override
		public void onItemSelected(AdapterView<?> parent, View v, int _position, long id) {
			_position = _position % 6;
			switch (_position) {
			case 0:
				mapSelected = 1;
				break;
			case 1:
				mapSelected = 2;
				break;
			case 2:
				if (fullversion == 0) {
					mapSelected = 1;
				} else {
					mapSelected = 3;
				}
				break;
			case 3:
				if (fullversion == 0) {
					mapSelected = 1;
				} else {
					mapSelected = 4;
				}
				break;
			case 4:
				if (fullversion == 0) {
					mapSelected = 1;
				} else {
					mapSelected = 5;
				}
				break;
			case 5:
				if (fullversion == 0) {
					mapSelected = 1;
				} else {
					mapSelected = 6;
				}
				break;
			}

		}

		// @Override
		public void onNothingSelected(AdapterView<?> arg0) {
			// TODO Auto-generated method stub
		}
	};

	private class ImageAdapter extends BaseAdapter {
		private Context context;
		// private int itemBackground;
		public int position;
		private int x;
		private int y;

		public ImageAdapter(Context c) {
			context = c;
			x = (int) (110 * getResources().getDisplayMetrics().density);
			y = (int) (165 * getResources().getDisplayMetrics().density);
		}

		// ---returns the number of images---
		public int getCount() {
			return 1000;
		}

		public Object getItem(int position) {
			return position % 6;
		}

		public long getItemId(int position) {
			return position % 5;
		}

		// ---returns an ImageView view---
		public View getView(int position, View convertView, ViewGroup parent) {
			this.position = position % 6;
			ImageView imageView = new ImageView(context);
			imageView.setImageBitmap(mmaps[this.position]);
			imageView.setScaleType(ImageView.ScaleType.FIT_XY);
			imageView.setLayoutParams(new Gallery.LayoutParams(x, y));
			imageView.setBackgroundResource(R.drawable.xml_gallery);
			return imageView;
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			long secondTime = System.currentTimeMillis();
			if (secondTime - firstTime > 2000) {
				firstTime = secondTime;
				Toast.makeText(this, R.string.confim_exit, Toast.LENGTH_SHORT).show();
			} else {
				System.exit(0);
			}
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}

}
