package com.longer.playdoudou.utils;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnKeyListener;
import android.os.Handler;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.longer.playdoudou.R;

public class GoloProgressDialog {

	
	public static Dialog dialog;
	public static final int cancelDialog = -1000;
	
	
	/**
	 * 
	 * @Title: showProgressDialog   
	 * @Description: TODO(公共加载框)  
	 * @param: @param context
	 * @param: @param msg ("1"代表拼命提交中) （"2"代表玩命加载中）（"0"代表疯狂登录中）    
	 * @return: void     
	 * @throws
	 */
	public static void showProgressDialog(Context context) {
		if(context !=null && !((Activity)context).isFinishing()){
			//处理 由于上次创建对话框的Context已经结束 ，继续关闭对话引起的异常问题  zilongw 2015.03.07 begin
			if (dialog != null /*&& !dialog.getOwnerActivity().isFinishing()*/ && dialog.isShowing()) {				
				try {
					dialog.dismiss();
				} catch (Exception e) {
					// TODO: handle exception
				}
				dialog = null;
				
			}
			//处理 由于上次创建对话框的Context已经结束 ，继续关闭对话引起的异常问题  zilongw 2015.03.07 end
			dialog = new Dialog(context, R.style.dialog_normal_Dim);
			dialog.show();
			View view = (LinearLayout) LayoutInflater.from(context).inflate(R.layout.loading_layout, null);
			dialog.setContentView(view);
			dialog.setCanceledOnTouchOutside(false);
		} 
	}

	
	public static boolean dismissProgressDialog(Context context) {
		if (dialog != null && dialog.isShowing()) {
			//modify: 添加异常处理  所属的窗口已经finished后继续关闭对话框会出现异常 zilongw  2014.08.13 begin
			try {
				dialog.dismiss();
				dialog = null;
				return true;
			} catch (Exception e) {
			}
			//modify: 添加异常处理  所属的窗口已经finished后继续关闭对话框会出现异常 zilongw  2014.08.13 end
		}
		dialog = null;
		return false;
	}

}