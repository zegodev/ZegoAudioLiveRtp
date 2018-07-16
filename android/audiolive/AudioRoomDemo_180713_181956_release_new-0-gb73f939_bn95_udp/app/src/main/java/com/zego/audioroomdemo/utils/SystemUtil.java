package com.zego.audioroomdemo.utils;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;

import com.zego.audioroomdemo.R;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;


/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class SystemUtil {
    public static String getAppVersionName(Context context) {

        String versionName = context.getString(R.string.demo_version);

        try {
            PackageManager manager = context.getPackageManager();
            PackageInfo info = manager.getPackageInfo(context.getPackageName(), 0);
            versionName = versionName + info.versionName;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return versionName;
    }


    static public String getOsInfo() {

        // 上报系统信息
        StringBuilder oriInfo = new StringBuilder();
        oriInfo.append(Build.MODEL);

        // 替换字符串中的","
        String finalInfo = oriInfo.toString().replaceAll(",", ".");

        return finalInfo;
    }

    /**
     * 将文件从assets目录，考贝到 /data/data/包名/files/ 目录中。assets 目录中的文件，会不经压缩打包至APK包中，使用时还应从apk包中导出来
     *
     * @param fileName 文件名,如aaa.txt
     */
    static public String copyAssetsFile2Phone(Activity activity, String fileName) {
        Activity mActivity = activity;
        try {
            InputStream inputStream = mActivity.getAssets().open(fileName);
            //getFilesDir() 获得当前APP的安装路径 /data/data/包名/files 目录
            File file = new File(mActivity.getFilesDir().getAbsolutePath() + File.separator + fileName);
            if (!file.exists() || file.length() == 0) {
                FileOutputStream fos = new FileOutputStream(file);//如果文件不存在，FileOutputStream会自动创建文件
                int len;
                byte[] buffer = new byte[1024];
                while ((len = inputStream.read(buffer)) != -1) {
                    fos.write(buffer, 0, len);
                }
                fos.flush();//刷新缓存区
                inputStream.close();
                fos.close();

            } else {

            }
            return file.getPath();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;

    }


}
