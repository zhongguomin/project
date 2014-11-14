package com.thtfit.test;

import android.app.Application;
import android.content.res.Configuration;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.Size;
import android.util.Log;

import java.util.ArrayList;
import java.util.TreeMap;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

public class ProductTest extends Application{
	private final static String LOG_TAG = "Report";
	private final String report = "/mnt/sdcard/report";
	public TreeMap<Integer, String> report_test_result;
	List<Map<String, Object>> report_test_item_title;
	
	private String report_test_item_memory = null;
	private String report_test_item_flash = null;
	private String report_test_item_sdcard = null;
	private String report_test_item_otg = null;
	private String report_test_item_key = null;
	private String report_test_item_gravity = null;
	private String report_test_item_wifi = null;
	private String report_test_item_bluetooth = null;
	private String report_test_item_tp = null;
	private String report_test_item_camera = null;
	private String report_test_item_display = null;
	private String report_test_item_audio = null;
	private String report_test_item_recorder = null;
	private String report_test_item_earplug = null;
	
	private String info_camear_pixels = null;
	private String info_no_camear = null;
	
	private int memorySize = 0; 
	private int flashSize = 0;
	private int cameraPixels = 0;
	
	private void init_report_test_item_title_res() {
		report_test_item_memory = getResources().getString(R.string.report_test_item_memory);
		report_test_item_flash = getResources().getString(R.string.report_test_item_flash);
		report_test_item_sdcard = getResources().getString(R.string.report_test_item_sdcard);
		report_test_item_otg = getResources().getString(R.string.report_test_item_otg);
		report_test_item_key = getResources().getString(R.string.report_test_item_key);
		report_test_item_gravity = getResources().getString(R.string.report_test_item_gravity);
		report_test_item_wifi = getResources().getString(R.string.report_test_item_wifi);
		report_test_item_bluetooth = getResources().getString(R.string.report_test_item_bluetooth);
		report_test_item_tp = getResources().getString(R.string.report_test_item_tp);
		report_test_item_camera = getResources().getString(R.string.report_test_item_camera);
		report_test_item_display = getResources().getString(R.string.report_test_item_display);
		report_test_item_audio = getResources().getString(R.string.report_test_item_audio);
		report_test_item_recorder = getResources().getString(R.string.report_test_item_recorder);
		report_test_item_earplug = getResources().getString(R.string.report_test_item_earplug);
		
		info_camear_pixels = getResources().getString(R.string.info_camera_pixels);
		info_no_camear = getResources().getString(R.string.info_no_camear);
	}
	
	private void init_report_test_item_title_list() {
		report_test_item_title = new ArrayList<Map<String,Object>>();
		report_test_item_title.clear();
		
		Map<String,Object> map1 =new HashMap<String,Object>();
		map1.put("title", report_test_item_memory + " ( " + memorySize + " M )");
		report_test_item_title.add(0, map1);
		
		Map<String,Object> map2 =new HashMap<String,Object>();
		map2.put("title", report_test_item_flash + " ( " + flashSize + " M )");
		report_test_item_title.add(1, map2);

		Map<String,Object> map3 =new HashMap<String,Object>();
		map3.put("title", report_test_item_sdcard);
		report_test_item_title.add(2, map3);
		
		Map<String,Object> map4 =new HashMap<String,Object>();
		map4.put("title", report_test_item_otg);
		report_test_item_title.add(3, map4);

		Map<String,Object> map5 =new HashMap<String,Object>();
		map5.put("title", report_test_item_key);
		report_test_item_title.add(4, map5);

		Map<String,Object> map6 =new HashMap<String,Object>();
		map6.put("title", report_test_item_gravity);
		report_test_item_title.add(5, map6);

		Map<String,Object> map7 =new HashMap<String,Object>();
		map7.put("title", report_test_item_wifi);
		report_test_item_title.add(6, map7);

		Map<String,Object> map8 =new HashMap<String,Object>();
		map8.put("title", report_test_item_bluetooth);
		report_test_item_title.add(7, map8);

		Map<String,Object> map9 =new HashMap<String,Object>();
		map9.put("title", report_test_item_tp);
		report_test_item_title.add(8, map9);

		Map<String,Object> map10 =new HashMap<String,Object>();
		map10.put("title",report_test_item_camera + " ( " + cameraPixels + " " + info_camear_pixels + " )");
		report_test_item_title.add(9, map10);
		
		Map<String,Object> map11 =new HashMap<String,Object>();
		map11.put("title",report_test_item_display);
		report_test_item_title.add(10, map11);

		Map<String,Object> map12 =new HashMap<String,Object>();
		map12.put("title", report_test_item_audio);
		report_test_item_title.add(11, map12);

		Map<String,Object> map13 =new HashMap<String,Object>();
		map13.put("title", report_test_item_recorder);
		report_test_item_title.add(12, map13);

		Map<String,Object> map14 =new HashMap<String,Object>();
		map14.put("title", report_test_item_earplug);
		report_test_item_title.add(13, map14);
	}
	
