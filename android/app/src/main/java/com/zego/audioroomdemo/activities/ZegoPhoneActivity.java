package com.zego.audioroomdemo.activities;


import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothHeadset;
import android.bluetooth.BluetoothProfile;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.databinding.DataBindingUtil;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.os.PowerManager;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.Toast;

import com.alibaba.fastjson.JSONException;
import com.alibaba.fastjson.JSONObject;
import com.zego.audioroomdemo.AudioApplication;
import com.zego.audioroomdemo.MainActivity;
import com.zego.audioroomdemo.R;
import com.zego.audioroomdemo.adapters.RecyclerGridViewAdapter;
import com.zego.audioroomdemo.databinding.ActivityZegoPhoneBinding;
import com.zego.audioroomdemo.entity.StreamState;
import com.zego.audioroomdemo.utils.PrefUtils;
import com.zego.audioroomdemo.utils.SystemUtil;
import com.zego.zegoaudioroom.ZegoAudioAVEngineDelegate;
import com.zego.zegoaudioroom.ZegoAudioDeviceEventDelegate;
import com.zego.zegoaudioroom.ZegoAudioLiveEvent;
import com.zego.zegoaudioroom.ZegoAudioLiveEventDelegate;
import com.zego.zegoaudioroom.ZegoAudioLivePlayerDelegate;
import com.zego.zegoaudioroom.ZegoAudioLivePublisherDelegate;
import com.zego.zegoaudioroom.ZegoAudioLiveRecordDelegate;
import com.zego.zegoaudioroom.ZegoAudioPrepDelegate2;
import com.zego.zegoaudioroom.ZegoAudioPrepareDelegate;
import com.zego.zegoaudioroom.ZegoAudioRoom;
import com.zego.zegoaudioroom.ZegoAudioRoomDelegate;
import com.zego.zegoaudioroom.ZegoAudioStream;
import com.zego.zegoaudioroom.ZegoAudioStreamType;
import com.zego.zegoaudioroom.ZegoAuxData;
import com.zego.zegoaudioroom.ZegoLoginAudioRoomCallback;
import com.zego.zegoavkit2.IZegoMediaPlayerCallback;
import com.zego.zegoavkit2.ZegoMediaPlayer;
import com.zego.zegoavkit2.soundlevel.IZegoSoundLevelCallback;
import com.zego.zegoavkit2.soundlevel.ZegoSoundLevelInfo;
import com.zego.zegoavkit2.soundlevel.ZegoSoundLevelMonitor;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoIM;
import com.zego.zegoliveroom.entity.ZegoAudioFrame;
import com.zego.zegoliveroom.entity.ZegoConversationMessage;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;
import com.zego.zegoliveroom.entity.ZegoUserState;


import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import static com.zego.zegoaudioroom.ZegoAudioLiveEvent.Audio_Play_BeginRetry;
import static com.zego.zegoaudioroom.ZegoAudioLiveEvent.Audio_Play_RetrySuccess;
import static com.zego.zegoaudioroom.ZegoAudioLiveEvent.Audio_Play_TempDisconnected;
import static com.zego.zegoaudioroom.ZegoAudioLiveEvent.Audio_Publish_BeginRetry;
import static com.zego.zegoaudioroom.ZegoAudioLiveEvent.Audio_Publish_RetrySuccess;
import static com.zego.zegoaudioroom.ZegoAudioLiveEvent.Audio_Publish_TempDisconnected;


/**
 * Created by zego on 2018/6/26.
 */

public class ZegoPhoneActivity extends AppCompatActivity implements SensorEventListener {

    ActivityZegoPhoneBinding activityZegoPhoneBinding;
    private ZegoAudioRoom zegoAudioRoom;
    private String currentRoomId;
    private String appTitle;
    private ZegoUserState zegoUserState = new ZegoUserState();
    private RecyclerGridViewAdapter recyclerGridViewAdapter;
    /**
     * 是否已经推流
     */
    private boolean hasPublish = false;

    private String publishStreamId = null;

    private boolean hasLogin = false;

    private boolean hasBoom = false;

    private ZegoMediaPlayer zegoMediaPlayer = null;

    private Handler handler;

    final int RESTART_PUBLSH_MSG = 1;

    private HandlerThread handlerThread;

    int restartCount = 0;

