package com.zego.audioroomdemo;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.support.annotation.NonNull;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.pgyersdk.update.PgyUpdateManager;
import com.zego.audioroomdemo.activities.SessionActivity;
import com.zego.audioroomdemo.activities.SettingsActivity;
import com.zego.audioroomdemo.activities.ZegoPhoneActivity;
import com.zego.audioroomdemo.utils.PrefUtils;
import com.zego.audioroomdemo.utils.AppSignKeyUtils;
import com.zego.audioroomdemo.utils.SystemUtil;
import com.zego.zegoaudioroom.ZegoAudioRoom;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.entity.ZegoExtPrepSet;

import java.lang.ref.WeakReference;
import java.text.SimpleDateFormat;
import java.util.Date;

import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {

    static private final int REQUEST_CODE_PERMISSION = 0x101;

    static private final int REQUEST_CODE_UPDATE_APK = 0x10002;

    @Bind(R.id.room_name)
    public EditText ctrlRoomName;

    @Bind(R.id.btn_login_logout)
    public Button btnLoginOrLogout;

    @Bind(R.id.toolbar)
    public android.support.v7.widget.Toolbar toolBar;

    private long currentAppId = -1;
    private String currentStrSignKey = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (!isTaskRoot()) {
            /* If this is not the root activity */
            Intent intent = getIntent();
            String action = intent.getAction();
            if (intent.hasCategory(Intent.CATEGORY_LAUNCHER) && Intent.ACTION_MAIN.equals(action)) {
                finish();
                return;
            }
        }
        setContentView(R.layout.activity_main);

        ButterKnife.bind(this);

        setSupportActionBar(toolBar);
        toolBar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent settingsIntent = new Intent(MainActivity.this, SettingsActivity.class);
                settingsIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                currentAppId = PrefUtils.getAppId();
                currentStrSignKey = AppSignKeyUtils.convertSignKey2String(PrefUtils.getAppKey());
                settingsIntent.putExtra("appId", currentAppId);
                settingsIntent.putExtra("rawKey", currentStrSignKey);
                startActivityForResult(settingsIntent, 101);
            }
        });

        btnLoginOrLogout.setEnabled(false);
        if (PrefUtils.isManualPublish()) {
            btnLoginOrLogout.setText(R.string.zg_login_room);
        } else {
            btnLoginOrLogout.setText(R.string.zg_start_communicate);
        }

        if (checkOrRequestPermission(REQUEST_CODE_UPDATE_APK)) {
            /** 可选配置集成方式 **/
            updateApk();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        int currentAppFlavor = PrefUtils.getCurrentAppFlavor();
        setTitle(AppSignKeyUtils.getAppTitle(currentAppFlavor, this));
    }

    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE", Manifest.permission.CAMERA, Manifest.permission.RECORD_AUDIO};

    private boolean checkOrRequestPermission(int code) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED ||
                    ContextCompat.checkSelfPermission(this, "android.permission.READ_EXTERNAL_STORAGE") != PackageManager.PERMISSION_GRANTED ||
                    ContextCompat.checkSelfPermission(this, "android.permission.WRITE_EXTERNAL_STORAGE") != PackageManager.PERMISSION_GRANTED) {
                this.requestPermissions(PERMISSIONS_STORAGE, code);
                return false;
            }
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == REQUEST_CODE_PERMISSION) {
            int i = 0;
            boolean allPermissionAllowed = true;
            for (int result : grantResults) {
                if (result != PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(this, String.format("Permission %s not granted", permissions[i]), Toast.LENGTH_SHORT).show();
                    allPermissionAllowed = false;
                    break;
                }
                i++;
            }
            if (allPermissionAllowed) {
                startSessionActivity();
            }
        } else if (requestCode == REQUEST_CODE_UPDATE_APK) {
            updateApk();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == 101) {
            ZegoAudioRoom zegoAudioRoom = ((AudioApplication) getApplication()).getAudioRoomClient();
            if (resultCode == 1) {
                ZGLog.d("on SettingsActivity Result, reInit SDK");
                long appId;
                if (data == null) {
                    appId = PrefUtils.getAppId();
                    reInitZegoSDK();
                } else {
                    currentStrSignKey = data.getStringExtra("rawKey");
                    appId = data.getLongExtra("appId", PrefUtils.getAppId());
                    if (appId != AppSignKeyUtils.UDP_APP_ID && appId != AppSignKeyUtils.INTERNATIONAL_APP_ID) {
                        PrefUtils.setAppId(appId);
                        PrefUtils.setAppKey(AppSignKeyUtils.parseSignKeyFromString(currentStrSignKey));
                    }
                    reInitZegoSDK();
                }
                setTitle(AppSignKeyUtils.getAppTitle(appId, MainActivity.this));
            } else {
                ZGLog.d("on SettingsActivity Result: %d", resultCode);
                zegoAudioRoom.setManualPublish(PrefUtils.isManualPublish());
            }

            if (PrefUtils.isManualPublish()) {
                btnLoginOrLogout.setText(R.string.zg_login_room);
            } else {
                btnLoginOrLogout.setText(R.string.zg_start_communicate);
            }
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    private void updateApk() {
        if (checkOrRequestPermission(1002) && !SystemUtil.isDebugVersion(this)) {
            /** 可选配置集成方式 **/
            new PgyUpdateManager.Builder()
                    .setForced(false)                //设置是否强制更新
                    .setUserCanRetry(false)         //失败后是否提示重新下载
                    .setDeleteHistroyApk(false)     // 检查更新前是否删除本地历史 Apk， 默认为true
                    .register();
        }
    }

    @OnClick(R.id.btn_login_logout)
    public void onLoginClick(View view) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[]{Manifest.permission.RECORD_AUDIO}, REQUEST_CODE_PERMISSION);
            } else {
                startSessionActivity();
            }
        } else {
            startSessionActivity();
        }
    }

    @butterknife.OnTextChanged(R.id.room_name)
    public void onRoomInfoChanged(CharSequence text, int start, int before, int count) {
        if (TextUtils.isEmpty(text)) {
            btnLoginOrLogout.setEnabled(false);
        } else {
            btnLoginOrLogout.setEnabled(true);
        }
    }

    private void reInitZegoSDK() {
        AudioApplication.sApplication.reInitZegoSDK();
    }

    private void startSessionActivity() {
        Intent startIntent = new Intent(MainActivity.this, ZegoPhoneActivity.class);
        startIntent.putExtra("roomId", ctrlRoomName.getText().toString().trim());
        startIntent.putExtra("title", AppSignKeyUtils.getAppTitle(currentAppId, MainActivity.this));
        startActivity(startIntent);
    }

    static public class ZGLog {
        static private final String TAG = "AudioLiveDemo";

        static private WeakReference<AudioApplication> appRef = new WeakReference<AudioApplication>(AudioApplication.sApplication);
        static private SimpleDateFormat sDateFormat = new SimpleDateFormat("HH:mm:ss.SSS");

        static public void d(@NonNull String format, Object... args) {
            String message = String.format(format, args);
            Log.d(TAG, message);
            appendLog(message);
        }

        static public void w(@NonNull String format, Object... args) {
            String message = String.format(format, args);
            Log.w(TAG, message);
        }

        static private void appendLog(String message) {
            AudioApplication app = appRef.get();
            if (app != null) {
                String datetime = sDateFormat.format(new Date());
                app.appendLog("[%s] %s", datetime, message);
            }
        }
    }
}
