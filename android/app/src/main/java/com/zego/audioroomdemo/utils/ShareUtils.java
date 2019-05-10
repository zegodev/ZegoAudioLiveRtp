package com.zego.audioroomdemo.utils;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.support.v4.content.FileProvider;

import java.io.File;
import java.io.FilenameFilter;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * <p>Copyright © 2017 Zego. All rights reserved.</p>
 *
 * @author realuei on 05/09/2017.
 */

public class ShareUtils {

    static final public void sendFiles(File[] fileList, Activity activity) {
        File cacheDir = activity.getExternalCacheDir();
        if (cacheDir == null || !cacheDir.canWrite()) {
            cacheDir = activity.getCacheDir();
        }

        File[] oldLogCaches = cacheDir.listFiles(new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                return name.startsWith("zegoavlog") && name.endsWith(".zip");
            }
        });

        for (File cache : oldLogCaches) {
            cache.delete();
        }

        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd-HHmmss");
        String zipFileName = String.format("zegoavlog_%s.zip", sdf.format(new Date()));
        File zipFile = new File(cacheDir, zipFileName);

        try {
            ZipUtil.zipFiles(fileList, zipFile, "Zego LiveDemo5 日志信息");

            Intent shareIntent = new Intent(Intent.ACTION_SEND);
            Uri uri;

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N){
                uri = FileProvider.getUriForFile(activity, "com.zego.audioroomdemo.fileProvider", zipFile);
            }else {
                uri = Uri.fromFile(zipFile);
            }

            shareIntent.putExtra(Intent.EXTRA_STREAM, uri);
            shareIntent.setType("application/zip");

            shareIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK
                    | Intent.FLAG_ACTIVITY_NEW_TASK
                    | Intent.FLAG_GRANT_READ_URI_PERMISSION);
            activity.startActivity(shareIntent);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