    private boolean isPromptToast = true;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        //获取系统服务POWER_SERVICE，返回一个PowerManager对象
        localPowerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
        //获取PowerManager.WakeLock对象,后面的参数|表示同时传入两个值,最后的是LogCat里用的Tag
        localWakeLock = this.localPowerManager.newWakeLock(32, "MyPower");//第一个参数为电源锁级别，第二个是日志tag
        handlerThread = new HandlerThread("music");
        handlerThread.start();
        handler = new Handler(handlerThread.getLooper(), new Handler.Callback() {
            @Override
            public boolean handleMessage(Message msg) {
                if (msg.what == RESTART_PUBLSH_MSG) {

                    //计数器
                    if (restartCount <= 10) {
                        restartCount++;
                        /**
                         * 重新推流
                         */
                        boolean restartState = zegoAudioRoom.restartPublishStream();
                        MainActivity.ZGLog.d(" Handler handleMessage restartPublish : %b", restartState);
                        /**
                         * 超过10次后给用户提示,只提示1次
                         */
                    } else if (isPromptToast) {
                        isPromptToast = false;
                        MainActivity.ZGLog.d(" Handler handleMessage restartPublish restartCount: %d", restartCount);
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(ZegoPhoneActivity.this, getString(R.string.zg_text_app_restart_publish_failure), Toast.LENGTH_LONG).show();
                            }
                        });
                    }
                }
                return false;
            }
        });


        //  ActivityBaseBinding 类是自动生成的
        activityZegoPhoneBinding = DataBindingUtil.setContentView(this, R.layout.activity_zego_phone);
        //  activityZegoPhoneBinding.userRecyclerView
        zegoAudioRoom = ((AudioApplication) getApplication()).getAudioRoomClient();
        Intent startIntent = getIntent();
        String roomId = startIntent.getStringExtra("roomId");
        if (TextUtils.isEmpty(roomId)) {
            Toast.makeText(this, R.string.zg_tip_parameter_illegal, Toast.LENGTH_LONG).show();
            finish();
        } else {
            currentRoomId = roomId;
            appTitle = startIntent.getStringExtra("title");

            setupCallbacks();
            login(roomId);
        }

        initMediaPlayer();

        activityZegoPhoneBinding.toolbar.setTitleTextColor(Color.WHITE);

        setSupportActionBar(activityZegoPhoneBinding.toolbar);
        getSupportActionBar().setTitle(getString(R.string.zg_btn_room_name, currentRoomId));
        GridLayoutManager mgr = new GridLayoutManager(this, 3);
        activityZegoPhoneBinding.userRecyclerView.setLayoutManager(mgr);
        recyclerGridViewAdapter = new RecyclerGridViewAdapter(this.getApplicationContext(), activityZegoPhoneBinding.userRecyclerView);
        activityZegoPhoneBinding.userRecyclerView.setAdapter(recyclerGridViewAdapter);

        zegoAudioRoom.enableAECWhenHeadsetDetected(true);


        activityZegoPhoneBinding.btnMic.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                enableMic(isChecked);
            }
        });

        activityZegoPhoneBinding.log.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent startIntent = new Intent(ZegoPhoneActivity.this, LogsActivity.class);
                startActivity(startIntent);
            }
        });

        activityZegoPhoneBinding.advanced.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (hasBoom) {
                    hasBoom = false;
                    activityZegoPhoneBinding.boomAdvanced.setVisibility(View.GONE);
                } else {
                    hasBoom = true;
                    activityZegoPhoneBinding.boomAdvanced.setVisibility(View.VISIBLE);
                }
            }
        });

        activityZegoPhoneBinding.play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String stop = getString(R.string.zg_btn_text_stop);
                String play = getString(R.string.zg_btn_text_play);
                if (activityZegoPhoneBinding.play.getText().equals(stop)) {
                    activityZegoPhoneBinding.play.setText(play);
                    stopMusic();
                } else {
                    activityZegoPhoneBinding.play.setText(stop);
                    playMusic();
                }
            }
        });

        activityZegoPhoneBinding.btnSpeaker.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                speaker = !isChecked;
                builtinSpeakerOn(isChecked);
            }
        });

        activityZegoPhoneBinding.btnSpeaker.setChecked(true);
        builtinSpeakerOn(true);
        registerHeadsetPlug();

        activityZegoPhoneBinding.exitPhone.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });

        // 开启音浪监听
        soundLevel();
    }

    private void stopMusic() {
        zegoMediaPlayer.stop();
    }

    private void playMusic() {
        handler.post(new Runnable() {
            @Override
            public void run() {
                path = SystemUtil.copyAssetsFile2Phone(ZegoPhoneActivity.this, "test.mp3");
                if (path != null) {
                    zegoMediaPlayer.start(path, false);
                } else {
                    Toast.makeText(ZegoPhoneActivity.this, getString(R.string.zg_toast_text_play_path_error), Toast.LENGTH_LONG).show();
                }
            }
        });

    }


    private void initMediaPlayer() {
        zegoMediaPlayer = new ZegoMediaPlayer();
        zegoMediaPlayer.init(ZegoMediaPlayer.PlayerTypeAux);


        zegoMediaPlayer.setCallback(new IZegoMediaPlayerCallback() {
            @Override
            public void onPlayStart() {
                activityZegoPhoneBinding.play.post(new Runnable() {
                    @Override
                    public void run() {
                        activityZegoPhoneBinding.play.setText(getString(R.string.zg_btn_text_stop));
                    }
                });
            }

            @Override
            public void onPlayError(int i) {

            }

            @Override
            public void onPlayPause() {

            }

            @Override
            public void onPlayStop() {

            }

            @Override
            public void onPlayResume() {

            }

            @Override
            public void onVideoBegin() {

            }

            @Override
            public void onAudioBegin() {

            }

            @Override
            public void onPlayEnd() {
                activityZegoPhoneBinding.play.post(new Runnable() {
                    @Override
                    public void run() {
                        activityZegoPhoneBinding.play.setText(getString(R.string.zg_btn_text_play));
                    }
                });
            }

            @Override
            public void onBufferBegin() {

            }

            @Override
            public void onBufferEnd() {

            }

            @Override
            public void onSeekComplete(int i, long l) {

            }
        });


    }

    String path = null;

    boolean speaker = false;

    @Override
    protected void onResume() {
        super.onResume();
    }

    private void unregisterSensor() {
        localWakeLock.setReferenceCounted(false);
        localWakeLock.release();
        mManager.unregisterListener(this);
    }

    private void registerSensor() {
        this.localPowerManager.newWakeLock(32, "MyPower");
        mManager.registerListener(this, mManager.getDefaultSensor(Sensor.TYPE_PROXIMITY),// 距离感应器
                SensorManager.SENSOR_DELAY_NORMAL);//注册传感器，第一个参数为距离监听器，第二个是传感器类型，第三个是延迟类型
    }

    HeadSetReceiver mReceiver;

    private void registerHeadsetPlug() {
        mReceiver = new HeadSetReceiver();
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(Intent.ACTION_HEADSET_PLUG);
        intentFilter.addAction(BluetoothHeadset.ACTION_CONNECTION_STATE_CHANGED);
        registerReceiver(mReceiver, intentFilter);
    }


    /**
     * receiver监听
     */
    public class HeadSetReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (BluetoothHeadset.ACTION_CONNECTION_STATE_CHANGED.equals(action)) {
                BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
                if (BluetoothProfile.STATE_DISCONNECTED == adapter.getProfileConnectionState(BluetoothProfile.HEADSET)) {
                    //Bluetooth headset is now disconnected
                }
            } else if ("android.intent.action.HEADSET_PLUG".equals(action)) {
                if (intent.hasExtra("state")) {
                    if (intent.getIntExtra("state", 0) == 0) {
                        activityZegoPhoneBinding.btnSpeaker.setEnabled(true);
                        activityZegoPhoneBinding.btnSpeaker.setAlpha(1f);
                    } else if (intent.getIntExtra("state", 0) == 1) {
                        activityZegoPhoneBinding.btnSpeaker.setEnabled(false);
                        activityZegoPhoneBinding.btnSpeaker.setAlpha(0.5f);
                    }
                }
            }
        }
    }


    private void soundLevel() {
        ZegoSoundLevelMonitor.getInstance().setCallback(new IZegoSoundLevelCallback() {
            @Override
            public void onSoundLevelUpdate(ZegoSoundLevelInfo[] zegoSoundLevelInfos) {
                for (ZegoSoundLevelInfo zegoSoundLevelInfo : zegoSoundLevelInfos) {
                    if (recyclerGridViewAdapter != null) {
                        recyclerGridViewAdapter.soundLevelUpdate(zegoSoundLevelInfo);
                    }
                }
            }

            @Override
            public void onCaptureSoundLevelUpdate(ZegoSoundLevelInfo zegoSoundLevelInfo) {
                if (recyclerGridViewAdapter != null) {
                    recyclerGridViewAdapter.soundLevelUpdate(zegoSoundLevelInfo);
                }
            }
        });

        ZegoSoundLevelMonitor.getInstance().start();
    }

    /**
     * 开启麦克风
     *
     * @param enable true为关闭麦克风 false为开启麦克风
     */
    private void enableMic(final boolean enable) {

        if (zegoAudioRoom != null) {
            if (zegoAudioRoom.enableMic(enable)) {
                StreamState streamState = new StreamState();
                streamState.setEnable_mic(enable);

                JSONObject jsonObject = new JSONObject();
                try {
                    jsonObject.put("stream_state", streamState);
                } catch (JSONException e) {
                    e.printStackTrace();
                }

                zegoAudioRoom.updateStreamExtraInfo(jsonObject.toString());

                recyclerGridViewAdapter.updateMuteState(enable, PrefUtils.getUserName());
            }
        }

    }


    private void builtinSpeakerOn(boolean enable) {
        if (zegoAudioRoom != null) {
            if (enable) {
                unregisterSensor();
            } else {
                registerSensor();
            }
            zegoAudioRoom.setBuiltinSpeakerOn(enable);
        }
    }


    private void login(String roomId) {

        // TODO 开始登陆房间
        zegoAudioRoom.setUserStateUpdate(true);
        zegoAudioRoom.enableAux(false);
        zegoAudioRoom.enableMic(true);
        zegoAudioRoom.enableSelectedAudioRecord(ZegoConstants.AudioRecordMask.NoRecord, 44100);
        zegoAudioRoom.enableSpeaker(true);
        boolean success = zegoAudioRoom.
                loginRoom(roomId, new ZegoLoginAudioRoomCallback() {
            @SuppressLint("DefaultLocale")
            @Override
            public void onLoginCompletion(int state) {
                MainActivity.ZGLog.d("onLoginCompletion: %d", state);

                if (state == 0) {
                    hasLogin = true;
                    zegoUserState.userID = PrefUtils.getUserId();
                    zegoUserState.userName = PrefUtils.getUserName();
                    recyclerGridViewAdapter.addUser(zegoUserState);
                    recyclerGridViewAdapter.setSelfZegoUser(zegoUserState);
                    enableMic(true);

                    // TODO 登陆成功
                } else {
                    Toast.makeText(ZegoPhoneActivity.this, String.format("Login Error: %d", state), Toast.LENGTH_LONG).show();
                    // TODO 登陆失败错误码
                }
            }
        });

        MainActivity.ZGLog.d("login: %s", success);
        if (!success) {
            // TODO 登陆失败
        }
    }


    private void setupCallbacks() {
        zegoAudioRoom.setAudioRoomDelegate(new ZegoAudioRoomDelegate() {
            @Override
            public void onKickOut(int errorCode, String roomId) {
                MainActivity.ZGLog.d("onKickOut room: %s, errorCode: %d", roomId, errorCode);
                // TODO 被踢出房间
            }

            @Override
            public void onDisconnect(int errorCode, String roomId) {
                MainActivity.ZGLog.d("onDisconnect room: %s, errorCode: %d", roomId, errorCode);
                // TODO 与房间断开连接, 错误码
                recyclerGridViewAdapter.streamStateUpdateAll(1);
            }

            @Override
            public void onStreamUpdate(final ZegoAudioStreamType zegoAudioStreamType, final ZegoAudioStream zegoAudioStream) {
                activityZegoPhoneBinding.userRecyclerView.post(new Runnable() {
                    @Override
                    public void run() {
                        MainActivity.ZGLog.d("onStreamUpdate, type: %s, streamId: %s", zegoAudioStreamType, zegoAudioStream.getStreamId());
                        ZegoUserState zegoUserState = new ZegoUserState();
                        zegoUserState.userID = zegoAudioStream.getUserId();
                        zegoUserState.userName = zegoAudioStream.getUserName();
                        switch (zegoAudioStreamType) {
                            case ZEGO_AUDIO_STREAM_ADD:
                                // TODO 新增流
                                recyclerGridViewAdapter.addUser(zegoUserState);
                                recyclerGridViewAdapter.bindUserInfoStreamID(zegoAudioStream);
                                String extraInfo = zegoAudioStream.getExtraInfo();
                                if (extraInfo != null) {
                                    JSONObject jsonObject = JSONObject.parseObject(extraInfo);
                                    if (jsonObject != null) {
                                        StreamState streamState = jsonObject.getObject("stream_state", StreamState.class);
                                        recyclerGridViewAdapter.updateMuteState(streamState.getEnable_mic(), zegoAudioStream.getUserName());
                                    }
                                }
                                break;
                            case ZEGO_AUDIO_STREAM_DELETE:
                                // TODO 删除流
                                recyclerGridViewAdapter.removeUser(zegoUserState);
                                break;
                            default:
                                break;

                        }
                    }
                });
            }

            @Override
            public void onUserUpdate(ZegoUserState[] userList, int updateType) {
                MainActivity.ZGLog.d("onUserUpdate, updateType: " + (updateType == ZegoIM.UserUpdateType.Increase ? "Increase" : "Total"));
                for (ZegoUserState user : userList) {
                    MainActivity.ZGLog.d("onUserUpdate, userName: " + user.userName + "; updateFlag: " + (user.updateFlag == ZegoIM.UserUpdateFlag.Added ? "Add" : "Delete"));
                    if (user.updateFlag == ZegoIM.UserUpdateFlag.Added) {
                        // TODO 新增用户
                        recyclerGridViewAdapter.addUser(user);
                    } else {
                        // TODO 删除用户
                        recyclerGridViewAdapter.removeUser(user);
                    }
                }
            }

            @Override
            public void onUpdateOnlineCount(String s, int i) {
                MainActivity.ZGLog.d("online count: %d", i);
            }

            @Override
            public void onRecvRoomMessage(String roomId, ZegoRoomMessage[] messages) {
                // TODO 房间消息
            }

            @Override
            public void onRecvConversationMessage(String roomId, String conversationId, ZegoConversationMessage message) {
                MainActivity.ZGLog.d("onRecvConversationMessage, roomId: %s; conversationId: %s", roomId, conversationId);
            }

            @Override
            public void onRecvBigRoomMessage(String s, com.zego.zegoliveroom.entity.ZegoBigRoomMessage[] zegoBigRoomMessages) {
                MainActivity.ZGLog.d("onRecvBigRoomMessage, roomId: %s", s);
            }

            @Override
            public void onRecvCustomCommand(String userId, String userName, String content, String roomId) {
                MainActivity.ZGLog.d("onRecvCustomCommand, userId: %s; roomId: %s; content: %s", userId, roomId, content);

            }

            @Override
            public void onStreamExtraInfoUpdated(final ZegoAudioStream[] zegoStreamInfos, String s) {
                activityZegoPhoneBinding.userRecyclerView.post(new Runnable() {
                    @Override
                    public void run() {
                        // TODO 流信息额外更新
                        for (ZegoAudioStream zegoStreamInfo : zegoStreamInfos) {
                            String extraInfo = zegoStreamInfo.getExtraInfo();
                            if (extraInfo != null) {
                                JSONObject jsonObject = JSONObject.parseObject(extraInfo);
                                StreamState streamState = jsonObject.getObject("stream_state", StreamState.class);
                                if (streamState != null)
                                    recyclerGridViewAdapter.updateMuteState(streamState.getEnable_mic(), zegoStreamInfo.getUserName());
                            }
                        }
                    }
                });
            }
        });

        zegoAudioRoom.setAudioPublisherDelegate(new ZegoAudioLivePublisherDelegate() {

            @Override
            public void onPublishStateUpdate(int stateCode, String streamId, HashMap<String, Object> info) {
                MainActivity.ZGLog.d("onPublishStateUpdate, stateCode: %d, streamId: %s, info: %s", stateCode, streamId, info);

                ZegoAudioStream myStream = new ZegoAudioStream(streamId, PrefUtils.getUserId(), PrefUtils.getUserName());
                if (stateCode == 0) {
                    hasPublish = true;
                    publishStreamId = streamId;

                    recyclerGridViewAdapter.bindUserInfoStreamID(myStream);

                    /**
                     * 清空重试计数器
                     */

                } else {
                    // TODO 推流失败
                    recyclerGridViewAdapter.streamStateUpdate(1, myStream);
                    /**
                     * 延时10秒后开启重新推流
                     */
                    handler.removeMessages(RESTART_PUBLSH_MSG);
                    handler.sendMessageDelayed(handler.obtainMessage(RESTART_PUBLSH_MSG), 10000);
                }

            }

            @Override
            public ZegoAuxData onAuxCallback(int dataLen) {

                return null;
            }

            @Override
            public void onPublishQualityUpdate(String streamId, ZegoStreamQuality zegoStreamQuality) {
                MainActivity.ZGLog.d("onPublishQualityUpdate, streamId: %s, quality: %d, audioBitrate: %fkb",
                        streamId, zegoStreamQuality.quality, zegoStreamQuality.audioBitrate);
                // 推流质量更新
                recyclerGridViewAdapter.updateQualityUpdate(streamId, zegoStreamQuality);
            }
        });
        zegoAudioRoom.setAudioPlayerDelegate(new ZegoAudioLivePlayerDelegate() {
            @Override
            public void onPlayStateUpdate(int stateCode, ZegoAudioStream zegoAudioStream) {
                MainActivity.ZGLog.d("onPlayStateUpdate, stateCode: %d, streamId: %s", stateCode, zegoAudioStream.getStreamId());
                if (stateCode == 0) {
                    recyclerGridViewAdapter.bindUserInfoStreamID(zegoAudioStream);
                } else {
                    recyclerGridViewAdapter.streamStateUpdate(1, zegoAudioStream);
                }

            }

            @Override
            public void onPlayQualityUpdate(String streamId, ZegoStreamQuality zegoStreamQuality) {
                MainActivity.ZGLog.d("onPlayQualityUpdate, streamId: %s, quality: %d,  audioBitrate: %fkb",
                        streamId, zegoStreamQuality.quality, zegoStreamQuality.audioBitrate);
                // 拉流质量更新
                recyclerGridViewAdapter.updateQualityUpdate(streamId, zegoStreamQuality);
                ZegoAudioStream zegoAudioStream = new ZegoAudioStream();
                zegoAudioStream.setStreamId(streamId);
            }
        });
        zegoAudioRoom.setAudioLiveEventDelegate(new ZegoAudioLiveEventDelegate() {
            @Override
            public void onAudioLiveEvent(ZegoAudioLiveEvent zegoAudioLiveEvent, HashMap<String, String> info) {
                MainActivity.ZGLog.d("onAudioLiveEvent, event: %s, info: %s", zegoAudioLiveEvent, info);
                ZegoAudioStream mZegoAudioStream = new ZegoAudioStream();
                String streamID = info.get("StreamID");
                mZegoAudioStream.setStreamId(streamID);
                // 开始
                if (zegoAudioLiveEvent == Audio_Play_BeginRetry || zegoAudioLiveEvent == Audio_Publish_BeginRetry) {
                    recyclerGridViewAdapter.streamStateUpdate(2, mZegoAudioStream);
                } else if (zegoAudioLiveEvent == Audio_Play_RetrySuccess || zegoAudioLiveEvent == Audio_Publish_RetrySuccess) {
                    recyclerGridViewAdapter.streamStateUpdate(0, mZegoAudioStream);
                } else if (zegoAudioLiveEvent == Audio_Play_TempDisconnected || zegoAudioLiveEvent == Audio_Publish_TempDisconnected) {
                    recyclerGridViewAdapter.streamStateUpdate(1, mZegoAudioStream);
                }
            }
        });
        zegoAudioRoom.setAudioRecordDelegate(new ZegoAudioLiveRecordDelegate() {
            private long lastCallbackTime = 0;

            @Override
            public void onAudioRecord(byte[] audioData, int sampleRate, int numberOfChannels, int bitDepth, int type) {
                long nowTime = System.currentTimeMillis();
                if (nowTime - lastCallbackTime > 1000) {    // 过滤不停回调显示太多日志，只需要有一条日志表示有回调就可以了
                    MainActivity.ZGLog.d("onAudioRecord, sampleRate: %d, numberOfChannels: %d, bitDepth: %d, type: %d", sampleRate, numberOfChannels, bitDepth, type);
                }
                lastCallbackTime = nowTime;
            }
        });
        zegoAudioRoom.setAudioDeviceEventDelegate(new ZegoAudioDeviceEventDelegate() {
            @Override
            public void onAudioDevice(String deviceName, int errorCode) {
                MainActivity.ZGLog.d("onAudioDevice, deviceName: %s, errorCode: %d", deviceName, errorCode);
            }
        });
        zegoAudioRoom.setAudioPrepareDelegate(new ZegoAudioPrepareDelegate() {
            private long lastCallbackTime = 0;

            @Override
            public void onAudioPrepared(ByteBuffer inData, int sampleCount, int bitDepth, int sampleRate, ByteBuffer outData) {
                long nowTime = System.currentTimeMillis();
                if (nowTime - lastCallbackTime > 1000) {    // 过滤不停回调显示太多日志，只需要有一条日志表示有回调就可以了
                    MainActivity.ZGLog.d("onAudioPrepared, inData is null? %s, sampleCount: %d, bitDepth: %d, sampleRate: %d",
                            inData == null, sampleCount, bitDepth, sampleRate);
                }
                lastCallbackTime = nowTime;
                if (inData != null && outData != null) {
                    inData.position(0);
                    outData.position(0);
                    // outData的长度固定为sampleCount * bitDepth
                    // 不可更改
                    outData.limit(sampleCount * bitDepth);
                    // 将处理后的数据返回sdk
                    outData.put(inData);
                }
            }
        });

        zegoAudioRoom.setAudioPrepDelegate2(new ZegoAudioPrepDelegate2() {
            @Override
            public ZegoAudioFrame onAudioPrep(ZegoAudioFrame zegoAudioFrame) {
                return zegoAudioFrame;
            }
        });
        zegoAudioRoom.setAudioAVEngineDelegate(new ZegoAudioAVEngineDelegate() {
            @Override
            public void onAVEngineStop() {
                MainActivity.ZGLog.d("onAVEngineStop");
            }
        });
    }


    @Override
    protected void onDestroy() {
        if (hasLogin) {
            logout();
        }
        removeCallbacks();
        if (mManager != null) {
            localWakeLock.setReferenceCounted(false);
            localWakeLock.release();//释放电源锁，如果不释放finish这个acitivity后仍然会有自动锁屏的效果
            mManager.unregisterListener(this);//注销传感器监听
        }
        if (handler != null) {
            handler.removeCallbacksAndMessages(null);
            handlerThread.quit();
        }

        if (mReceiver != null) {
            unregisterReceiver(mReceiver);
        }

        super.onDestroy();
    }


    private void logout() {

        boolean success = zegoAudioRoom.logoutRoom();

        hasLogin = false;
        hasPublish = false;


        MainActivity.ZGLog.d("logout: %s", success);
    }


    private void removeCallbacks() {
        zegoAudioRoom.setAudioRoomDelegate(null);
        zegoAudioRoom.setAudioPublisherDelegate(null);
        zegoAudioRoom.setAudioPlayerDelegate(null);
        zegoAudioRoom.setAudioLiveEventDelegate(null);
        zegoAudioRoom.setAudioRecordDelegate(null);
        zegoAudioRoom.setAudioDeviceEventDelegate(null);
        zegoAudioRoom.setAudioPrepareDelegate(null);
        zegoAudioRoom.setAudioAVEngineDelegate(null);
    }


    //调用距离传感器，控制屏幕
    private SensorManager mManager;//传感器管理对象
    //屏幕开关
    private PowerManager localPowerManager = null;//电源管理对象
    private PowerManager.WakeLock localWakeLock = null;//电源锁


    @Override
    public void onSensorChanged(SensorEvent event) {
        float[] its = event.values;
        //Log.d(TAG,"its array:"+its+"sensor type :"+event.sensor.getType()+" proximity type:"+Sensor.TYPE_PROXIMITY);
        if (its != null && event.sensor.getType() == Sensor.TYPE_PROXIMITY) {
            // boolean temp =  speaker;
            System.out.println("its[0]:" + its[0]);

            //经过测试，当手贴近距离感应器的时候its[0]返回值为0.0，当手离开时返回1.0
            if (its[0] == 0.0) {// 贴近手机
//                activityZegoPhoneBinding.btnSpeaker.setChecked(false);
//                speaker = temp;
                Log.d("zego", "hands up in calling activity");
                if (localWakeLock.isHeld()) {
                    return;
                } else {
                    localWakeLock.acquire();// 申请设备电源锁
                }
            } else {// 远离手机

                System.out.println("hands moved");
                Log.d("zego", "hands moved in calling activity");
//                if(!speaker){
//                    activityZegoPhoneBinding.btnSpeaker.setChecked(true);
//                }
                //    speaker = temp;
                if (localWakeLock.isHeld()) {
                    return;
                } else {
                    localWakeLock.setReferenceCounted(false);
                    localWakeLock.release(); // 释放设备电源锁
                }
            }
        }

    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}
