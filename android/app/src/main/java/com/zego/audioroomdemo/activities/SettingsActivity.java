package com.zego.audioroomdemo.activities;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.SystemClock;
import android.provider.Settings;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.alibaba.fastjson.JSONObject;
import com.dommy.qrcode.util.Constant;
import com.google.zxing.activity.CaptureActivity;
import com.zego.audioroomdemo.AudioApplication;
import com.zego.audioroomdemo.entity.AppConfig;
import com.zego.audioroomdemo.utils.AppSignKeyUtils;
import com.zego.audioroomdemo.utils.PrefUtils;
import com.zego.audioroomdemo.R;
import com.zego.audioroomdemo.utils.ShareUtils;
import com.zego.audioroomdemo.utils.SystemUtil;
import com.zego.zegoaudioroom.*;
import com.zego.zegoliveroom.ZegoLiveRoom;

import java.io.File;
import java.io.FilenameFilter;

import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class SettingsActivity extends AppCompatActivity {

    @Bind(R.id.tv_version)
    public TextView tvVersion;

    @Bind(R.id.tv_version2)
    public TextView tvVersion2;

    @Bind(R.id.tv_user_id)
    public EditText tvUserId;

    @Bind(R.id.tv_user_name)
    public EditText etUserName;

    @Bind(R.id.checkbox_use_test_env)
    public CheckBox cbUseTestEnv;

    @Bind(R.id.checkbox_audio_prepare)
    public CheckBox cbTurnOnAudioPrepare;

    @Bind(R.id.sp_app_flavor)
    public Spinner spAppFlavors;

    @Bind(R.id.et_app_id)
    public EditText etAppId;

    @Bind(R.id.ll_app_key)
    public LinearLayout llAppKey;

    @Bind(R.id.et_app_key)
    public EditText etAppKey;

    @Bind(R.id.container)
    public RelativeLayout llContainer;

    @Bind(R.id.tv_demo_version)
    public TextView tvDemoVersion;


    private boolean oldUseTestEnvValue;
    private boolean oldAudioPrepareValue;
    private boolean oldManualPublishValue;
    private String oldUserName;
    private String oldUserId;
    private long appId = 0;
    private long oldAppId;
    private String signKey;

    private CompoundButton.OnCheckedChangeListener checkedChangeListener = new CompoundButton.OnCheckedChangeListener() {

        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            switch (buttonView.getId()) {
                case R.id.checkbox_audio_prepare:
                    PrefUtils.enableAudioPrepare(isChecked);
                    break;

                case R.id.checkbox_use_test_env:
                    AudioApplication.sApplication.setUseTestEnv(isChecked);
                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        ButterKnife.bind(this);
        final Intent startIntent = getIntent();
        tvVersion.setText(ZegoAudioRoom.version());
        tvVersion2.setText(ZegoAudioRoom.version2());
        appId = (startIntent != null && startIntent.hasExtra("appId")) ? startIntent.getLongExtra("appId", -1) : -1;
        signKey = (startIntent != null && startIntent.hasExtra("rawKey")) ? startIntent.getStringExtra("rawKey") : "";


        spAppFlavors.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                reInitSDK = true;

                PrefUtils.setAppFlavor(position);
                if (position == 2) {
                    appId = PrefUtils.getAppId();
                    signKey = PrefUtils.getAppKeyToString();
                    if (appId > 0 && !TextUtils.isEmpty(signKey)) {
                        etAppId.setText(String.valueOf(appId));
                        etAppKey.setText(String.valueOf(signKey));
                    } else {

                        etAppId.setText("");
                        etAppKey.setText("");

                    }

                    etAppId.setEnabled(true);
                    llAppKey.setVisibility(View.VISIBLE);
                } else {
                    switch (position) {
                        case 0:
                            appId = AppSignKeyUtils.UDP_APP_ID;
                            break;

                        case 1:
                            appId = AppSignKeyUtils.INTERNATIONAL_APP_ID;
                            break;
                    }

                    etAppId.setEnabled(false);
                    etAppId.setText(String.valueOf(appId));

                    byte[] signKey = AppSignKeyUtils.requestSignKey(appId);
                    etAppKey.setText(AppSignKeyUtils.convertSignKey2String(signKey));
                    llAppKey.setVisibility(View.GONE);
                }
                setTitle(AppSignKeyUtils.getAppTitle(appId, SettingsActivity.this));
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });


//        oldAppId = (startIntent != null) ? startIntent.getLongExtra("appId", -1) : -1;
//        if (AppSignKeyUtils.isUdpProduct(oldAppId) || oldAppId == -1L) {
//            spAppFlavors.setSelection(0);
//            startIntent.removeExtra("appId");
//        } else if (AppSignKeyUtils.isInternationalProduct(oldAppId)) {
//            spAppFlavors.setSelection(1);
//            startIntent.removeExtra("appId");
//        } else {
//            spAppFlavors.setSelection(2);
//        }

        spAppFlavors.setSelection(PrefUtils.getCurrentAppFlavor());

        oldUserId = PrefUtils.getUserId();
        tvUserId.setText(oldUserId);

        oldUserName = PrefUtils.getUserName();
        etUserName.setText(oldUserName);

        oldUseTestEnvValue = AudioApplication.sApplication.isUseTestEnv();
        cbUseTestEnv.setChecked(oldUseTestEnvValue);

        oldAudioPrepareValue = PrefUtils.isEnableAudioPrepare();
        cbTurnOnAudioPrepare.setChecked(oldAudioPrepareValue);

        oldManualPublishValue = PrefUtils.isManualPublish();

        cbUseTestEnv.setOnCheckedChangeListener(checkedChangeListener);
        cbTurnOnAudioPrepare.setOnCheckedChangeListener(checkedChangeListener);


        tvDemoVersion.setText(SystemUtil.getAppVersionName(this));

        llContainer.setOnClickListener(new View.OnClickListener() {

            private long[] mHits = new long[5];

            @Override
            public void onClick(View v) {
                System.arraycopy(mHits, 1, mHits, 0, mHits.length - 1);
                mHits[mHits.length - 1] = SystemClock.uptimeMillis();
                if (mHits[0] >= SystemClock.uptimeMillis() - 700) {
                    sendLog2App();

                    for (int i = 0; i < mHits.length; i++) {
                        mHits[i] = 0;
                    }
                }
            }
        });

        etAppId.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                String appId = s.toString();
                if ("1".equals(appId)) {

                    etAppKey.setText(AppSignKeyUtils.convertSignKey2String(AppSignKeyUtils.requestSignKey(1l)));
                }
            }
        });

    }

    private final static int REQ_CODE = 1028;
    AppConfig appConfig = null;

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQ_CODE && data != null) {
            Bundle bundle = data.getExtras();
            String result = bundle.getString(Constant.INTENT_EXTRA_KEY_QR_SCAN);
            if (result != null) {
                try {
                    JSONObject jsonObject = JSONObject.parseObject(result);
                    if ("ac".equals(jsonObject.getString("type"))) {
                        appConfig = jsonObject.getObject("data", AppConfig.class);
                        PrefUtils.setAppId(appConfig.appid);
                        PrefUtils.setAppKey(AppSignKeyUtils.parseSignKeyFromString(appConfig.appkey));
                        PrefUtils.setUseTestEnv(appConfig.isTestenv());
                        PrefUtils.setBusinessType(appConfig.getBusinesstype());
                        PrefUtils.setInternational(appConfig.isI18n());
                        setResult(1, null);
                        spAppFlavors.setSelection(2);
                        Toast.makeText(this, getString(R.string.zg_toast_config_successful), Toast.LENGTH_LONG).show();
                        finish();
                    }
                } catch (Exception e) {
                    Toast.makeText(this, getString(R.string.zg_toast_config_failure), Toast.LENGTH_LONG).show();
                }
            }
        }
    }

    public void scan(View view) {
        if (checkOrRequestPermission(REQUEST_PERMISSION_CODE)) {
            startActivityForResult(new Intent(this, CaptureActivity.class), REQ_CODE);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case REQUEST_PERMISSION_CODE: {
                boolean allPermissionGranted = true;
                for (int i = 0; i < grantResults.length; i++) {
                    if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                        allPermissionGranted = false;
                        Toast.makeText(this, String.format("获取%s权限失败 ", permissions[i]), Toast.LENGTH_LONG).show();
                    }
                }
                if (allPermissionGranted) {

                } else {
                    Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                    intent.setData(Uri.parse("package:" + this.getPackageName()));
                    startActivity(intent);
                }
                break;
            }
        }
    }

    private final int REQUEST_PERMISSION_CODE = 0506;

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


    @OnClick(R.id.share_log_button)
    public void shareLog() {
        ZegoLogShareActivity.actionStart(this);
    }

    boolean reInitSDK = false;

    @Override
    public void onBackPressed() {
        String _appIdStr = etAppId.getEditableText().toString();
        String appKey = etAppKey.getEditableText().toString();
        Editable userIdEdi = tvUserId.getEditableText();
        long appId = 0;
        if (!TextUtils.isEmpty(_appIdStr)) {
            try {
                appId = Long.valueOf(_appIdStr);
            } catch (NumberFormatException e) {
                Toast.makeText(this, R.string.zg_tip_appid_format_illegal, Toast.LENGTH_LONG).show();
                etAppId.requestFocus();
                return;
            }
        }

        // appKey长度必须等于32位
        byte[] signKey;
        try {
            signKey = AppSignKeyUtils.parseSignKeyFromString(appKey);
        } catch (NumberFormatException e) {
            Toast.makeText(this, R.string.zg_tip_appkey_must_32_bits, Toast.LENGTH_LONG).show();
            etAppKey.requestFocus();
            return;
        }

        Intent resultIntent = null;
        if (appId != oldAppId) {
            resultIntent = new Intent();
            resultIntent.putExtra("appId", appId);
            resultIntent.putExtra("signKey", signKey);
            resultIntent.putExtra("rawKey", appKey);
            reInitSDK = true;

            if (PrefUtils.getCurrentAppFlavor() == 2 || !AppSignKeyUtils.isInternationalProduct(appId) && !AppSignKeyUtils.isUdpProduct(appId)) {
                PrefUtils.setAppId(appId);
                PrefUtils.setAppKey(signKey);
            }

        }

        String userName = etUserName.getEditableText().toString();
        if (!TextUtils.equals(userName, oldUserName)
                && !TextUtils.isEmpty(userName)) {
            PrefUtils.setUserName(userName);
            reInitSDK = true;
        }

        String userId = userIdEdi.toString();

        if (!TextUtils.equals(userId, oldUserId) && !TextUtils.isEmpty(userId)) {

            PrefUtils.setUserId(userId);

        }

        reInitSDK = reInitSDK | (PrefUtils.isEnableAudioPrepare() != oldAudioPrepareValue);
        reInitSDK = reInitSDK | (AudioApplication.sApplication.isUseTestEnv() != oldUseTestEnvValue);
        setResult(reInitSDK ? 1 : 0, resultIntent);

        super.onBackPressed();
    }

    private void sendLog2App() {
        String rootPath = com.zego.zegoavkit2.utils.ZegoLogUtil.getLogPath(this);
        File rootDir = new File(rootPath);
        File[] logFiles = rootDir.listFiles(new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                return !TextUtils.isEmpty(name) && name.startsWith("zegoavlog") && name.endsWith(".txt");
            }
        });

        if (logFiles.length > 0) {
            ShareUtils.sendFiles(logFiles, this);
        } else {
            Log.w("SettingFragment", "not found any log files.");
        }
    }
}
