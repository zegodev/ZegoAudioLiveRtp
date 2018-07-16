package com.zego.audioroomdemo.activities;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.graphics.Color;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.zego.audioroomdemo.AudioApplication;
import com.zego.audioroomdemo.MainActivity;
import com.zego.audioroomdemo.utils.PrefUtils;
import com.zego.audioroomdemo.R;
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
import com.zego.zegoaudioroom.callback.ZegoRoomMessageDelegate;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoIM;
import com.zego.zegoliveroom.entity.AuxData;
import com.zego.zegoliveroom.entity.ZegoAudioFrame;
import com.zego.zegoliveroom.entity.ZegoConversationMessage;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;
import com.zego.zegoliveroom.entity.ZegoUserState;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class SessionActivity extends AppCompatActivity {

    @Bind(R.id.btn_communicate_action)
    public Button btnCommunicate;

    @Bind(R.id.btn_aux)
    public Button btnAux;

    @Bind(R.id.btn_mute)
    public Button btnMute;

    @Bind(R.id.btn_microphone)
    public Button btnMicrophone;

    @Bind(R.id.btn_recorder)
    public Button btnRecorder;

    @Bind(R.id.tv_event_tips)
    public TextView tvEventTips;

    @Bind(R.id.stream_list)
    public ListView ctrlStreamList;

    @Bind(R.id.empty_data_tip)
    public TextView emptyView;

    @Bind(R.id.lv_messages)
    public ListView lvMessages;

    @Bind(R.id.btn_send)
    public Button btnSend;

    @Bind(R.id.et_message)
    public EditText etMessage;

    @Bind(R.id.btn_game_background_music)
    public Button btnGameBackground;


    @Bind(R.id.btn_game_music_volume)
    public SeekBar mSeekBar;


    @Bind(R.id.spinner_latency)
    public Spinner spinner;

    private ZegoAudioRoom zegoAudioRoom;

    private StreamAdapter streamAdapter;

    private MessageAdapter messageAdapter;

    private InputStream backgroundMusicStream;

    /**
     * 是否已经推流
     */
    private boolean hasPublish = false;
    private String publishStreamId = null;

    private boolean hasLogin = false;

    private boolean enableAux = false;
    private boolean enableMute = false;
    private boolean enableRecorder = false;
    private boolean enableMic = true;

    private String appTitle;

    private String currentRoomId;

    private boolean isPromptToast = true;

    int restartCount = 0;

    Handler restartPublishHandler;
    final int RESTART_PUBLSH_MSG = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_session);

        ButterKnife.bind(this);

        zegoAudioRoom = ((AudioApplication) getApplication()).getAudioRoomClient();
        restartPublishHandler = new Handler(getMainLooper(), new PublishHandlerImpl());
        if (PrefUtils.isManualPublish()) {
            btnCommunicate.setVisibility(View.VISIBLE);
            btnCommunicate.setEnabled(false);
        } else {
            btnCommunicate.setVisibility(View.GONE);
        }

        streamAdapter = new StreamAdapter();
        ctrlStreamList.setEmptyView(emptyView);
        ctrlStreamList.setAdapter(streamAdapter);

        messageAdapter = new MessageAdapter();
        lvMessages.setEmptyView(emptyView);
        lvMessages.setAdapter(messageAdapter);

        Intent startIntent = getIntent();
        String roomId = startIntent.getStringExtra("roomId");
        if (TextUtils.isEmpty(roomId)) {
            Toast.makeText(this, R.string.zg_tip_parameter_illegal, Toast.LENGTH_LONG).show();
            finish();
        } else {
            currentRoomId = roomId;
            appTitle = startIntent.getStringExtra("title");
            setTitle(appTitle);
            setupCallbacks();
            login(roomId);
        }
        mSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int volume=seekBar.getProgress();
                if(player!=null) {
                    player.setVolume((volume * 0.1f), (volume * 0.1f));
                }
            }
        });
        mSeekBar.setProgress(5);

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(position == 0){
                    zegoAudioRoom.setLatencyMode(ZegoConstants.LatencyMode.Normal);
                }else {
                    zegoAudioRoom.setLatencyMode(ZegoConstants.LatencyMode.Low);
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
    }

    /**
     * Take care of popping the fragment back stack or finishing the activity
     * as appropriate.
     */
    @Override
    public void onBackPressed() {
        if (hasLogin) {
            logout();
        }
        removeCallbacks();
        super.onBackPressed();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_show_logs:
                Intent startIntent = new Intent(SessionActivity.this, LogsActivity.class);
                startIntent.putExtra("title", appTitle);
                startActivity(startIntent);
                return true;

            case R.id.action_close:
                onBackPressed();
                return true;

            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @OnClick({R.id.btn_communicate_action, R.id.btn_aux, R.id.btn_mute, R.id.btn_recorder, R.id.btn_send, R.id.btn_microphone})
    public void onViewClicked(View view) {
        switch (view.getId()) {
            case R.id.btn_communicate_action:
                handleCommunicate();
                break;

            case R.id.btn_aux:
                handleAuxState();
                break;

            case R.id.btn_mute:
                handleMuteState();
                break;

            case R.id.btn_recorder:
                handleRecorderState();
                break;

            case R.id.btn_send:
                handleSendMessage();
                break;

            case R.id.btn_microphone:
                handleMicrophone();
                break;
        }
    }


    /**
     * 延时重新推流
     * 最多只能重试10次重新推流
     */

    private class PublishHandlerImpl implements Handler.Callback {

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
                    Toast.makeText(SessionActivity.this, getString(R.string.zg_text_app_restart_publish_failure), Toast.LENGTH_LONG).show();
                }
            }
            return false;
        }
    }

    protected InputStream mIsBackgroundMusic = null;


    private void setupCallbacks() {
        zegoAudioRoom.setAudioRoomDelegate(new ZegoAudioRoomDelegate() {
            @Override
            public void onKickOut(int errorCode, String roomId) {
                MainActivity.ZGLog.d("onKickOut room: %s, errorCode: %d", roomId, errorCode);
                tvEventTips.setText(getString(R.string.zg_tip_user_kickout, roomId, errorCode));
            }

            @Override
            public void onDisconnect(int errorCode, String roomId) {
                MainActivity.ZGLog.d("onDisconnect room: %s, errorCode: %d", roomId, errorCode);
                tvEventTips.setText(getString(R.string.zg_tip_user_disconnect, roomId, errorCode));
            }

            @Override
            public void onStreamUpdate(ZegoAudioStreamType zegoAudioStreamType, ZegoAudioStream zegoAudioStream) {
                MainActivity.ZGLog.d("onStreamUpdate, type: %s, streamId: %s", zegoAudioStreamType, zegoAudioStream.getStreamId());
//                String streamId = zegoAudioStream.getStreamId();
                switch (zegoAudioStreamType) {
                    case ZEGO_AUDIO_STREAM_ADD:
                        streamAdapter.insertItem(zegoAudioStream);
//                        tvEventTips.setText("新增流：" + streamId);
                        break;
                    case ZEGO_AUDIO_STREAM_DELETE:
                        streamAdapter.removeItem(zegoAudioStream);
//                        tvEventTips.setText("删除流：" + streamId);
                        break;
                    default:
                        break;
                }
            }

            @Override
            public void onUserUpdate(ZegoUserState[] userList, int updateType) {
                MainActivity.ZGLog.d("onUserUpdate, updateType: " + (updateType == ZegoIM.UserUpdateType.Increase ? "Increase" : "Total"));
                for (ZegoUserState user : userList) {
                    MainActivity.ZGLog.d("onUserUpdate, userName: " + user.userName + "; updateFlag: " + (user.updateFlag == ZegoIM.UserUpdateFlag.Added ? "Add" : "Delete"));
                    if (user.updateFlag == ZegoIM.UserUpdateFlag.Added) {
                        tvEventTips.setText(getString(R.string.zg_tip_user_enter_a_room, user.userName));
                    } else {
                        tvEventTips.setText(getString(R.string.zg_tip_user_leave_a_room, user.userName));
                    }
                }
            }

            @Override
            public void onUpdateOnlineCount(String s, int i) {
                MainActivity.ZGLog.d("online count: %d", i);
            }

            @Override
            public void onRecvRoomMessage(String roomId, ZegoRoomMessage[] messages) {
                messageAdapter.updateData(messages);
                lvMessages.setSelection(messageAdapter.getCount()-1);
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

                if (TextUtils.equals(currentRoomId, roomId)) {
                    tvEventTips.setText(getString(R.string.zg_tip_receive_server_message, content));
                }
            }

            @Override
            public void onStreamExtraInfoUpdated(ZegoAudioStream[] zegoAudioStreams, String s) {

            }


        });
        zegoAudioRoom.setAudioPublisherDelegate(new ZegoAudioLivePublisherDelegate() {

            @Override
            public void onPublishStateUpdate(int stateCode, String streamId, HashMap<String, Object> info) {
                MainActivity.ZGLog.d("onPublishStateUpdate, stateCode: %d, streamId: %s, info: %s", stateCode, streamId, info);

                btnCommunicate.setEnabled(true);

                if (stateCode == 0) {
                    hasPublish = true;
                    publishStreamId = streamId;
                    ZegoAudioStream myStream = new ZegoAudioStream(streamId, PrefUtils.getUserId(), PrefUtils.getUserName());
                    streamAdapter.insertItem(myStream);

                    btnCommunicate.setText(R.string.zg_stop_communicate);
                    tvEventTips.setText(R.string.zg_tip_publish_stream_success);
                    /**
                     * 清空重试计数器
                     */
                    restartCount = 0;
                    isPromptToast = true;
                } else {
                    btnCommunicate.setText(R.string.zg_start_communicate);
                    tvEventTips.setText(getString(R.string.zg_tip_publish_stream_failed, stateCode));
                    ZegoAudioStream myStream = new ZegoAudioStream(streamId, PrefUtils.getUserId(), PrefUtils.getUserName());
                    streamAdapter.removeItem(myStream);
                    /**
                     * 延时10秒后开启重新推流
                     */
                    restartPublishHandler.removeMessages(RESTART_PUBLSH_MSG);
                    restartPublishHandler.sendMessageDelayed(restartPublishHandler.obtainMessage(RESTART_PUBLSH_MSG), 10000);
                }
            }

            @Override
            public ZegoAuxData onAuxCallback(int dataLen) {
                if (dataLen <= 0) return null;

                // 开启伴奏后, sdk每20毫秒一次取数据
                ZegoAuxData auxData = new ZegoAuxData();
                auxData.dataBuf = new byte[AUX_DATA_LENGHT];

                try {
                    AssetManager am = getAssets();
                    if (mIsBackgroundMusic == null) {
                        // a.pcm 为用于混音的音频数据，其采样率为 44100，声道数为 2，位深 16
                        mIsBackgroundMusic = am.open("a.pcm");
                    }

                    int len = mIsBackgroundMusic.read(auxData.dataBuf);
                    if (len <= 0) {
                        // 歌曲播放完毕
                        mIsBackgroundMusic.close();
                        mIsBackgroundMusic = null;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

                auxData.channelCount = AUX_DATA_CHANNEL_COUNT;
                auxData.sampleRate = AUX_DATA_SAMPLE_RATE;

                return auxData;
            }

            @Override
            public void onPublishQualityUpdate(String streamId, ZegoStreamQuality zegoStreamQuality) {
                MainActivity.ZGLog.d("onPublishQualityUpdate, streamId: %s, quality: %d, audioBitrate: %fkb",
                        streamId, zegoStreamQuality.quality, zegoStreamQuality.audioBitrate);
            }
        });
        zegoAudioRoom.setAudioPlayerDelegate(new ZegoAudioLivePlayerDelegate() {
            @Override
            public void onPlayStateUpdate(int stateCode, ZegoAudioStream zegoAudioStream) {
                MainActivity.ZGLog.d("onPlayStateUpdate, stateCode: %d, streamId: %s", stateCode, zegoAudioStream.getStreamId());
                if (stateCode == 0) {
                    tvEventTips.setText(getString(R.string.zg_tip_play_stream_success, zegoAudioStream.getStreamId()));
                } else {
                    tvEventTips.setText(getString(R.string.zg_tip_play_stream_failed, stateCode));
                }
            }

            @Override
            public void onPlayQualityUpdate(String streamId, ZegoStreamQuality zegoStreamQuality) {
                MainActivity.ZGLog.d("onPlayQualityUpdate, streamId: %s, quality: %d,  audioBitrate: %fkb",
                        streamId, zegoStreamQuality.quality, zegoStreamQuality.audioBitrate);
            }
        });
        zegoAudioRoom.setAudioLiveEventDelegate(new ZegoAudioLiveEventDelegate() {
            @Override
            public void onAudioLiveEvent(ZegoAudioLiveEvent zegoAudioLiveEvent, HashMap<String, String> info) {
                MainActivity.ZGLog.d("onAudioLiveEvent, event: %s, info: %s", zegoAudioLiveEvent, info);
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

    final static int AUX_DATA_CHANNEL_COUNT = 2;
    final static int AUX_DATA_SAMPLE_RATE = 44100;
    final static int AUX_DATA_LENGHT = AUX_DATA_SAMPLE_RATE * AUX_DATA_CHANNEL_COUNT * 2 / 50;

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

    MediaPlayer mMediaPlayer = null;


    @OnClick(R.id.btn_game_background_music)
    public void openGameBackgroundMusic() {

        if (btnGameBackground.getText().equals(getString(R.string.zg_open_game_backround))) {
            playGameMusic();
            btnGameBackground.setText(R.string.zg_close_game_backround);
        } else {
            stopGameMusic();
            btnGameBackground.setText(R.string.zg_open_game_backround);
        }


    }

    MediaPlayer player = null;

    private AssetManager assetManager = null;

    private MediaPlayer playGameMusic() {

        try {
            if (player == null) {
                player = new MediaPlayer();
            }
            if (assetManager == null) {
                assetManager = getAssets();

            }
            AssetFileDescriptor fileDescriptor = assetManager.openFd("game_music.mp3");
            player.setDataSource(fileDescriptor.getFileDescriptor(), fileDescriptor.getStartOffset(),
                    fileDescriptor.getStartOffset());
            player.setLooping(true);
            player.setAudioStreamType(AudioManager.STREAM_MUSIC);
            player.prepareAsync();
            player.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer player) {
                    player.start();
                    player.setVolume(mSeekBar.getProgress()*0.1f,mSeekBar.getProgress()*0.1f);

                }
            });


        } catch (IOException e) {
            e.printStackTrace();
        }
        return player;
    }

    private void stopGameMusic() {


        if (player != null) {
            player.stop();
            player.release();
            player = null;
        }


    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        stopGameMusic();
    }

    private void handleCommunicate() {
        if (!PrefUtils.isManualPublish()) return;

        if (hasPublish) {
            zegoAudioRoom.stopPublish();
            btnCommunicate.setText(R.string.zg_start_communicate);
            ZegoAudioStream myStream = new ZegoAudioStream(publishStreamId, PrefUtils.getUserId(), PrefUtils.getUserName());
            streamAdapter.removeItem(myStream);
            publishStreamId = null;
            hasPublish = false;
            tvEventTips.setText(R.string.zg_tip_stop_publish);
        } else {
            btnCommunicate.setEnabled(false);
            zegoAudioRoom.startPublish();
        }
    }

    private void login(String roomId) {
        tvEventTips.setText(getString(R.string.zg_tip_begin_login_room, roomId));
        zegoAudioRoom.setUserStateUpdate(true);
        zegoAudioRoom.enableAux(false);
        zegoAudioRoom.enableMic(true);
        zegoAudioRoom.enableSelectedAudioRecord(ZegoConstants.AudioRecordMask.NoRecord, 44100);
        zegoAudioRoom.enableSpeaker(true);

        boolean success = zegoAudioRoom.loginRoom(roomId, new ZegoLoginAudioRoomCallback() {
            @Override
            public void onLoginCompletion(int state) {
                MainActivity.ZGLog.d("onLoginCompletion: 0x%1$x", state);

                if (state == 0) {
                    hasLogin = true;

                    btnAux.setEnabled(true);
                    btnMute.setEnabled(true);
                    btnRecorder.setEnabled(true);
                    btnMicrophone.setEnabled(true);

                    if (PrefUtils.isManualPublish()) {
                        btnCommunicate.setEnabled(true);
                    }

                    tvEventTips.setText(R.string.zg_tip_login_success);
                } else {
                    Toast.makeText(SessionActivity.this, String.format("Login Error: 0x%1$x", state), Toast.LENGTH_LONG).show();
                    tvEventTips.setText(getString(R.string.zg_tip_login_failed_state, state));
                }
            }
        });
        MainActivity.ZGLog.d("login: %s", success);
        if (!success) {
            tvEventTips.setText(R.string.zg_tip_login_failed);
        }
    }

    private void logout() {
        zegoAudioRoom.enableAux(false);     // 停止伴音
        boolean success = zegoAudioRoom.logoutRoom();
        streamAdapter.clear();
        hasLogin = false;
        hasPublish = false;

        btnAux.setEnabled(false);
        btnMute.setEnabled(false);
        btnRecorder.setEnabled(false);
        btnMicrophone.setEnabled(false);

        btnCommunicate.setText(R.string.zg_start_communicate);
        if (PrefUtils.isManualPublish()) {
            btnCommunicate.setEnabled(false);
        }

        MainActivity.ZGLog.d("logout: %s", success);
    }

    private void handleAuxState() {
        enableAux = !enableAux;
        zegoAudioRoom.enableAux(enableAux);

        btnAux.setText(enableAux ? R.string.zg_btn_text_aux_off : R.string.zg_btn_text_aux);
    }

    private void handleMuteState() {
        enableMute = !enableMute;
        zegoAudioRoom.enableSpeaker(!enableMute);

        btnMute.setText(enableMute ? R.string.zg_btn_text_mute_off : R.string.zg_btn_text_mute);
    }

    private void handleRecorderState() {
        enableRecorder = !enableRecorder;
        int mask = enableRecorder ? ZegoConstants.AudioRecordMask.Mix : ZegoConstants.AudioRecordMask.NoRecord;
        zegoAudioRoom.enableSelectedAudioRecord(mask, 44100);

        btnRecorder.setText(enableRecorder ? R.string.zg_btn_text_record_off : R.string.zg_btn_text_record_on);
    }

    private void handleSendMessage() {
        String msgContent = etMessage.getText().toString();
        boolean success = zegoAudioRoom.sendRoomMessage(ZegoIM.MessageType.Text, ZegoIM.MessageCategory.Chat, ZegoIM.MessagePriority.Default, msgContent, new ZegoRoomMessageDelegate() {
            @Override
            public void onSendRoomMessage(int errorCode, String roomId, long sessionId) {
                MainActivity.ZGLog.d("sendRoomMessage, errorCode: %d, sessionId: %d", errorCode, sessionId);
            }
        });
        if (success) {
            ZegoRoomMessage message = new ZegoRoomMessage();
            message.content = msgContent;
            message.fromUserID = PrefUtils.getUserId();
            messageAdapter.addItem(message);
            etMessage.setText("");
            lvMessages.setSelection(messageAdapter.getCount()-1);
        } else {
            tvEventTips.setText(R.string.zg_tip_send_message_failed);
        }
    }

    private void handleMicrophone() {
        enableMic = !enableMic;
        zegoAudioRoom.enableMic(enableMic);

        btnMicrophone.setText(enableMic ? R.string.zg_btn_text_mic_off : R.string.zg_btn_text_mic_on);
    }

    private class StreamAdapter extends BaseAdapter {
        private List<ZegoAudioStream> streamSet;
        private LayoutInflater inflater;

        public StreamAdapter() {
            inflater = getLayoutInflater();
            streamSet = new ArrayList<>();
        }

        @Override
        public int getCount() {
            return streamSet.size();
        }

        @Override
        public Object getItem(int position) {
            return streamSet.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = inflater.inflate(R.layout.widget_list_item, null, false);
            }

            ZegoAudioStream stream = (ZegoAudioStream) getItem(position);
            String streamId = stream.getStreamId();
            String userName = stream.getUserName();
            String content = String.format("Stream %d: %s\nUser: %s", position, streamId, userName);
            ((TextView) convertView).setText(content);
            if (TextUtils.equals(publishStreamId, streamId)) {
                ((TextView) convertView).setTextColor(Color.argb(255, 255, 81, 50));
            } else {
                ((TextView) convertView).setTextColor(Color.argb(255, 123, 123, 123));
            }
            return convertView;
        }

        public void insertItem(ZegoAudioStream item) {
            if (streamSet.contains(item)) return;

            streamSet.add(item);
            notifyDataSetChanged();
        }

        public void removeItem(ZegoAudioStream item) {
            if (item == null || streamSet == null || streamSet.size() == 0) {
                return;
            }

            for (ZegoAudioStream stream : streamSet) {
                if (TextUtils.equals(stream.getStreamId(), item.getStreamId())) {
                    streamSet.remove(stream);
                    notifyDataSetChanged();
                    break;
                }
            }
        }

        public void clear() {
            streamSet.clear();
            notifyDataSetChanged();
        }
    }

    private class MessageAdapter extends BaseAdapter {
        private List<ZegoRoomMessage> messageSet;
        private LayoutInflater inflater;

        public MessageAdapter() {
            messageSet = new ArrayList<>();
            inflater = getLayoutInflater();
        }

        /**
         * How many items are in the data set represented by this Adapter.
         *
         * @return Count of items.
         */
        @Override
        public int getCount() {
            return messageSet.size();
        }

        /**
         * Get the data item associated with the specified position in the data set.
         *
         * @param position Position of the item whose data we want within the adapter's
         *                 data set.
         * @return The data at the specified position.
         */
        @Override
        public Object getItem(int position) {
            return messageSet.get(position);
        }

        /**
         * Get the row id associated with the specified position in the list.
         *
         * @param position The position of the item within the adapter's data set whose row id we want.
         * @return The id of the item at the specified position.
         */
        @Override
        public long getItemId(int position) {
            return position;
        }

        /**
         * Get a View that displays the data at the specified position in the data set. You can either
         * create a View manually or inflate it from an XML layout file. When the View is inflated, the
         * parent View (GridView, ListView...) will apply default layout parameters unless you use
         * {@link LayoutInflater#inflate(int, ViewGroup, boolean)}
         * to specify a root view and to prevent attachment to the root.
         *
         * @param position    The position of the item within the adapter's data set of the item whose view
         *                    we want.
         * @param convertView The old view to reuse, if possible. Note: You should check that this view
         *                    is non-null and of an appropriate type before using. If it is not possible to convert
         *                    this view to display the correct data, this method can create a new view.
         *                    Heterogeneous lists can specify their number of view types, so that this View is
         *                    always of the right type (see {@link #getViewTypeCount()} and
         *                    {@link #getItemViewType(int)}).
         * @param parent      The parent that this view will eventually be attached to
         * @return A View corresponding to the data at the specified position.
         */
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            ViewHolder viewHolder;
            if (convertView == null) {
                convertView = inflater.inflate(android.R.layout.simple_list_item_2, null, false);
                viewHolder = new ViewHolder();
                viewHolder.text1 = (TextView) convertView.findViewById(android.R.id.text1);
                viewHolder.text2 = (TextView) convertView.findViewById(android.R.id.text2);
                convertView.setTag(viewHolder);
            } else {
                viewHolder = (ViewHolder) convertView.getTag();
            }

            ZegoRoomMessage message = (ZegoRoomMessage) getItem(position);
            if (message.fromUserID.equals(PrefUtils.getUserId())) {
                viewHolder.text1.setText("I say:");
            } else {
                viewHolder.text1.setText("from : " + message.fromUserName + ":");
            }
            viewHolder.text2.setText(message.content);
            return convertView;
        }

        public void updateData(ZegoRoomMessage[] messages) {
            if (messages != null && messages.length > 0) {
                for (ZegoRoomMessage message : messages) {
                    messageSet.add(message);
                }
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        notifyDataSetChanged();
                    }
                });
            }
        }

        public void addItem(ZegoRoomMessage message) {
            if (message == null) return;

            messageSet.add(message);
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    notifyDataSetChanged();
                }
            });
        }

        private class ViewHolder {
            TextView text1;
            TextView text2;
        }
    }
}