	private void init_report_test_item_result() {
		report_test_result = new TreeMap<Integer, String>();
		MemoryActivity.createHashTable(report_test_result);
		NandflashActivity.createHashTable(report_test_result);
		SdcardActivity.createHashTable(report_test_result);
		UsbhostActivity.createHashTable(report_test_result);
		MouseActivity.createHashTable(report_test_result);
		DisplayActivity.createHashTable(report_test_result);
	}
	
	public int getCamPPlxels() {
		int pixels = 0;
		try{
			Camera mCamera = Camera.open();
			Parameters parameters = mCamera.getParameters(); 
			int newPixels = 0; 
			List<Size> psizelist = parameters.getSupportedPictureSizes(); 
			if (null != psizelist && 0 < psizelist.size()) { 
				int heights[] = new int[psizelist.size()]; 
				int widths[] = new int[psizelist.size()]; 
				for (int i = 0; i < psizelist.size(); i++) { 
					Size size = (Size) psizelist.get(i); 
					int sizehieght = size.height; 
					int sizewidth = size.width; 
					heights[i] = sizehieght; 
					widths[i] =sizewidth; 
				} 
				int Height_Pixels = heights[0]; 
				int width_Pixels = widths[0]; 
				newPixels = Height_Pixels*width_Pixels; 
				newPixels = newPixels / 10000;
				pixels = newPixels;
			} 
			mCamera.release();
		}catch(Exception e){
			pixels = 0;
			e.printStackTrace();
		}
		
		return pixels;
	}
	
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		
		memorySize = Block.getMemorySize();
		flashSize = Block.getFlashSize();
		cameraPixels = getCamPPlxels();
		
		// report list item title
		init_report_test_item_title_res();
		init_report_test_item_title_list();
		init_report_test_item_result();
	}
	
	public String getTitle(int position)
	{
		String str = "";
		String key = "title";
		Map<String,Object> map = report_test_item_title.get(position);
		if(map.containsKey(key)){
			str = map.get(key).toString();
		}
		return str;
	}
	
	@Override
	public void onTerminate() {
		// TODO Auto-generated method stub
		super.onTerminate();
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		// TODO Auto-generated method stub
		super.onConfigurationChanged(newConfig);
		
		init_report_test_item_title_res();
		init_report_test_item_title_list();
		init_report_test_item_result();
	}

	public void addKeyEvent(int position, String key){
		Map<String,Object> map = report_test_item_title.get(position);
		if(map.containsKey(key)){
			int val = Integer.parseInt(map.get(key).toString());
			val++;
			map.put(key, val);
			Log.v(LOG_TAG, "key:"+key+"val:"+val);
		}else{
			map.put(key, 1);
			Log.v(LOG_TAG, "key:"+key+"val:1");
		}
	}
	public void addKeyEvent(int index){
		int position = index / 100;
		position = position - 1;
		String key = report_test_result.get(index);
		if(position > 13 || position < 0){
			Log.e(LOG_TAG, "position err");
			return;
		}
		Map<String,Object> map = report_test_item_title.get(position);
		if(map.containsKey(key)){
			int val = Integer.parseInt(map.get(key).toString());
			val++;
			map.put(key, val);
			Log.v(LOG_TAG, "key:"+key+"val:"+val);
		}else{
			map.put(key, 1);
			Log.v(LOG_TAG, "key:"+key+"val:1");
		}
	}
}
